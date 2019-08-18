#pragma once

#include <algorithm>
#include <cmath>
#include <initializer_list>

namespace hq
{
namespace util
{
    static const float epsilon = 1e-6f;
}

namespace math
{
// Mixin macro for Vector members common to all specializations
#define MIXIN_VECTOR_MEMBERS(n)                               \
    /* Subscript accessors */                                 \
    T& operator[](size_t i)                                   \
    {                                                         \
        return data[i];                                       \
    }                                                         \
    const T& operator[](size_t i) const                       \
    {                                                         \
        return data[i];                                       \
    }                                                         \
    /* Constructors */                                        \
    Vector()                                                  \
        : data {}                                             \
    {                                                         \
    }                                                         \
    Vector(std::initializer_list<T> initList)                 \
    {                                                         \
        size_t m    = std::min((size_t)n, initList.size());   \
        auto   iter = initList.begin();                       \
        for (size_t i = 0; i < m; ++i)                        \
        {                                                     \
            data[i] = *iter;                                  \
            ++iter;                                           \
        }                                                     \
        /* Zero-fill any remaining elements */                \
        for (size_t i = m; i < n; ++i)                        \
            data[i] = T(0);                                   \
    }                                                         \
    explicit Vector(T a)                                      \
    {                                                         \
        for (size_t i = 0; i < n; ++i)                        \
            data[i] = a;                                      \
    }                                                         \
    template <typename U>                                     \
    explicit Vector(const U* p)                               \
    {                                                         \
        for (size_t i = 0; i < n; ++i)                        \
            data[i] = T(p[i]);                                \
    }                                                         \
    template <typename U, size_t nOther>                      \
    explicit Vector(Vector<U, nOther> v)                      \
    {                                                         \
        size_t m = std::min((size_t)n, nOther);               \
        for (size_t i = 0; i < m; ++i)                        \
            data[i] = T(v[i]);                                \
        /* Zero-fill any remaining elements */                \
        for (size_t i = m; i < n; ++i)                        \
            data[i] = T(0);                                   \
    }                                                         \
    /* C array conversions */                                 \
    typedef T(&array_t)[n];                                   \
    operator array_t()                                        \
    {                                                         \
        return data;                                          \
    }                                                         \
    typedef const T(&const_array_t)[n];                       \
    operator const_array_t() const                            \
    {                                                         \
        return data;                                          \
    }                                                         \
    /* Disallow bool conversions (without this, they'd happen \
       implicitly via the array conversions) */               \
private:                                                      \
    operator bool();                                          \
                                                              \
public:

    template <typename T, size_t Dimension>
    struct Vector
    {
        T data[Dimension];
        MIXIN_VECTOR_MEMBERS(Dimension)
    };

    template <typename T>
    struct Vector<T, 2>
    {
        union {
            T data[2];
            struct
            {
                T x, y;
            };
            struct
            {
                T u, v;
            };
        };
        MIXIN_VECTOR_MEMBERS(2)
        Vector(T vx, T vy)
            : x(vx)
            , y(vy)
        {
        }
    };

    template <typename T>
    struct Vector<T, 3>
    {
        union {
            T data[3];
            struct
            {
                T x, y, z;
            };
            struct
            {
                T r, g, b;
            };
            Vector<T, 2> xy;
        };

        MIXIN_VECTOR_MEMBERS(3)
        Vector(T vx, T vy, T vz)
            : x(vx)
            , y(vy)
            , z(vz)
        {
        }
        Vector(Vector<T, 2> v, T vz)
            : x(v.x)
            , y(v.y)
            , z(vz)
        {
        }
    };

    template <typename T>
    struct Vector<T, 4>
    {
        union {
            T data[4];
            struct
            {
                T x, y, z, w;
            };
            struct
            {
                T r, g, b, a;
            };
            Vector<T, 2> xy;
            Vector<T, 3> xyz;
            Vector<T, 3> rgb;
        };
        MIXIN_VECTOR_MEMBERS(4)
        Vector(T vx, T vy, T vz, T vw)
            : x(vx)
            , y(vy)
            , z(vz)
            , w(vw)
        {
        }
        Vector(Vector<T, 2> v, T vz, T vw)
            : x(v.x)
            , y(v.y)
            , z(vz)
            , w(vw)
        {
        }
        Vector(Vector<T, 3> v, T vw)
            : x(v.x)
            , y(v.y)
            , z(v.z)
            , w(vw)
        {
        }
    };

