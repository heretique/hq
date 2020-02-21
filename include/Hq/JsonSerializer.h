#pragma once

#include "Hq/Serializer.h"
#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/document.h>

namespace hq {

class JsonSerializer : public Serializer
{
public:
    JsonSerializer(std::ostream& out);
	~JsonSerializer();

    bool isDeserializer() const override
    {
        return false;
    }

    void beginObject(const std::string& s) override;
    void endObject() override;
    // serializers need to implement this
    void beginArray(const std::string& s, const size_t count) override;
    void endArray() override;

    void operator() (std::string& value, const std::string& s) override;
    void operator() (const std::string& value, const std::string& s) override;
    void operator() (u8& value, const std::string& s) override;
    void operator() (const u8& value, const std::string& s) override;
    void operator() (u32& value, const std::string& s) override;
    void operator() (const u32& value, const std::string& s) override;
    void operator() (u64& value, const std::string& s) override;
    void operator() (const u64& value, const std::string& s) override;
    void operator() (float& value, const std::string& s) override;
    void operator() (const float& value, const std::string& s) override;
    void operator() (double& value, const std::string& s) override;
    void operator() (const double& value, const std::string& s) override;


    void operator() (std::string& value) override;
    void operator() (const std::string& value) override;
    void operator() (u8& value) override;
    void operator() (const u8& value) override;
    void operator() (u32& value) override;
    void operator() (const u32& value) override;
    void operator() (u64& value) override;
    void operator() (const u64& value) override;
    void operator() (float& value) override;
    void operator() (const float& value) override;
    void operator() (double& value) override;
    void operator() (const double& value) override;

private:
    rapidjson::OStreamWrapper _osw;
    rapidjson::Writer<rapidjson::OStreamWrapper> _writer;
};





struct JsonDeserializer : public Serializer
{
    JsonDeserializer(std::istream& in);
	~JsonDeserializer();

    bool isDeserializer() const override
    {
        return true;
    }

    void beginObject(const std::string& s) override;
    void beginObject(const size_t index) override;
    void endObject() override;
    // deserializers need to implement this
    size_t beginArray(const std::string& s) override;
    void endArray() override;

    // Serializer interface
public:
    void operator ()(std::string& value, const std::string& s) override;
    void operator ()(const std::string&, const std::string&) override {}
    void operator ()(u8& value, const std::string& s) override;
    void operator ()(const u8&, const std::string&) override {}
    void operator ()(u32& value, const std::string& s) override;
    void operator ()(const u32&, const std::string&) override {}
    void operator ()(u64& value, const std::string& s) override;
    void operator ()(const u64&, const std::string&) override {}
    void operator ()(float&, const std::string&) override;
    void operator ()(const float&, const std::string&) override {}
    void operator ()(double& value, const std::string& s) override;
    void operator ()(const double& value, const std::string& s) override {}

    void operator ()(std::string& value) override;
    void operator ()(const std::string&) override {}
    void operator ()(u8& value) override;
    void operator ()(const u8&) override {}
    void operator ()(u32& value) override;
    void operator ()(const u32&) override {}
    void operator ()(u64& value) override;
    void operator ()(const u64&) override {}
    void operator ()(float& value) override;
    void operator ()(const float& value) override {}
    void operator ()(double& value) override;
    void operator ()(const double& value) override {}

private:
    rapidjson::IStreamWrapper _isw;
    std::vector<const rapidjson::Value*> _stack;
    rapidjson::Document _document;


};
} // hq namespace
