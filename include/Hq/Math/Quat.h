#include "MathTypes.h"

namespace hq
{
namespace math
{
    ///////////////////// Quaternion /////////////////////////////////////

    bool  isZero(const Quat& q);
    bool  isIdentity(const Quat& q);
    Quat  createFromEuler(float yaw, float pitch, float roll);
    void  createFromEuler(float yaw, float pitch, float roll, Quat& dst);
    Quat  createFromRotationMatrix(const Mat4x4& m);
    void  createFromRotationMatrix(const Mat4x4& m, Quat& dst);
    Quat  createFromAxisAngle(const Vec3& axis, float angle);
    void  createFromAxisAngle(const Vec3& axis, float angle, Quat& dst);
    Quat  conjugate(const Quat& q);
    void  conjugate(const Quat& q, Quat& dst);
    void  conjugate(Quat& q);
    void  toEuler(const Quat& q, float& yaw, float& pitch, float& roll);
    Quat  invert(const Quat& q);
    void  invert(const Quat& q, Quat& dst);
    void  invert(Quat& q);
    Quat  mul(const Quat& q1, const Quat& q2);
    void  mul(const Quat& q1, const Quat& q2, Quat& dst);
    Quat  normalize(const Quat& q);
    void  normalize(const Quat& q, Quat& dst);
    void  normalize(Quat& q);
    Vec3  rotatePoint(const Vec3& point, const Quat& q);
    void  rotatePoint(const Vec3& point, const Quat& q, Vec3& dst);
    float quatToAxisAngle(const Quat& q, Vec3& dst);
    void  quatToAxisAngle(const Quat& q, Vec3& dst, float& angle);
    Quat  lerp(const Quat& q1, const Quat& q2, float t);
    void  lerp(const Quat& q1, const Quat& q2, float t, Quat& dst);
    Quat  slerp(const Quat& q1, const Quat& q2, float t);
    void  slerp(const Quat& q1, const Quat& q2, float t, Quat& dst);
    Quat  squad(const Quat& q1, const Quat& q2, const Quat& s1, const Quat& s2, float t);
    void  squad(const Quat& q1, const Quat& q2, const Quat& s1, const Quat& s2, float t, Quat& dst);
}
}