    using Vector2d = Vector<double, 2>;
    using Vector3d = Vector<double, 3>;
    using Vector4d = Vector<double, 4>;
    using Vector2f = Vector<float, 2>;
    using Vector3f = Vector<float, 3>;
    using Vector4f = Vector<float, 4>;
    using Vector2i = Vector<int, 2>;
    using Vector3i = Vector<int, 3>;
    using Vector4i = Vector<int, 4>;

    // Overloaded math operators

#define DEFINE_UNARY_OPERATOR(op)                            \
    template <typename T, size_t Dimension>                  \
    Vector<T, Dimension> operator op(Vector<T, Dimension> a) \
    {                                                        \
        Vector<T, Dimension> result;                         \
        for (size_t i = 0; i < Dimension; ++i)               \
            result[i] = op a[i];                             \
        return result;                                       \
    }

#define DEFINE_BINARY_OPERATORS(op)                                                  \
    /* Vector-Vector op */                                                           \
    template <typename T, size_t Dimension>                                          \
    Vector<T, Dimension> operator op(Vector<T, Dimension> a, Vector<T, Dimension> b) \
    {                                                                                \
        Vector<T, Dimension> result;                                                 \
        for (size_t i = 0; i < Dimension; ++i)                                       \
            result[i] = a[i] op b[i];                                                \
        return result;                                                               \
    }                                                                                \
    /* Scalar-Vector op */                                                           \
    template <typename T, size_t Dimension>                                          \
    Vector<T, Dimension> operator op(T a, Vector<T, Dimension> b)                    \
    {                                                                                \
        Vector<T, Dimension> result;                                                 \
        for (size_t i = 0; i < Dimension; ++i)                                       \
            result[i] = a op b[i];                                                   \
        return result;                                                               \
    }                                                                                \
    /* Vector-scalar op */                                                           \
    template <typename T, size_t Dimension>                                          \
    Vector<T, Dimension> operator op(Vector<T, Dimension> a, T b)                    \
    {                                                                                \
        Vector<T, Dimension> result;                                                 \
        for (size_t i = 0; i < Dimension; ++i)                                       \
            result[i] = a[i] op b;                                                   \
        return result;                                                               \
    }

#define DEFINE_INPLACE_OPERATORS(op)                                                   \
    /* Vector-Vector op */                                                             \
    template <typename T, size_t Dimension>                                            \
    Vector<T, Dimension>& operator op(Vector<T, Dimension>& a, Vector<T, Dimension> b) \
    {                                                                                  \
        for (size_t i = 0; i < Dimension; ++i)                                         \
            a[i] op b[i];                                                              \
        return a;                                                                      \
    }                                                                                  \
    /* Vector-scalar op */                                                             \
    template <typename T, size_t Dimension>                                            \
    Vector<T, Dimension>& operator op(Vector<T, Dimension>& a, T b)                    \
    {                                                                                  \
        for (size_t i = 0; i < Dimension; ++i)                                         \
            a[i] op b;                                                                 \
        return a;                                                                      \
    }

#define DEFINE_RELATIONAL_OPERATORS(op)                                                 \
    /* Vector-Vector op */                                                              \
    template <typename T, typename U, size_t Dimension>                                 \
    Vector<bool, Dimension> operator op(Vector<T, Dimension> a, Vector<U, Dimension> b) \
    {                                                                                   \
        Vector<bool, Dimension> result;                                                 \
        for (size_t i = 0; i < Dimension; ++i)                                          \
            result[i] = a[i] op b[i];                                                   \
        return result;                                                                  \
    }                                                                                   \
    /* Scalar-Vector op */                                                              \
    template <typename T, typename U, size_t Dimension>                                 \
    Vector<bool, Dimension> operator op(T a, Vector<U, Dimension> b)                    \
    {                                                                                   \
        Vector<bool, Dimension> result;                                                 \
        for (size_t i = 0; i < Dimension; ++i)                                          \
            result[i] = a op b[i];                                                      \
        return result;                                                                  \
    }                                                                                   \
    /* Vector-scalar op */                                                              \
    template <typename T, typename U, size_t Dimension>                                 \
    Vector<bool, Dimension> operator op(Vector<T, Dimension> a, U b)                    \
    {                                                                                   \
        Vector<bool, Dimension> result;                                                 \
        for (size_t i = 0; i < Dimension; ++i)                                          \
            result[i] = a[i] op b;                                                      \
        return result;                                                                  \
    }

