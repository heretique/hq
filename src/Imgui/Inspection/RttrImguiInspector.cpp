#include "RttrImguiInspector.h"
#include "rttr/registration"

#include "imgui.h"
#include "imgui_internal.h"

#include <unordered_map>
#include <vector>

namespace ui = ImGui;


struct InspectorRegistry
{
    InspectorRegistry()
    {
        auto inspectorTypes = rttr::type::get<Inspector>().get_derived_classes();
        for (auto& inspectorType : inspectorTypes)
        {
            auto inspectedTypeVar = inspectorType.get_metadata("InspectedType");
            if (inspectedTypeVar)
            {
                auto inspectedType = inspectedTypeVar.get_value<rttr::type>();
                auto inspectorVar = inspectorType.create();
                if (inspectorVar)
                {
                    typeMap[inspectedType] = inspectorVar.get_value<std::shared_ptr<Inspector>>();
                }
            }
        }
    }
    std::unordered_map<rttr::type, std::shared_ptr<Inspector>> typeMap;
};

std::shared_ptr<Inspector> get_inspector(rttr::type type)
{
    static InspectorRegistry registry;
    return registry.typeMap[type];
}


rttr::variant emptyMetaRead(const rttr::variant& other)
{
    return rttr::variant();
}

bool inspectVar(rttr::variant& var, bool skipCustom, bool readonly, const MetaReader& readMetadata)
{
    rttr::instance object = var;
    auto type = object.get_derived_type();
    auto properties = type.get_properties();

    bool changed = false;

    auto inspector = get_inspector(type);
    if (!skipCustom && inspector)
    {
        changed |= inspector->inspect(var, readonly, readMetadata);
    }
    else if (properties.empty())
    {
        if (type.is_enumeration())
        {
            auto enumeration = type.get_enumeration();
            changed |= inspectEnum(var, enumeration, readonly);
        }
    }
    else
    {
        for (auto& prop : properties)
        {
            bool propChanged = false;
            auto propVar = prop.get_value(object);
            bool isReadonly = prop.is_readonly();
            bool isArray = propVar.is_sequential_container();
            bool isAssociativeContainer = propVar.is_associative_container();
            bool isEnum = prop.is_enumeration();
            rttr::instance prop_object = propVar;
            bool hasInspector = !!get_inspector(prop_object.get_derived_type());
            bool details = !hasInspector && !isEnum;
            PropertyLayout layout(prop);
            bool open = true;
            if (details)
            {
                ui::AlignTextToFramePadding();
                open = ui::TreeNode("details");
            }

            if (open)
            {
                auto get_meta = [&prop](const rttr::variant& name) -> rttr::variant {
                    return prop.get_metadata(name);
                };
                if (isArray)
                {
                    propChanged |= inspectArray(propVar, isReadonly, readMetadata);
                }
                else if (isAssociativeContainer)
                {
                    propChanged |= inspectAssociativeContainer(propVar, isReadonly);
                }
                else if (isEnum)
                {
                    auto enumeration = prop.get_enumeration();
                    propChanged |= inspectEnum(propVar, enumeration, isReadonly);
                }
                else
                {
                    propChanged |= inspectVar(propVar, false, isReadonly, readMetadata);
                }

                if (details && open)
                    ui::TreePop();
            }

            if (propChanged && !isReadonly)
            {
                prop.set_value(object, propVar);
            }

            changed |= propChanged;
        }
    }

    return changed;
}

bool inspectArray(rttr::variant& var, bool read_only, const MetaReader& readMetadata)
{
    auto view = var.create_sequential_view();
    auto size = view.get_size();
    bool changed = false;
    auto int_size = static_cast<int>(size);

    if (view.is_dynamic())
    {
        PropertyLayout layout("Size");

        if (!read_only)
        {
            if (ui::InputInt("", &int_size))
            {
                if (int_size < 0)
                    int_size = 0;
                size = static_cast<std::size_t>(int_size);
                changed |= view.set_size(size);
            }
        }
        else
        {
            ui::AlignTextToFramePadding();
            ui::TextUnformatted(std::to_string(int_size).c_str());
        }
    }

    for (std::size_t i = 0; i < size; ++i)
    {
        auto value = view.get_value(i).extract_wrapped_value();
        std::string element = "Element ";
        element += std::to_string(i);

        PropertyLayout layout(element.data());

        changed |= inspectVar(value, false, read_only, readMetadata);

        if (changed)
            view.set_value(i, value);
    }

    return changed;
}

