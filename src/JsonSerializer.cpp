#include "Hq/JsonSerializer.h"
#include "Hq/Serializable.h"
#include <rapidjson/filereadstream.h>
#include <cstdio>

namespace hq {

JsonSerializer::JsonSerializer(std::ostream& out)
    : _osw(out),
      _writer(_osw)
{
}

JsonSerializer::~JsonSerializer()
{
}

void JsonSerializer::beginObject(const std::string &s)
{
    if (!s.empty())
    {
        _writer.String(s);
    }
    _writer.StartObject();
}

void JsonSerializer::endObject()
{
    _writer.EndObject();
}

void JsonSerializer::beginArray(const std::string &s, const size_t)
{
    _writer.StartArray();
}

void JsonSerializer::endArray()
{
    _writer.EndArray();
}

void JsonSerializer::operator()(std::string& value, const std::string& s)
{
    _writer.String(s);
    _writer.String(value);
}

void JsonSerializer::operator()(const std::string& value, const std::string& s)
{
    _writer.String(s);
    _writer.String(value);
}

void JsonSerializer::operator()(u8& value, const std::string& s)
{
    _writer.String(s);
    _writer.Uint(value);
}

void JsonSerializer::operator()(const u8& value, const std::string& s)
{
    _writer.String(s);
    _writer.Uint(value);
}

void JsonSerializer::operator()(u32& value, const std::string& s)
{
    _writer.String(s);
    _writer.Uint(value);
}

void JsonSerializer::operator()(const u32& value, const std::string& s)
{
    _writer.String(s);
    _writer.Uint(value);
}

void JsonSerializer::operator()(u64& value, const std::string& s)
{
    _writer.String(s);
    _writer.Uint64(value);
}

void JsonSerializer::operator()(const u64& value, const std::string& s)
{
    _writer.String(s);
    _writer.Uint64(value);
}

void JsonSerializer::operator()(float& value, const std::string& s)
{
    _writer.String(s);
    _writer.Double(value);
}

void JsonSerializer::operator()(const float &value, const std::string &s)
{
    _writer.String(s);
    _writer.Double(value);
}

void JsonSerializer::operator()(double& value, const std::string& s)
{
    _writer.String(s);
    _writer.Double(value);
}

void JsonSerializer::operator()(const double &value, const std::string &s)
{
    _writer.String(s);
    _writer.Double(value);
}

void JsonSerializer::operator()(std::string& value)
{
    _writer.String(value);
}

void JsonSerializer::operator()(const std::string& value)
{
    _writer.String(value);
}

void JsonSerializer::operator()(u8& value)
{
    _writer.Uint(value);
}

void JsonSerializer::operator()(const u8& value)
{
    _writer.Uint(value);
}

void JsonSerializer::operator()(u32& value)
{
    _writer.Uint(value);
}

void JsonSerializer::operator()(const u32& value)
{
    _writer.Uint(value);
}

void JsonSerializer::operator()(u64& value)
{
    _writer.Uint64(value);
}

void JsonSerializer::operator()(const u64& value)
{
    _writer.Uint64(value);
}

void JsonSerializer::operator()(float& value)
{
    _writer.Double(value);
}

void JsonSerializer::operator()(const float &value)
{
    _writer.Double(value);
}

void JsonSerializer::operator()(double& value)
{
    _writer.Double(value);
}

void JsonSerializer::operator()(const double &value)
{
    _writer.Double(value);
}

//////////////// JsonDeserializer

JsonDeserializer::JsonDeserializer(std::istream& in)
    : _isw(in)
{
    _document.ParseStream(_isw);
    assert(_document.IsObject());
    _stack.emplace_back(&_document);
}

JsonDeserializer::~JsonDeserializer()
{
}

void JsonDeserializer::beginObject(const std::string &s)
{
    using namespace rapidjson;
    if (!s.empty())
    {
        assert(!_stack.empty());
        if (!_stack.back()->HasMember(s))
            return;

        const Value& val = (*_stack.back())[s];
        assert(val.IsObject());
        _stack.push_back(&val);
    }
}

void JsonDeserializer::beginObject(const size_t index)
{
    using namespace rapidjson;
    const Value& val = *_stack.back();
    assert(val.IsArray());
    assert(index < val.Size());
    const Value& element = val[index];
    assert(element.IsObject());
    _stack.push_back(&element);
}

void JsonDeserializer::endObject()
{
    _stack.pop_back();
}

size_t JsonDeserializer::beginArray(const std::string &s)
{
    using namespace rapidjson;
    assert(!_stack.empty());
    if (!_stack.back()->HasMember(s))
        return 0;

    const Value& val = (*_stack.back())[s];
    assert(val.IsArray());
    _stack.push_back(&val);
    return val.Size();
}

void JsonDeserializer::endArray()
{
    _stack.pop_back();
}

//void JsonDeserializer::operator()(Serializable &serializable)
//{
//    if (!_document.IsObject())
//        return;

//    _stack.push_back(&_document);
//    serializable.Serialize(*this);
//    _stack.pop_back();
//    assert(_stack.empty());
//}

//void JsonDeserializer::operator()(Serializable &serializable, const std::string &s)
//{
//    using namespace rapidjson;
//    assert(!_stack.empty());
//    if (!_stack.back()->HasMember(s))
//        return;

//    const Value& val = (*_stack.back())[s];
//    assert(val.IsObject());
//    _stack.push_back(&val);
//    serializable.Serialize(*this);
//    _stack.pop_back();
//}


//    template <typename T>
//    inline void operator() (std::vector<T>& container, const std::string& s)
//    {
//        using namespace rapidjson;
//        assert(!_stack.empty());
//        if (!_stack.back()->HasMember(s))
//            return;

//        const Value& val = (*_stack.back())[s];
//        assert(val.IsArray());
//        for (SizeType i = 0; i < val.Size(); ++i)
//        {
//            const Value& element = val[i];
//            if (std::is_class_v<T>)
//            {
//                assert(element.IsObject());
//            }
//            _stack.push_back(&element);
//            T value;
//            (*this)(value);
//            container.emplace_back(value);
//            _stack.pop_back();
//        }
//    }

//    template <typename K, typename T>
//    inline void operator() (std::unordered_map<K, T>& value, const std::string& s)
//	{
//		using namespace rapidjson;
//        assert(!_stack.empty());
//        if (!_stack.back()->HasMember(s))
//			return;

//        const Value& val = (*_stack.back())[s];
//		assert(val.IsArray());
//		for (SizeType i = 0; i < val.Size(); ++i)
//		{
//			const Value& element = val[i];
//			assert(element.IsObject());
//            _stack.push_back(&element);
//            K key;
//            T mapVal;
//			(*this)(key, "key");
//			(*this)(mapVal, "value");
//			value.insert(std::make_pair(std::move(key), std::move(mapVal)));
//            _stack.pop_back();
//		}
//	}

//    template <class T>
//    inline void operator() (std::unique_ptr<T>& value, const std::string& s)
//	{
//		using namespace rapidjson;
//        assert(!_stack.empty());
//        if (!_stack.back()->HasMember(s))
//			return;

//        const Value& val = (*_stack.back())[s];
//        value = std::make_unique<T>();
//		(*this)((*value.get()), s);
//	}

void JsonDeserializer::operator()(std::string& value, const std::string& s)
{
    using namespace rapidjson;
    assert(!_stack.empty());
    if (!_stack.back()->HasMember(s))
        return;

    const Value& val = (*_stack.back())[s];
    if (!val.IsString())
        return;

    value = val.GetString();
}

void JsonDeserializer::operator()(u8& value, const std::string& s)
{
    using namespace rapidjson;
    assert(!_stack.empty());
    if (!_stack.back()->HasMember(s))
        return;

    const Value& val = (*_stack.back())[s];
    if (!val.IsNumber())
        return;

    value = val.GetUint();
}

void JsonDeserializer::operator()(u32& value, const std::string& s)
{
    using namespace rapidjson;
    assert(!_stack.empty());
    if (!_stack.back()->HasMember(s))
        return;

    const Value& val = (*_stack.back())[s];
    if (!val.IsNumber())
        return;

    value = val.GetUint();
}

void JsonDeserializer::operator()(u64& value, const std::string& s)
{
    using namespace rapidjson;
    assert(!_stack.empty());
    if (!_stack.back()->HasMember(s))
        return;

    const Value& val = (*_stack.back())[s];
    if (!val.IsNumber())
        return;

    value = val.GetUint64();
}

void JsonDeserializer::operator()(float& value, const std::string& s)
{
    using namespace rapidjson;
    assert(!_stack.empty());
    if (!_stack.back()->HasMember(s))
        return;

    const Value& val = (*_stack.back())[s];
    if (!val.IsNumber())
        return;

    value = val.GetFloat();
}

void JsonDeserializer::operator()(double& value, const std::string& s)
{
    using namespace rapidjson;
    assert(!_stack.empty());
    if (!_stack.back()->HasMember(s))
        return;

    const Value& val = (*_stack.back())[s];
    if (!val.IsNumber())
        return;

    value = val.GetDouble();
}

void JsonDeserializer::operator()(std::string& value)
{
    using namespace rapidjson;
    assert(!_stack.empty());

    const Value& val = *_stack.back();
    if (!val.IsString())
        return;

    value = val.GetString();
}

void JsonDeserializer::operator()(u8& value)
{
    using namespace rapidjson;
    assert(!_stack.empty());

    const Value& val = *_stack.back();
    if (!val.IsNumber())
        return;

    value = val.GetUint();
}

void JsonDeserializer::operator()(u32& value)
{
    using namespace rapidjson;
    assert(!_stack.empty());

    const Value& val = *_stack.back();
    if (!val.IsNumber())
        return;

    value = val.GetUint();
}

void JsonDeserializer::operator()(u64& value)
{
    using namespace rapidjson;
    assert(!_stack.empty());

    const Value& val = *_stack.back();
    if (!val.IsNumber())
        return;

    value = val.GetUint64();
}

void JsonDeserializer::operator()(float& value)
{
    using namespace rapidjson;
    assert(!_stack.empty());

    const Value& val = *_stack.back();
    if (!val.IsNumber())
        return;

    value = val.GetFloat();
}

void JsonDeserializer::operator()(double& value)
{
    using namespace rapidjson;
    assert(!_stack.empty());

    const Value& val = *_stack.back();
    if (!val.IsNumber())
        return;

    value = val.GetDouble();
}


} // hq namespace