    DEFINE_BINARY_OPERATORS(+)
    DEFINE_BINARY_OPERATORS(-)
    DEFINE_UNARY_OPERATOR(-)
    DEFINE_BINARY_OPERATORS(*)
    DEFINE_BINARY_OPERATORS(/)
    DEFINE_BINARY_OPERATORS(&)
    DEFINE_BINARY_OPERATORS(|)
    DEFINE_BINARY_OPERATORS(^)
    DEFINE_UNARY_OPERATOR(!)
    DEFINE_UNARY_OPERATOR(~)

    DEFINE_INPLACE_OPERATORS(+=)
    DEFINE_INPLACE_OPERATORS(-=)
    DEFINE_INPLACE_OPERATORS(*=)
    DEFINE_INPLACE_OPERATORS(/=)
    DEFINE_INPLACE_OPERATORS(&=)
    DEFINE_INPLACE_OPERATORS(|=)
    DEFINE_INPLACE_OPERATORS(^=)

    DEFINE_RELATIONAL_OPERATORS(==)
    DEFINE_RELATIONAL_OPERATORS(!=)
    DEFINE_RELATIONAL_OPERATORS(<)
    DEFINE_RELATIONAL_OPERATORS(>)
    DEFINE_RELATIONAL_OPERATORS(<=)
    DEFINE_RELATIONAL_OPERATORS(>=)

#undef DEFINE_UNARY_OPERATOR
#undef DEFINE_BINARY_OPERATORS
#undef DEFINE_INPLACE_OPERATORS
#undef DEFINE_RELATIONAL_OPERATORS

    // Other math functions

    template <typename T, size_t Dimension>
    T dot(Vector<T, Dimension> a, Vector<T, Dimension> b)
    {
        T result(0);
        for (size_t i = 0; i < Dimension; ++i)
            result += a[i] * b[i];
        return result;
    }

    template <typename T, size_t Dimension>
    T lengthSquared(Vector<T, Dimension> a)
    {
        return dot(a, a);
    }

    template <typename T, size_t Dimension>
    T length(Vector<T, Dimension> a)
    {
        return sqrt(lengthSquared(a));
    }

    template <typename T, size_t Dimension>
    Vector<T, Dimension> normalize(Vector<T, Dimension> a)
    {
        return a / length(a);
    }

    template <typename T, size_t Dimension>
    Vector<T, Dimension> pow(Vector<T, Dimension> a, float p)
    {
        Vector<T, Dimension> result;
        for (size_t i = 0; i < Dimension; ++i)
            result[i] = std::pow(a[i], p);
        return result;
    }

    template <typename T, size_t Dimension>
    Vector<bool, Dimension> isNear(Vector<T, Dimension> a, Vector<T, Dimension> b, float epsilon = util::epsilon)
    {
        Vector<bool, Dimension> result;
        for (size_t i = 0; i < Dimension; ++i)
            result[i] = isnear(a[i], b[i], epsilon);
        return result;
    }
    template <typename T, size_t Dimension>
    Vector<bool, Dimension> isNear(Vector<T, Dimension> a, T b, float epsilon = util::epsilon)
    {
        Vector<bool, Dimension> result;
        for (size_t i = 0; i < Dimension; ++i)
            result[i] = isnear(a[i], b, epsilon);
        return result;
    }
    template <typename T, size_t Dimension>
    Vector<bool, Dimension> isNear(T a, Vector<T, Dimension> b, float epsilon = util::epsilon)
    {
        Vector<bool, Dimension> result;
        for (size_t i = 0; i < Dimension; ++i)
            result[i] = isnear(a, b[i], epsilon);
        return result;
    }

    template <typename T, size_t Dimension>
    Vector<bool, Dimension> isFinite(Vector<T, Dimension> a)
    {
        Vector<bool, Dimension> result;
        for (size_t i = 0; i < Dimension; ++i)
            result[i] = isfinite(a[i]);
        return result;
    }

    template <typename T, size_t Dimension>
    Vector<size_t, Dimension> round(Vector<T, Dimension> a)
    {
        Vector<size_t, Dimension> result;
        for (size_t i = 0; i < Dimension; ++i)
            result[i] = round(a[i]);
        return result;
    }

    template <typename T>
    Vector<T, 3> cross(Vector<T, 3> a, Vector<T, 3> b)
    {
        return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x,
        };
    }

    template <typename T>
    Vector<T, 2> orthogonalVector(Vector<T, 2> a)
    {
        return {-a.y, a.x};
    }

