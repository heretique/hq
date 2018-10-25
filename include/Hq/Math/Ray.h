#pragma once

#include "vector.h"
namespace hq
{
namespace math
{
    template <typename T>
    class Ray
    {
    public:
        typedef Vector<T, 3> VectorType;

        Ray() {}
        Ray(const VectorType& origin, const VectorType& direction, float time = 0.f)
            : _origin(origin)
            , _direction(normalize(direction))
            , _time(time)
        {
        }

        VectorType origin() const
        {
            return _origin;
        }

        void setOrigin(const VectorType& origin)
        {
            _origin = origin;
        }

        VectorType direction() const
        {
            return _direction;
        }

        void setDirection(const VectorType& direction)
        {
            _direction = direction;
        }

        VectorType pointOnRay(float distance) const
        {
            return _origin + distance * _direction;
        }

        float time() const
        {
            return _time;
        }

        void setTime(float time)
        {
            _time = time;
        }

    private:
        VectorType _origin;
        VectorType _direction;
        float      _time;
    };

    using Rayf = Ray<float>;
}  // namespace math
}  // namespace hq
