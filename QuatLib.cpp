﻿#include "QuatLib.h"
#include "MathCalc.h"
#include <cmath>
#include <numbers>

Quaternion QuatLib::Multiply(const Quaternion& lhs, const Quaternion& rhs)
{
    Quaternion result = {};
    result.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
    result.x = lhs.y * rhs.z - lhs.z * rhs.y + rhs.w * lhs.x + lhs.w * rhs.x;
    result.y = lhs.z * rhs.x - lhs.x * rhs.z + rhs.w * lhs.y + lhs.w * rhs.y;
    result.z = lhs.x * rhs.y - rhs.x * lhs.y + rhs.w * lhs.z + lhs.w * rhs.z;
    return result;
}

Quaternion QuatLib::IdentityQuaternion()
{
    return Quaternion(0.0f,0.0f,0.0f,1.0f);
}

Quaternion QuatLib::Conjugate(const Quaternion& quaternion)
{
    return Quaternion(-quaternion.x, -quaternion.y, -quaternion.z, quaternion.w);
}

float QuatLib::Norm(const Quaternion& quaternion)
{
    float norm = 0;
    norm = std::sqrtf(std::powf(quaternion.w, 2) + std::powf(quaternion.x, 2) + std::powf(quaternion.y, 2) + std::powf(quaternion.z, 2));
    return norm;
}

Quaternion QuatLib::Normalize(const Quaternion& quaternion)
{
    Quaternion result = {};
    float length = Norm(quaternion);
    if (length != 0) {
        result.w = quaternion.w / length;
        result.x = quaternion.x / length;
        result.y = quaternion.y / length;
        result.z = quaternion.z / length;
    }
    return result;
}

Quaternion QuatLib::Inverse(const Quaternion& quaternion)
{
    Quaternion result = Conjugate(quaternion);
    float length = std::powf(Norm(quaternion), 2);

    if (length != 0) {
        result.x /= length;
        result.y /= length;
        result.z /= length;
        result.w /= length;
    }

    //Quaternion
    return result;
}

float QuatLib::Dot(const Quaternion& q0, const Quaternion& q1)
{
    return ((q0.x * q1.x) + (q0.y * q1.y) + (q0.z * q1.z) + (q0.w * q1.w));
}

Quaternion QuatLib::Slerp(const Quaternion& q0, const Quaternion& q1, float t)
{
    Quaternion quat0 = q0;
    Quaternion quat1 = q1;
    float dot = Dot(q0, q1);
    if (dot < 0) {
        quat0 = Scaler(q0, -1.0f);
        dot *= -1.0f;
    }
    // なす角
    float theta = std::acosf(dot);

    float scale0 = std::sinf((1 - t) * theta) / std::sinf(theta);
    float scale1 = std::sinf(t * theta) / std::sinf(theta);

    return Add(Scaler(q0, scale0), Scaler(q1, scale1));
}

Quaternion QuatLib::Scaler(const Quaternion& q, float scaler)
{
    return Quaternion(q.x * scaler, q.y * scaler, q.z * scaler, q.w * scaler);
}

Quaternion QuatLib::Add(const Quaternion& q0, const Quaternion& q1)
{
    return Quaternion(q0.x + q1.x, q0.y + q1.y, q0.z + q1.z, q0.w + q1.w);
}

Quaternion QuatLib::MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle)
{
    Quaternion result = {};
    result.w = std::cosf(angle / 2.0f);
    result.x = /*std::cosf(angle / 2.0f) + */std::sinf(angle / 2.0f) * axis.x;
    result.y = /*std::cosf(angle / 2.0f) + */std::sinf(angle / 2.0f) * axis.y;
    result.z = /*std::cosf(angle / 2.0f) + */std::sinf(angle / 2.0f) * axis.z;
    return result;
}
