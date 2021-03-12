#pragma once

#include <type_traits>

namespace hq
{
template <typename E, typename = typename std::enable_if_t<std::is_enum_v<E>, void> >
class Flags
{
public:
    using U = std::underlying_type_t<E>;

    Flags(E flags)
        : _flags(static_cast<U>(flags))
    {
    }

    Flags(U flags)
        : _flags(flags)
    {
    }

    inline bool has(E e)
    {
        return _flags & static_cast<U>(e);
    }

    inline bool has(Flags f)
    {
        return _flags & f._flags;
    }

    inline Flags operator~()
    {
        return ~_flags;
    }

    inline Flags operator&(const U u)
    {
        return _flags & u;
    }

    inline Flags operator|(const U u)
    {
        return _flags | u;
    }

    inline Flags operator^(const U u)
    {
        return _flags ^ u;
    }

    inline Flags& operator&=(const U u)
    {
        _flags &= u;
        return *this;
    }

    inline Flags& operator|=(const U u)
    {
        _flags |= u;
        return *this;
    }

    inline Flags& operator^=(const U u)
    {
        _flags ^= u;
        return *this;
    }

    inline Flags operator&(const E e)
    {
        return _flags & static_cast<U>(e);
    }

    inline Flags operator|(const E e)
    {
        return _flags | static_cast<U>(e);
    }

    inline Flags operator^(const E e)
    {
        return _flags ^ static_cast<U>(e);
    }

    inline Flags& operator&=(const E e)
    {
        _flags &= static_cast<U>(e);
        return *this;
    }

    inline Flags& operator|=(const E e)
    {
        _flags |= static_cast<U>(e);
        return *this;
    }

    inline Flags& operator^=(const E e)
    {
        _flags ^= static_cast<U>(e);
        return *this;
    }

    inline Flags operator&(const Flags f)
    {
        return _flags & f._flags;
    }

    inline Flags operator|(const Flags f)
    {
        return _flags | f._flags;
    }

    inline Flags operator^(const Flags f)
    {
        return _flags ^ f._flags;
    }

    inline Flags& operator&=(const Flags f)
    {
        _flags &= f._flags;
        return *this;
    }

    inline Flags& operator|=(const Flags f)
    {
        _flags |= f._flags;
        return *this;
    }

    inline Flags& operator^=(const Flags f)
    {
        return _flags ^= f._flags;
        return *this;
    }

private:
    U _flags;
};

template <typename E>
inline std::enable_if_t<std::is_enum_v<E>, std::underlying_type_t<E> > operator&(const E lhs, const E rhs)
{
    return static_cast<std::underlying_type_t<E> >(lhs) & static_cast<std::underlying_type_t<E> >(rhs);
}

template <typename E>
inline std::enable_if_t<std::is_enum_v<E>, std::underlying_type_t<E> > operator|(const E lhs, const E rhs)
{
    return static_cast<std::underlying_type_t<E> >(lhs) | static_cast<std::underlying_type_t<E> >(rhs);
}

template <typename E>
inline std::enable_if_t<std::is_enum_v<E>, std::underlying_type_t<E> > operator^(const E lhs, const E rhs)
{
    return static_cast<std::underlying_type_t<E> >(lhs) ^ static_cast<std::underlying_type_t<E> >(rhs);
}

}