#include "Hq/JsonSerializer.h"
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

void JsonSerializer::operator()(double& value, const std::string& s)
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

void JsonSerializer::operator()(double& value)
{
    _writer.Double(value);
}

//////////////// JsonDeserializer

JsonDeserializer::JsonDeserializer(std::istream& in)
    : _isw(in)
{
    _document.ParseStream(_isw);
}

JsonDeserializer::~JsonDeserializer()
{
}


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