bool inspectAssociativeContainer(rttr::variant& var, bool read_only)
{
    auto associative_view = var.create_associative_view();
    // auto size = associative_view.get_size();
    bool changed = false;

    return changed;
}

bool inspectEnum(rttr::variant& var, rttr::enumeration& data, bool read_only)
{
    auto strings = data.get_names();
    std::vector<const char*> cstrings{};
    cstrings.reserve(strings.size());

    for (const auto& string : strings)
        cstrings.push_back(string.data());

    if (read_only)
    {
        int listbox_item_current = var.to_int();
        ui::AlignTextToFramePadding();
        ui::TextUnformatted(cstrings[std::size_t(listbox_item_current)]);
    }
    else
    {
        int listbox_item_current = var.to_int();
        int listbox_item_size = static_cast<int>(cstrings.size());
        if (ui::Combo("", &listbox_item_current, cstrings.data(), listbox_item_size, listbox_item_size))
        {
            rttr::variant arg(listbox_item_current);
            arg.convert(var.get_type());
            var = arg;
            return true;
        }
    }

    return false;
}


void Tooltip(const rttr::property& prop)
{
    auto& g = *ui::GetCurrentContext();
    if (!g.DragDropActive && ui::IsItemHovered())
    {
        auto tooltip = prop.get_metadata("tooltip");
        if (tooltip)
        {
            ui::BeginTooltip();
            ui::TextUnformatted(tooltip.to_string().c_str());
            ui::EndTooltip();
        }
    }
}

void Tooltip(const std::string& tooltip)
{
    auto& g = *ui::GetCurrentContext();
    if (!g.DragDropActive && ui::IsItemHovered())
    {
        ui::BeginTooltip();
        ui::TextUnformatted(tooltip.c_str());
        ui::EndTooltip();
    }
}

PropertyLayout::PropertyLayout(const rttr::property& prop, bool columns /*= true*/)
{
    std::string pretty_name = prop.get_name().to_string();
    auto meta_pretty_name = prop.get_metadata("pretty_name");
    if (meta_pretty_name)
    {
        pretty_name = meta_pretty_name.get_value<std::string>();
    }

    if (columns)
    {
        if (ui::GetColumnsCount() > 1)
        {
            ui::EndColumns();
        }
        ui::BeginColumns("properties", 2, ImGuiColumnsFlags_NoBorder | ImGuiColumnsFlags_NoResize);
    }

    ui::AlignTextToFramePadding();
    ui::TextUnformatted(pretty_name.c_str());

    Tooltip(prop);

    ui::NextColumn();

    ui::PushID(pretty_name.c_str());
    ui::PushItemWidth(ui::GetContentRegionAvailWidth());
}

PropertyLayout::PropertyLayout(const std::string& name, bool columns /*= true*/)
{
    if (columns)
    {
        if (ui::GetColumnsCount() > 1)
        {
            ui::EndColumns();
        }
        ui::BeginColumns("properties", 2, ImGuiColumnsFlags_NoBorder | ImGuiColumnsFlags_NoResize);
    }

    ui::AlignTextToFramePadding();
    ui::TextUnformatted(name.c_str());

    ui::NextColumn();

    ui::PushID(name.c_str());
    ui::PushItemWidth(ui::GetContentRegionAvailWidth());
}

