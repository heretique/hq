#pragma once

#include "Hq/BasicTypes.h"

#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <entt/fwd.hpp>

namespace hq
{
/// Binary serializer that uses visitor pattern for serialization.
/// Does not support versioning. If fields change in the `Serialize` method the binary archives
/// becom obsolete.
/// Use a member templated `Serialize` method to define members to be serialized
/// template <class Serializer>
/// void Serialize(Serializer& serializer)
/// {
///     SERIALIZE(data);
/// }
struct BinarySerializer
{
    BinarySerializer(std::ostream& out)
        : m_out(out)
    {
    }
    ~BinarySerializer() { }

    template <typename Serializable>
    inline void operator()(Serializable& serializable)
    {
        serializable.Serialize(*this);
    }

    template <typename Serializable>
    inline void operator()(const Serializable& serializable)
    {
        const_cast<Serializable&>(serializable).Serialize(*this);
    }

    template <typename Serializable>
    inline void operator()(Serializable& serializable, const std::string& s)
    {
        serializable.Serialize(*this);
    }

    template <typename Serializable>
    inline void operator()(const Serializable& serializable, const std::string& s)
    {
        const_cast<Serializable&>(serializable).Serialize(*this);
    }

    template <typename Key, typename Type>
    inline void operator()(std::unordered_map<Key, Type>& value, const std::string& s)
    {
        size_t size = value.size();
        m_out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (auto& pair : value)
        {
            (*this)(pair.first, "key");
            (*this)(pair.second, "value");
        }
    }

    template <class Type>
    inline void operator()(std::unique_ptr<Type>& value, const std::string& s)
    {
        assert(value);
        (*this)(*value, s);
    }

    template <typename T, size_t N>
    inline void operator()(T (&array)[N], const std::string& s)
    {
        size_t size = N;
        m_out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (size_t i = 0; i < N; ++i)
        {
            T& value = array[i];
            (*this)(value);
        }
    }

    void operator()(std::string& value, const std::string& s);
    void operator()(const std::string& value, const std::string& s);
    void operator()(int& value, const std::string& s);
    void operator()(const int& value, const std::string& s);
    void operator()(u8& value, const std::string& s);
    void operator()(const u8& value, const std::string& s);
    void operator()(u32& value, const std::string& s);
    void operator()(const u32& value, const std::string& s);
    void operator()(u64& value, const std::string& s);
    void operator()(const u64& value, const std::string& s);
    void operator()(float& value, const std::string& s);
    void operator()(const float& value, const std::string& s);
    void operator()(double& value, const std::string& s);
    void operator()(const double& value, const std::string& s);
    void operator()(entt::entity& value, const std::string& s);
    void operator()(const entt::entity& value, const std::string& s);

    void operator()(std::string& value);
    void operator()(const std::string& value);
    void operator()(int& value);
    void operator()(const int& value);
    void operator()(u8& value);
    void operator()(const u8& value);
    void operator()(u32& value);
    void operator()(const u32& value);
    void operator()(u64& value);
    void operator()(const u64& value);
    void operator()(float& value);
    void operator()(const float& value);
    void operator()(double& value);
    void operator()(const double& value);
    void operator()(entt::entity& value);
    void operator()(const entt::entity& value);

private:
    std::ostream& m_out;
};

/// Binary deserializer that uses visitor pattern for deserialization.
/// Does not support versioning. If fields change in the `Serialize` method the binary archives
/// becom obsolete.
/// Use a member templated `Serialize` method to define members to be serialized
/// template <class Serializer>
/// void Serialize(Serializer& serializer)
/// {
///     SERIALIZE(data);
/// }
struct BinaryDeserializer
{
    BinaryDeserializer(std::istream& in)
        : m_in(in) {};
    ~BinaryDeserializer() { }

    template <typename Serializable>
    inline void operator()(Serializable& serializable)
    {
        serializable.Serialize(*this);
    }

    template <typename Serializable>
    inline void operator()(Serializable& serializable, const std::string& s)
    {
        serializable.Serialize(*this);
    }

    template <typename Key, typename Type>
    inline void operator()(std::unordered_map<Key, Type>& value, const std::string& s)
    {
        size_t count = 0;
        m_in.read(reinterpret_cast<char*>(&count), sizeof(count));
        for (size_t i = 0; i < count; ++i)
        {
            Key  k;
            Type v;
            (*this)(k, "key");
            (*this)(v, "value");
            value.insert(std::make_pair(k, v));
        }
    }

    template <class Type>
    inline void operator()(std::unique_ptr<Type>& serializable)
    {
        serializable = std::make_unique<Type>();
        serializable->Serialize(*this);
    }

    template <class Type>
    inline void operator()(std::unique_ptr<Type>& value, const std::string& s)
    {
        assert(value);
        (*this)((*value.get()), s);
    }

    template <typename T, size_t N>
    inline void operator()(T (&array)[N], const std::string& s)
    {
        size_t count = 0;
        m_in.read(reinterpret_cast<char*>(&count), sizeof(count));
        assert(count == N);
        for (size_t i = 0; i < count; ++i)
        {
            T& value = array[i];
            (*this)(value);
        }
    }

    void operator()(std::string& value, const std::string& s);
    void operator()(int& value, const std::string& s);
    void operator()(u8& value, const std::string& s);
    void operator()(u32& value, const std::string& s);
    void operator()(u64& value, const std::string& s);
    void operator()(float& value, const std::string& s);
    void operator()(double& value, const std::string& s);
    void operator()(entt::entity& value, const std::string& s);

    void operator()(std::string& value);
    void operator()(int& value);
    void operator()(u8& value);
    void operator()(u32& value);
    void operator()(u64& value);
    void operator()(float& value);
    void operator()(double& value);
    void operator()(entt::entity& value);

private:
    std::istream& m_in;
};

}  // hq namespace
