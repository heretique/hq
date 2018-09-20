#pragma once

#include "Hq/Types.h"

#include <cstddef>
#include <string>

namespace hq
{
class StringHash
{
public:
    // used for unordered_map
    struct Hasher
    {
        size_t operator()(const StringHash& s) const;
    };

    StringHash();
    StringHash(const char* str);
    StringHash(const std::string& str);
    bool operator==(const StringHash& other) const;
    operator size_t() const;

    size_t hash() const;

    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(_hash);
    }

private:
    size_t _hash;
};

inline size_t StringHash::Hasher::operator()(const StringHash& s) const
{
    // StringHash objects are already hashed during creation, return hash
    return s._hash;
}

inline bool StringHash::operator==(const StringHash& other) const
{
    return _hash == other._hash;
}

inline StringHash::operator size_t() const
{
    return _hash;
}

inline u32 rotl32(u32 x, int8_t r)
{
    return (x << r) | (x >> (32 - r));
}

inline u32 getblock32(const u32* p, int i)
{
    return p[i];
}

inline u32 fmix32(u32 h)
{
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;

    return h;
}
}  // atlas namespace

namespace std
{
template <>
struct hash<hq::StringHash>
{
    size_t operator()(const hq::StringHash& s) const
    {
        return s;
    }
};
}
