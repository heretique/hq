#pragma once

#include "Hq/BasicTypes.h"
#include <memory>
#include <string>
#include <istream>
#include <ostream>
#include <vector>
#include <unordered_map>
#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/document.h>
#include <entt/fwd.hpp>

namespace hq {

struct JsonSerializer
{
    JsonSerializer(std::ostream& out);
	~JsonSerializer();

	template <typename Serializable>
	inline void operator () (Serializable& serializable)
	{
        _writer.StartObject();
		serializable.Serialize(*this);
        _writer.EndObject();
	}

	template <typename Serializable>
	inline void operator () (Serializable& serializable, const std::string& s)
	{
        _writer.String(s);
        _writer.StartObject();
		serializable.Serialize(*this);
        _writer.EndObject();
	}

    template <typename K, typename T>
    inline void operator() (std::unordered_map<K, T>& value, const std::string& s)
	{
        _writer.String(s);
        _writer.StartArray();
		for (auto& pair : value)
		{
            _writer.StartObject();
			(*this)(pair.first, "key");
			(*this)(pair.second, "value");
            _writer.EndObject();
		}
        _writer.EndArray();
	}

    template <typename T>
    inline void operator() (std::unique_ptr<T>& value, const std::string& s)
	{
		(*this)(*value, s);
	}

    template <typename T>
    inline void operator() (std::vector<T>& container, const std::string& s)
    {
        _writer.String(s);
        _writer.StartArray();
        for (auto& value : container)
        {
            if (std::is_class_v<T>)
                _writer.StartObject();

            (*this)(value);

            if (std::is_class_v<T>)
                _writer.EndObject();
        }
        _writer.EndArray();
    }

    template <typename T, size_t N>
    inline void operator() (T (&array)[N], const std::string& s)
    {
        _writer.String(s);
        _writer.StartArray();
        for (size_t i = 0; i < N; ++i)
        {
            T& value = array[i];
            if (std::is_class_v<T>)
                _writer.StartObject();

            (*this)(value);

            if (std::is_class_v<T>)
                _writer.EndObject();
        }
        _writer.EndArray();
    }

	void operator() (std::string& value, const std::string& s);
	void operator() (const std::string& value, const std::string& s);
    void operator() (int& value, const std::string& s);
    void operator() (const int& value, const std::string& s);
    void operator() (u8& value, const std::string& s);
    void operator() (const u8& value, const std::string& s);
    void operator() (u32& value, const std::string& s);
    void operator() (const u32& value, const std::string& s);
    void operator() (u64& value, const std::string& s);
    void operator() (const u64& value, const std::string& s);
	void operator() (float& value, const std::string& s);
    void operator() (const float& value, const std::string& s);
	void operator() (double& value, const std::string& s);
    void operator() (const double& value, const std::string& s);
    void operator() (entt::entity& value, const std::string& s);
    void operator() (const entt::entity& value, const std::string& s);

    void operator() (std::string& value);
    void operator() (const std::string& value);
    void operator() (int& value);
    void operator() (const int& value);
    void operator() (u8& value);
    void operator() (const u8& value);
    void operator() (u32& value);
    void operator() (const u32& value);
    void operator() (u64& value);
    void operator() (const u64& value);
    void operator() (float& value);
    void operator() (const float& value);
    void operator() (double& value);
    void operator() (const double& value);
    void operator() (entt::entity& value);
    void operator() (const entt::entity& value);

private:
    rapidjson::OStreamWrapper _osw;
    rapidjson::Writer<rapidjson::OStreamWrapper> _writer;
};





struct JsonDeserializer
{
    JsonDeserializer(std::istream& in);
	~JsonDeserializer();

	template <typename Serializable>
	inline void operator () (Serializable& serializable)
	{
        if (!_document.IsObject())
			return;

        _stack.push_back(&_document);
		serializable.Serialize(*this);
        _stack.pop_back();
        assert(_stack.empty());
	}

	template <typename Serializable>
	inline void operator () (Serializable& serializable, const std::string& s)
	{
		using namespace rapidjson;
        assert(!_stack.empty());
        if (!_stack.back()->HasMember(s))
			return;

        const Value& val = (*_stack.back())[s];
		assert(val.IsObject());
        _stack.push_back(&val);
		serializable.Serialize(*this);
        _stack.pop_back();
	}

    template <typename T>
    inline void operator() (std::vector<T>& container, const std::string& s)
    {
        using namespace rapidjson;
        assert(!_stack.empty());
        if (!_stack.back()->HasMember(s))
            return;

        const Value& val = (*_stack.back())[s];
        assert(val.IsArray());
        for (SizeType i = 0; i < val.Size(); ++i)
        {
            const Value& element = val[i];
            if (std::is_class_v<T>)
            {
                assert(element.IsObject());
            }
            _stack.push_back(&element);
            T value;
            (*this)(value);
            container.emplace_back(value);
            _stack.pop_back();
        }
    }

    template <typename K, typename T>
    inline void operator() (std::unordered_map<K, T>& value, const std::string& s)
	{
		using namespace rapidjson;
        assert(!_stack.empty());
        if (!_stack.back()->HasMember(s))
			return;

        const Value& val = (*_stack.back())[s];
		assert(val.IsArray());
		for (SizeType i = 0; i < val.Size(); ++i)
		{
			const Value& element = val[i];
			assert(element.IsObject());
            _stack.push_back(&element);
            K key;
            T mapVal;
			(*this)(key, "key");
			(*this)(mapVal, "value");
			value.insert(std::make_pair(std::move(key), std::move(mapVal)));
            _stack.pop_back();
		}
	}

    template <class T>
    inline void operator() (std::unique_ptr<T>& value, const std::string& s)
	{
		using namespace rapidjson;
        assert(!_stack.empty());
        if (!_stack.back()->HasMember(s))
			return;

        const Value& val = (*_stack.back())[s];
        value = std::make_unique<T>();
		(*this)((*value.get()), s);
	}

    void operator() (std::string& value, const std::string& s);
    void operator() (int& value, const std::string& s);
    void operator() (u8& value, const std::string& s);
    void operator() (u32& value, const std::string& s);
    void operator() (u64& value, const std::string& s);
    void operator() (float& value, const std::string& s);
    void operator() (double& value, const std::string& s);
    void operator() (entt::entity& value, const std::string& s);

    void operator() (std::string& value);
    void operator() (int& value);
    void operator() (u8& value);
    void operator() (u32& value);
    void operator() (u64& value);
    void operator() (float& value);
    void operator() (double& value);
    void operator() (entt::entity& value);

private:
    rapidjson::IStreamWrapper _isw;
    std::vector<const rapidjson::Value*> _stack;
    rapidjson::Document _document;
};
} // hq namespace
