#pragma once

#include <cmath>

namespace hq
{
inline float fpart(float v)
{
    return v - std::floor(v);
}

inline float rfpart(float v)
{
    return 1 - fpart(v);
}

inline bool cmpf(float a, float b, float epsilon)
{
    return fabs(a - b) < epsilon;
}
}  // namespace hq