PropertyLayout::PropertyLayout(const std::string& name, const std::string& tooltip, bool columns /*= true*/)
{
    if (columns)
    {
        if (ui::GetColumnsCount() > 1)
        {
            ui::EndColumns();
        }
        ui::BeginColumns("properties", 2, ImGuiColumnsFlags_NoBorder | ImGuiColumnsFlags_NoResize);
    }

    ui::AlignTextToFramePadding();
    ui::TextUnformatted(name.c_str());

    Tooltip(tooltip);

    ui::NextColumn();

    ui::PushID(name.c_str());
    ui::PushItemWidth(ui::GetContentRegionAvailWidth());
}

PropertyLayout::~PropertyLayout()
{
    ui::PopItemWidth();
    ui::PopID();
    if (ui::GetColumnsCount() > 1)
    {
        ui::EndColumns();
    }
}


bool InspectorBool::inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata)
{
    auto data = inspectable.get_value<bool>();

    if (readonly)
    {
        ui::AlignTextToFramePadding();
        ui::TextUnformatted(data ? "true" : "false");
    }
    else
    {
        if (ui::Checkbox("", &data))
        {
            inspectable = data;
            return true;
        }
    }

    return false;
}

bool InspectorFloat::inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata)
{
    auto data = inspectable.to_float();
    if (readonly)
    {
        ui::AlignTextToFramePadding();
        ui::TextUnformatted(std::to_string(data).c_str());
    }
    else
    {
        float min = 0.0f;
        float max = 0.0f;
        float step = 0.05f;
        std::string format = "%.3f";

        auto minVar = readMetadata("min");
        if (minVar)
            min = minVar.to_float();

        auto maxVar = readMetadata("max");
        if (maxVar)
            max = maxVar.to_float();

        auto formatVar = readMetadata("format");
        if (formatVar)
            format = formatVar.to_string();

        auto stepVar = readMetadata("step");
        if (stepVar)
            step = stepVar.to_float();

        bool isRange = maxVar.is_valid();

        if (isRange)
        {
            if (ui::SliderFloat("", &data, min, max, format.c_str()))
            {
                inspectable = data;
                return true;
            }
        }
        else
        {
            if (ui::DragFloat("", &data, step, min, max))
            {
                inspectable = data;
                return true;
            }
        }
    }

    return false;
}

bool InspectorDouble::inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata)
{
    auto data = inspectable.to_double();
    if (readonly)
    {
        ui::AlignTextToFramePadding();
        ui::TextUnformatted(std::to_string(data).c_str());
    }
    else
    {
        double min = 0.0;
        double max = 0.0;
        float step = 0.05;
        std::string format = "%.3f";

        auto minVar = readMetadata("min");
        if (minVar)
            min = minVar.to_double();

        auto maxVar = readMetadata("max");
        if (maxVar)
            max = maxVar.to_double();

        auto formatVar = readMetadata("format");
        if (formatVar)
            format = formatVar.to_string();

        auto stepVar = readMetadata("step");
        if (stepVar)
            step = stepVar.to_float();

        bool isRange = maxVar.is_valid();

        if (isRange)
        {
            if (ui::SliderScalar("", ImGuiDataType_Double, &data, &min, &max, format.c_str()))
            {
                inspectable = data;
                return true;
            }
        }
        else
        {
            if (ui::DragScalar("", ImGuiDataType_Double, &data, step, &min, &max))
            {
                inspectable = data;
                return true;
            }
        }
    }

    return false;
}

bool InspectorInt8::inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata)
{
    auto data = static_cast<int>(inspectable.to_int8());
    if (readonly)
    {
        ui::AlignTextToFramePadding();
        ui::TextUnformatted(std::to_string(data).c_str());
    }
    else
    {
        int min = 0;
        int max = 0;

        auto minVar = readMetadata("min");
        if (minVar)
            min = minVar.to_int8();

        auto maxVar = readMetadata("max");
        if (maxVar)
            max = maxVar.to_int8();

        bool isRange = maxVar.is_valid();

        if (isRange)
        {
            if (ui::SliderInt("", &data, min, max))
            {
                inspectable = static_cast<std::int8_t>(data);
                return true;
            }
        }
        else
        {
            if (ui::DragInt("", &data))
            {
                inspectable = static_cast<std::int8_t>(data);
                return true;
            }
        }
    }

    return false;
}

