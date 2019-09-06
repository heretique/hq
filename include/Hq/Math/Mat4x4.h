#include "MathTypes.h"

namespace hq
{
namespace math
{
    //////////////////// Mat4x4 ////////////////////////////////

    bool  isIdentity(const Mat4x4& matrix);
    void  setIdentity(Mat4x4& dst);
    void  mul(const Mat4x4& matrix, float scalar, Mat4x4& dst);
    void  mul(const Mat4x4& lhs, const Mat4x4& rhs, Mat4x4& dst);
    void  createLookAt(const Vec3& eyePosition, const Vec3& targetPosition, const Vec3& up, Mat4x4& dst);
    void  createLookAt(float eyePositionX, float eyePositionY, float eyePositionZ, float targetCenterX,
                       float targetCenterY, float targetCenterZ, float upX, float upY, float upZ, Mat4x4& dst);
    void  createPerspective(float fieldOfView, float aspectRatio, float zNearPlane, float zFarPlane, Mat4x4& dst);
    void  createOrthographic(float width, float height, float zNearPlane, float zFarPlane, Mat4x4& dst);
    void  createOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane,
                                      float zFarPlane, Mat4x4& dst);
    void  createBillboard(const Vec3& objectPosition, const Vec3& cameraPosition, const Vec3& cameraUpVector,
                          Mat4x4& dst);
    void  createBillboard(const Vec3& objectPosition, const Vec3& cameraPosition, const Vec3& cameraUpVector,
                          const Vec3& cameraForwardVector, Mat4x4& dst);
    void  createReflection(const Plane& plane, Mat4x4& dst);
    void  createScale(const Vec3& scale, Mat4x4& dst);
    void  createScale(float xScale, float yScale, float zScale, Mat4x4& dst);
    void  createRotation(const Quat& quat, Mat4x4& dst);
    void  createRotation(const Vec3& axis, float angle, Mat4x4& dst);
    void  createRotationX(float angle, Mat4x4& dst);
    void  createRotationY(float angle, Mat4x4& dst);
    void  createRotationZ(float angle, Mat4x4& dst);
    void  createFromEuler(float yaw, float pitch, float roll, Mat4x4& dst);
    void  createTranslation(const Vec3& translation, Mat4x4& dst);
    void  createTranslation(float xTranslation, float yTranslation, float zTranslation, Mat4x4& dst);
    void  decompose(const Mat4x4& matrix, Quat& rotation, Vec3& scale, Vec3& translation);
    float determinant(const Mat4x4& matrix);
    void  getScale(const Mat4x4& matrix, Vec3& scale);
    void  getRotation(const Mat4x4& matrix, Quat& rotation);
    void  getTranslation(const Mat4x4& matrix, Vec3& translation);
    void  getUp(const Mat4x4& matrix, Vec3& dst);
    void  getRight(const Mat4x4& matrix, Vec3& dst);
    void  getForward(const Mat4x4& matrix, Vec3& dst);
    bool  canInvert(const Mat4x4& matrix);
    void  invert(const Mat4x4& matrix, Mat4x4& dst);
    void  invert(Mat4x4& matrix);
    void  rotate(const Mat4x4& matrix, const Quat& rotation, Mat4x4& dst);
    void  rotate(Mat4x4& matrix, const Quat& rotation);
    void  rotate(const Mat4x4& matrix, const Vec3& axis, float angle, Mat4x4& dst);
    void  rotate(Mat4x4& matrix, const Vec3& axis, float angle);
    void  rotateX(const Mat4x4& matrix, float angle, Mat4x4& dst);
    void  rotateX(Mat4x4& matrix, float angle);
    void  rotateY(const Mat4x4& matrix, float angle, Mat4x4& dst);
    void  rotateY(Mat4x4& matrix, float angle);
    void  rotateZ(const Mat4x4& matrix, float angle, Mat4x4& dst);
    void  rotateZ(Mat4x4& matrix, float angle);
    void  scale(const Mat4x4& matrix, float scale, Mat4x4& dst);
    void  scale(const Mat4x4& matrix, float scaleX, float scaleY, float scaleZ, Mat4x4& dst);
    void  scale(const Mat4x4& matrix, const Vec3& scale, Mat4x4& dst);
    void  scale(Mat4x4& matrix, float scale);
    void  scale(Mat4x4& matrix, float scaleX, float scaleY, float scaleZ);
    void  scale(Mat4x4& matrix, const Vec3& scale);
    void  tranformPoint(const Vec3& point, const Mat4x4& matrix, Vec3& dst);
    void  tranformPoint(Vec3& point, const Mat4x4& matrix);
    void  tranform(const Vec3& v, const Mat4x4& matrix, Vec3& dst);
    void  tranform(Vec3& v, const Mat4x4& matrix);
    void  transform(const Vec4& v, const Mat4x4& matrix, Vec4& dst);
    void  transform(Vec4& v, const Mat4x4& matrix);
    void  translate(const Mat4x4& matrix, const Vec3& translation, Mat4x4& dst);
    void  translate(Mat4x4& matrix, const Vec3& translation);
    void  translate(const Mat4x4& matrix, float x, float y, float z, Mat4x4& dst);
    void  translate(Mat4x4& matrix, float x, float y, float z);
    void  transpose(const Mat4x4& matrix, Mat4x4& dst);
    void  transpose(Mat4x4& matrix);
}
}
