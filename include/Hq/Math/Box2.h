#include "MathTypes.h"

namespace hq
{
namespace math
{
    float width(const Box2& b);
    float height(const Box2& b);

    void moveTo(const Box2& b, const Vec2& point, Box2& dst);
    void moveTo(Box2& b, const Vec2& point);

    void merge(const Box2& b, const Vec2& point, Box2& dst);
    void merge(Box2& b, const Vec2& point);

    // int variant
    int width(const Box2i& b);
    int height(const Box2i& b);

    void moveTo(const Box2i& b, const Vec2i& point, Box2i& dst);
    void moveTo(Box2i& b, const Vec2i& point);

    void merge(const Box2i& b, const Vec2i& point, Box2i& dst);
    void merge(Box2i& b, const Vec2i& point);
}
}