bool InspectorInt16::inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata)
{
    auto data = static_cast<int>(inspectable.to_int16());
    if (readonly)
    {
        ui::AlignTextToFramePadding();
        ui::TextUnformatted(std::to_string(data).c_str());
    }
    else
    {
        int min = 0;
        int max = 0;

        auto minVar = readMetadata("min");
        if (minVar)
            min = minVar.to_int16();

        auto maxVar = readMetadata("max");
        if (maxVar)
            max = maxVar.to_int16();

        bool isRange = maxVar.is_valid();

        if (isRange)
        {
            if (ui::SliderInt("", &data, min, max))
            {
                inspectable = static_cast<std::int16_t>(data);
                return true;
            }
        }
        else
        {
            if (ui::DragInt("", &data))
            {
                inspectable = static_cast<std::int16_t>(data);
                return true;
            }
        }
    }

    return false;
}

bool InspectorInt32::inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata)
{
    auto data = static_cast<int>(inspectable.to_int32());
    if (readonly)
    {
        ui::AlignTextToFramePadding();
        ui::TextUnformatted(std::to_string(data).c_str());
    }
    else
    {
        int min = 0;
        int max = 0;

        auto minVar = readMetadata("min");
        if (minVar)
            min = minVar.to_int32();

        auto maxVar = readMetadata("max");
        if (maxVar)
            max = maxVar.to_int32();

        bool isRange = maxVar.is_valid();

        if (isRange)
        {
            if (ui::SliderInt("", &data, min, max))
            {
                inspectable = static_cast<std::int32_t>(data);
                return true;
            }
        }
        else
        {
            if (ui::DragInt("", &data))
            {
                inspectable = static_cast<std::int32_t>(data);
                return true;
            }
        }
    }

    return false;
}

bool InspectorInt64::inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata)
{
    auto data = inspectable.to_int64();
    if (readonly)
    {
        ui::AlignTextToFramePadding();
        ui::TextUnformatted(std::to_string(data).c_str());
    }
    else
    {
        int64_t min = 0;
        int64_t max = 0;

        auto minVar = readMetadata("min");
        if (minVar)
            min = minVar.to_int64();

        auto maxVar = readMetadata("max");
        if (maxVar)
            max = maxVar.to_int64();

        bool isRange = maxVar.is_valid();

        if (isRange)
        {
            if (ui::SliderScalar("", ImGuiDataType_S64, &data, &min, &max))
            {
                inspectable = data;
                return true;
            }
        }
        else
        {
            if (ui::DragScalar("", ImGuiDataType_S64 , &data, 1.0f, &min, &max))
            {
                inspectable = data;
                return true;
            }
        }
    }

    return false;
}

bool InspectorUInt8::inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata)
{
    auto data = inspectable.to_uint8();
    if (readonly)
    {
        ui::AlignTextToFramePadding();
        ui::TextUnformatted(std::to_string(data).c_str());
    }
    else
    {
        uint8_t min = 0;
        uint8_t max = 0;

        auto minVar = readMetadata("min");
        if (minVar)
            min = minVar.to_uint8();

        auto maxVar = readMetadata("max");
        if (maxVar)
            max = maxVar.to_uint8();

        bool isRange = maxVar.is_valid();

        if (isRange)
        {
            if (ui::SliderScalar("", ImGuiDataType_U8, &data, &min, &max))
            {
                inspectable = data;
                return true;
            }
        }
        else
        {
            if (ui::DragScalar("", ImGuiDataType_U8, &data, 1.0f, &min, &max))
            {
                inspectable = data;
                return true;
            }
        }
    }

    return false;
}

