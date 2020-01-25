#pragma once

#include <string>
#include <sstream>
#include <memory>
#include <unordered_map>


struct BinarySerializer
{
    BinarySerializer(std::ostream& out) : m_out(out) {}
    ~BinarySerializer() {}

    template <typename Serializable>
    inline void operator () (Serializable& serializable)
    {
        serializable.Serialize(*this);
    }

    template <typename Serializable>
    inline void operator () (const Serializable& serializable)
    {
        const_cast<Serializable&>(serializable).Serialize(*this);
    }

    template <typename Serializable>
    inline void operator () (Serializable& serializable, const std::string& s)
    {
        serializable.Serialize(*this);
    }

    template <typename Serializable>
    inline void operator () (const Serializable& serializable, const std::string& s)
    {
        const_cast<Serializable&>(serializable).Serialize(*this);
    }

    template <>
    inline void operator() (std::string& value, const std::string& s)
    {
        size_t len = value.length();
        m_out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        if (len)
            m_out.write(value.c_str(), len);
    }

    template <>
    inline void operator() (const std::string& value, const std::string& s)
    {
        size_t len = value.length();
        m_out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        if (len)
            m_out.write(value.c_str(), len);
    }
    template <>
    inline void operator() (uint8_t& value, const std::string& s)
    {
        m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
    template <>
    inline void operator() (const uint8_t& value, const std::string& s)
    {
        m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
    template <>
    inline void operator() (uint32_t& value, const std::string& s)
    {
        m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
    template <>
    inline void operator() (const uint32_t& value, const std::string& s)
    {
        m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
    template <>
    inline void operator() (uint64_t& value, const std::string& s)
    {
        m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
    template <>
    inline void operator() (const uint64_t& value, const std::string& s)
    {
        m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
    template <>
    inline void operator() (float& value, const std::string& s)
    {
        m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
    template <>
    inline void operator() (double& value, const std::string& s)
    {
        m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }

    template <typename Key, typename Type>
    inline void operator() (std::unordered_map<Key, Type>& value, const std::string& s)
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
    inline void operator() (std::unique_ptr<Type>& value, const std::string& s)
    {
        assert(value);
        (*this)(*value, s);
    }

private:
    std::ostream& m_out;
};


struct BinaryDeserializer
{
    BinaryDeserializer(std::istream& in) : m_in(in) {};
    ~BinaryDeserializer() {}

    template <typename Serializable>
    inline void operator () (Serializable& serializable)
    {
        serializable.Serialize(*this);
    }

    template <typename Serializable>
    inline void operator () (Serializable& serializable, const std::string& s)
    {
        serializable.Serialize(*this);
    }

    template <typename Key, typename Type>
    inline void operator() (std::unordered_map<Key, Type>& value, const std::string& s)
    {
        size_t count = 0;
        m_in.read(reinterpret_cast<char*>(&count), sizeof(count));
        for (size_t i = 0; i < count; ++i)
        {
            Key k;
            Type v;
            (*this)(k, "key");
            (*this)(v, "value");
            value.insert(std::make_pair(k, v));
        }
    }

    template <class Type>
    inline void operator() (std::unique_ptr<Type>& serializable)
    {
        serializable = std::make_unique<Type>();
        serializable->Serialize(*this);
    }

    template <class Type>
    inline void operator() (std::unique_ptr<Type>& value, const std::string& s)
    {
        assert(value);
        (*this)((*value.get()), s);
    }

    template <>
    inline void operator() (std::string& value, const std::string& s)
    {
        size_t len = 0;
        m_in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (len)
        {
            std::vector<char> tmp(len);
            m_in.read(tmp.data(), len); // deserialize characters of string
            value.assign(tmp.data(), len);
        }
    }
    template <>
    inline void operator() (uint8_t& value, const std::string& s)
    {
        value = 0;
        m_in.read(reinterpret_cast<char*>(&value), sizeof(value));
    }
    template <>
    inline void operator() (uint32_t& value, const std::string& s)
    {
        value = 0;
        m_in.read(reinterpret_cast<char*>(&value), sizeof(value));
    }
    template <>
    inline void operator() (uint64_t& value, const std::string& s)
    {
        value = 0;
        m_in.read(reinterpret_cast<char*>(&value), sizeof(value));
    }
    template <>
    inline void operator() (float& value, const std::string& s)
    {
        value = 0.f;
        m_in.read(reinterpret_cast<char*>(&value), sizeof(value));
    }
    template <>
    inline void operator() (double& value, const std::string& s)
    {
        value = 0.0;
        m_in.read(reinterpret_cast<char*>(&value), sizeof(value));
    }
private:
    std::istream& m_in;
};
