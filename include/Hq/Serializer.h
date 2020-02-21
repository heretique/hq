#pragma once

#include "Hq/BasicTypes.h"
#include "Hq/Serializable.h"
#include <memory>
#include <string>
#include <istream>
#include <ostream>
#include <vector>
#include <unordered_map>

namespace hq
{

class Serializer
{
public:
    virtual ~Serializer() {}

    virtual bool isDeserializer() const = 0;

    virtual void operator() (std::string& value, const std::string& s) = 0;
    virtual void operator() (const std::string& value, const std::string& s) = 0;
    virtual void operator() (u8& value, const std::string& s) = 0;
    virtual void operator() (const u8& value, const std::string& s) = 0;
    virtual void operator() (u32& value, const std::string& s) = 0;
    virtual void operator() (const u32& value, const std::string& s) = 0;
    virtual void operator() (u64& value, const std::string& s) = 0;
    virtual void operator() (const u64& value, const std::string& s) = 0;
    virtual void operator() (float& value, const std::string& s) = 0;
    virtual void operator() (const float& value, const std::string& s) = 0;
    virtual void operator() (double& value, const std::string& s) = 0;
    virtual void operator() (const double& value, const std::string& s) = 0;

    virtual void operator() (std::string& value) = 0;
    virtual void operator() (const std::string& value) = 0;
    virtual void operator() (u8& value) = 0;
    virtual void operator() (const u8& value) = 0;
    virtual void operator() (u32& value) = 0;
    virtual void operator() (const u32& value) = 0;
    virtual void operator() (u64& value) = 0;
    virtual void operator() (const u64& value) = 0;
    virtual void operator() (float& value) = 0;
    virtual void operator() (const float& value) = 0;
    virtual void operator() (double& value) = 0;
    virtual void operator() (const double& value) = 0;

    // Check usage in the templated call operators to understand
    // how the folliwing need to be implements in serializers or deserializers
    virtual void beginObject(const std::string& s) = 0;
    virtual void beginObject(const size_t index) {};
    virtual void endObject() = 0;
    // serializers need to implement this
    virtual void beginArray(const std::string& s, const size_t count){}
    // deserializers need to implement this
    virtual size_t beginArray(const std::string& s) { return 0; }
    virtual void endArray() = 0;


    void operator() (Serializable& serializable)
    {
        beginObject("");
        serializable.Serialize(*this);
        endObject();
    }

    void operator() (Serializable& serializable, const std::string& s)
    {
        beginObject(s);
        serializable.Serialize(*this);
        endObject();
    }

    template <typename K, typename T>
    inline void operator() (std::unordered_map<K, T>& value, const std::string& s)
    {
        if (isDeserializer())
        {
            size_t count = beginArray(s);
            for (size_t i = 0;  i < count; ++i)
            {
                beginObject(i);
                K key;
                T mapVal;
                (*this)(key, "key");
                (*this)(mapVal, "value");
                value.insert(std::make_pair(std::move(key), std::move(mapVal)));
                endObject();
            }
            endArray();
        }
        else
        {
            beginArray(s, value.size());
            for (auto &pair: value)
            {
                beginObject("");
                (*this)(pair.first, "key");
                (*this)(pair.second, "value");
                endObject();
            }
            endArray();
        }
    }

    template <typename T>
    inline void operator() (std::unique_ptr<T>& value, const std::string& s)
    {
        if (isDeserializer())
        {
            value = std::make_unique<T>();
        }

        (*this)(*value, s);
    }

    template <typename T>
    inline void operator() (std::vector<T>& container, const std::string& s)
    {
        if (isDeserializer())
        {
            size_t count = beginArray(s);
            for (size_t i = 0;  i < count; ++i)
            {
                if (std::is_class_v<T>)
                {
                    beginObject(i);
                }
                T value;
                (*this)(value);
                container.emplace_back(value);
                if (std::is_class_v<T>)
                {
                    endObject();
                }
            }
            endArray();
        }
        else
        {
            beginArray(s, container.size());
            for (auto &value: container)
            {
                if (std::is_class_v<T>)
                {
                    beginObject("");
                }
                (*this)(value);
                if (std::is_class_v<T>)
                {
                    endObject();
                }
            }
            endArray();
        }
    }
};

} // hq namespace