bool InspectorUInt16::inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata)
{
    auto data = inspectable.to_uint16();
    if (readonly)
    {
        ui::AlignTextToFramePadding();
        ui::TextUnformatted(std::to_string(data).c_str());
    }
    else
    {
        uint16_t min = 0;
        uint16_t max = 0;

        auto minVar = readMetadata("min");
        if (minVar)
            min = minVar.to_uint16();

        auto maxVar = readMetadata("max");
        if (maxVar)
            max = maxVar.to_uint16();

        bool isRange = maxVar.is_valid();

        if (isRange)
        {
            if (ui::SliderScalar("", ImGuiDataType_U16, &data, &min, &max))
            {
                inspectable = data;
                return true;
            }
        }
        else
        {
            if (ui::DragScalar("", ImGuiDataType_U16, &data, 1.0f, &min, &max))
            {
                inspectable = data;
                return true;
            }
        }
    }

    return false;
}

bool InspectorUInt32::inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata)
{
    auto data = inspectable.to_uint32();
    if (readonly)
    {
        ui::AlignTextToFramePadding();
        ui::TextUnformatted(std::to_string(data).c_str());
    }
    else
    {
        uint32_t min = 0;
        uint32_t max = 0;

        auto minVar = readMetadata("min");
        if (minVar)
            min = minVar.to_uint32();

        auto maxVar = readMetadata("max");
        if (maxVar)
            max = maxVar.to_uint32();

        bool isRange = maxVar.is_valid();

        if (isRange)
        {
            if (ui::SliderScalar("", ImGuiDataType_U32, &data, &min, &max))
            {
                inspectable = data;
                return true;
            }
        }
        else
        {
            if (ui::DragScalar("", ImGuiDataType_U32, &data, 1.0f, &min, &max))
            {
                inspectable = data;
                return true;
            }
        }
    }

    return false;
}

bool InspectorUInt64::inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata)
{
    auto data = inspectable.to_uint64();
    if (readonly)
    {
        ui::AlignTextToFramePadding();
        ui::TextUnformatted(std::to_string(data).c_str());
    }
    else
    {
        uint64_t min = 0;
        uint64_t max = 0;

        auto minVar = readMetadata("min");
        if (minVar)
            min = minVar.to_uint64();

        auto maxVar = readMetadata("max");
        if (maxVar)
            max = maxVar.to_uint64();

        bool isRange = maxVar.is_valid();

        if (isRange)
        {
            if (ui::SliderScalar("", ImGuiDataType_U64, &data, &min, &max))
            {
                inspectable = data;
                return true;
            }
        }
        else
        {
            if (ui::DragScalar("", ImGuiDataType_U64, &data, 1.0f, &min, &max))
            {
                inspectable = data;
                return true;
            }
        }
    }

    return false;
}

bool InspectorString::inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata)
{
    auto data = inspectable.get_value<std::string>();
    if (readonly)
    {
        ui::AlignTextToFramePadding();
        ui::TextUnformatted(data.c_str());
    }
    else
    {
        static std::array<char, 64> inputBuff;
        inputBuff.fill(0);
        std::memcpy(inputBuff.data(), data.c_str(), data.size() < 64 ? data.size() : 64);
        if (ui::InputText("", inputBuff.data(), inputBuff.size(), ImGuiInputTextFlags_EnterReturnsTrue))
        {
            // copy from c_str to remove trailing zeros
            inspectable = std::string(inputBuff.data());
            return true;
        }
    }

    return false;
}


RTTR_REGISTRATION
{
    rttr::registration::class_<Inspector>("RttrImguiInspector");
    REGISTER_INSPECTOR(InspectorBool, bool);
    REGISTER_INSPECTOR(InspectorFloat, float);
    REGISTER_INSPECTOR(InspectorDouble, double);
    REGISTER_INSPECTOR(InspectorInt8, int8_t);
    REGISTER_INSPECTOR(InspectorInt16, int16_t);
    REGISTER_INSPECTOR(InspectorInt32, int32_t);
    REGISTER_INSPECTOR(InspectorInt64, int64_t);
    REGISTER_INSPECTOR(InspectorUInt8, uint8_t);
    REGISTER_INSPECTOR(InspectorUInt16, uint16_t);
    REGISTER_INSPECTOR(InspectorUInt32, uint32_t);
    REGISTER_INSPECTOR(InspectorUInt64, uint64_t);
    REGISTER_INSPECTOR(InspectorString, std::string);
}