    template <typename T>
    Vector<T, 3> orthogonalVector(Vector<T, 3> a)
    {
        // Implementation due to Sam Hocevar - see blog post:
        // https://lolengine.net/blog/2013/09/21/picking-orthogonal-Vector-combing-coconuts
        if (abs(a.x) > abs(a.z))
            return {-a.y, a.x, T(0)};
        else
            return {T(0), -a.z, a.y};
    }

    template <typename T, size_t Dimension>
    Vector<T, Dimension> slerp(Vector<T, Dimension> a, Vector<T, Dimension> b, float u)
    {
        float theta = acosf(dot(a, b));
        return (a * sinf((1.0f - u) * theta) + b * sinf(u * theta)) / sinf(theta);
    }

    // Utilities for bool Vectors

    // Any: checks if any of the values of a bool Vector is true, i.e. ORs them
    // together.
    template <size_t Dimension>
    bool any(Vector<bool, Dimension> a)
    {
        bool result = a[0];
        for (size_t i = 1; i < Dimension; ++i)
            result |= a[i];
        return result;
    }

    // All: checks if all of the values of a bool Vector are true, i.e. ANDs them
    // together.
    template <size_t Dimension>
    bool all(Vector<bool, Dimension> a)
    {
        bool result = a[0];
        for (size_t i = 1; i < Dimension; ++i)
            result &= a[i];
        return result;
    }

    // Select: ternary operator for Vectors. Selects componentwise from a or b based
    // on cond.
    template <typename T, size_t Dimension>
    Vector<T, Dimension> select(Vector<bool, Dimension> cond, Vector<T, Dimension> a, Vector<T, Dimension> b)
    {
        Vector<T, Dimension> result;
        for (size_t i = 0; i < Dimension; ++i)
            result[i] = cond[i] ? a[i] : b[i];
        return result;
    }
    template <typename T, size_t Dimension>
    Vector<T, Dimension> select(Vector<bool, Dimension> cond, T a, Vector<T, Dimension> b)
    {
        Vector<T, Dimension> result;
        for (size_t i = 0; i < Dimension; ++i)
            result[i] = cond[i] ? a : b[i];
        return result;
    }
    template <typename T, size_t Dimension>
    Vector<T, Dimension> select(Vector<bool, Dimension> cond, Vector<T, Dimension> a, T b)
    {
        Vector<T, Dimension> result;
        for (size_t i = 0; i < Dimension; ++i)
            result[i] = cond[i] ? a[i] : b;
        return result;
    }

    template <typename T, size_t Dimension>
    Vector<T, Dimension> min(Vector<T, Dimension> a, Vector<T, Dimension> b)
    {
        return select(a < b, a, b);
    }
    template <typename T, size_t Dimension>
    Vector<T, Dimension> min(T a, Vector<T, Dimension> b)
    {
        return select(a < b, a, b);
    }
    template <typename T, size_t Dimension>
    Vector<T, Dimension> min(Vector<T, Dimension> a, T b)
    {
        return select(a < b, a, b);
    }

    template <typename T, size_t Dimension>
    Vector<T, Dimension> max(Vector<T, Dimension> a, Vector<T, Dimension> b)
    {
        return select(a < b, b, a);
    }
    template <typename T, size_t Dimension>
    Vector<T, Dimension> max(T a, Vector<T, Dimension> b)
    {
        return select(a < b, b, a);
    }
    template <typename T, size_t Dimension>
    Vector<T, Dimension> max(Vector<T, Dimension> a, T b)
    {
        return select(a < b, b, a);
    }

    template <typename T, size_t Dimension>
    Vector<T, Dimension> abs(Vector<T, Dimension> a)
    {
        return select(a < T(0), -a, a);
    }

    template <typename T, size_t Dimension>
    Vector<T, Dimension> clamp(Vector<T, Dimension> value, T lower, T upper)
    {
        return min(max(value, lower), upper);
    }

    template <typename T, size_t Dimension>
    Vector<T, Dimension> saturate(Vector<T, Dimension> value)
    {
        return clamp(value, T(0), T(1));
    }

    template <typename T, size_t Dimension>
    T minComponent(Vector<T, Dimension> a)
    {
        T result = a[0];
        for (size_t i = 1; i < Dimension; ++i)
            result = min(result, a[i]);
        return result;
    }

    template <typename T, size_t Dimension>
    T maxComponent(Vector<T, Dimension> a)
    {
        T result = a[0];
        for (size_t i = 1; i < Dimension; ++i)
            result = max(result, a[i]);
        return result;
    }
}
}  // namespace hq
