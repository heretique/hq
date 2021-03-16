#pragma once

#include "rttr/type"

// Most of the code is inspired by https://github.com/volcoma/EtherealEngine (MIT Licensed)

using MetaReader = std::function<rttr::variant(const rttr::variant&)>;

class Inspector
{
    RTTR_ENABLE()
public:


    virtual ~Inspector() = default;
    virtual bool inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata) = 0;
};

rttr::variant emptyMetaRead(const rttr::variant& other);

bool inspectVar(rttr::variant& var, bool skip_custom = false, bool readonly = false, const MetaReader& readMetadata = emptyMetaRead);
bool inspectArray(rttr::variant& var, bool readonly = false, const MetaReader& readMetadata = emptyMetaRead);
bool inspectAssociativeContainer(rttr::variant& var, bool readonly = false);
bool inspectEnum(rttr::variant& var, rttr::enumeration& data, bool readonly = false);


class PropertyLayout
{
public:
    PropertyLayout(const rttr::property& prop, bool columns = true);
    PropertyLayout(const std::string& name, bool columns = true);
    PropertyLayout(const std::string& name, const std::string& tooltip, bool columns = true);

    ~PropertyLayout();
private:
    std::string _name;
};


class InspectorBool : public Inspector
{
    RTTR_ENABLE(Inspector)
public:
    virtual bool inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata) override;
};

class InspectorFloat : public Inspector
{
    RTTR_ENABLE(Inspector)
public:
    virtual bool inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata) override;
};

class InspectorDouble : public Inspector
{
    RTTR_ENABLE(Inspector)
public:
    virtual bool inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata) override;
};

class InspectorInt8 : public Inspector
{
    RTTR_ENABLE(Inspector)
public:
    virtual bool inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata) override;
};

class InspectorInt16 : public Inspector
{
    RTTR_ENABLE(Inspector)
public:
    virtual bool inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata) override;
};

class InspectorInt32 : public Inspector
{
    RTTR_ENABLE(Inspector)
public:
    virtual bool inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata) override;
};

class InspectorInt64 : public Inspector
{
    RTTR_ENABLE(Inspector)
public:
    virtual bool inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata) override;
};

class InspectorUInt8 : public Inspector
{
    RTTR_ENABLE(Inspector)
public:
    virtual bool inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata) override;
};

class InspectorUInt16 : public Inspector
{
    RTTR_ENABLE(Inspector)
public:
    virtual bool inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata) override;
};

class InspectorUInt32 : public Inspector
{
    RTTR_ENABLE(Inspector)
public:
    virtual bool inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata) override;
};

class InspectorUInt64 : public Inspector
{
    RTTR_ENABLE(Inspector)
public:
    virtual bool inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata) override;
};

class InspectorString : public Inspector
{
    RTTR_ENABLE(Inspector)
public:
    virtual bool inspect(rttr::variant& inspectable, bool readonly, const MetaReader& readMetadata) override;
};


#define REGISTER_INSPECTOR(InspectorType, InspectedType)                      \
    rttr::registration::class_<InspectorType>(#InspectorType)                 \
    (                                                                         \
		rttr::metadata("InspectedType", rttr::type::get<InspectedType>())     \
    )                                                                         \
	.constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
