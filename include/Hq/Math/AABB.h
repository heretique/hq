#pragma once

#include "Ray.h"
#include "Vector.h"
namespace hq
{
namespace math
{
    template <typename T>
    class AABB
    {
    public:
        typedef Vector<T, 3> VectorType;
        typedef Ray<T>       RayType;

        AABB() {}
        AABB(VectorType min, VectorType max)
            : _min(min)
            , _max(max)
        {
        }

        VectorType min() const
        {
            return _min;
        }
        VectorType max() const
        {
            return _max;
        }

        bool hit(const RayType& rayIn, float tMin, float tMax) const
        {
            for (int i = 0; i < 3; ++i)
            {
                float invD = 1.f / rayIn.direction()[i];
                float t0   = (_min[i] - rayIn.origin()[i]) * invD;
                float t1   = (_max[i] - rayIn.origin()[i]) * invD;
                if (invD < 0.f)
                    std::swap(t0, t1);
                tMin = t0 > tMin ? t0 : tMin;
                tMax = t1 < tMax ? t1 : tMax;
                if (tMax <= tMin)
                    return false;
            }
            return true;
        }

        // more efficient hit test
        //    bool slabs(VectorType p0, VectorType p1, VectorType rayOrigin, VectorType invRayDir)
        //    {
        //        VectorType t0   = (p0 - rayOrigin) * invRayDir;
        //        VectorType t1   = (p1 - rayOrigin) * invRayDir;
        //        VectorType tmin = std::min(t0, t1), tmax = std::max(t0, t1);
        //        return max_component(tmin) <= min_component(tmax);
        //    }

    private:
        VectorType _min;
        VectorType _max;
    };

    using AABBf = AABB<float>;

}  // namespace math
}  // namespace hq
