#pragma once
#include "Vector3.h"

struct Quaternion {
	float x, y, z, w;
};

class QuatLib
{
public: // 基本的な計算
	// 積
	static Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);
	// 単位
	static Quaternion IdentityQuaternion();
	// 共役
	static Quaternion Conjugate(const Quaternion& quaternion);
	// norm
	static float Norm(const Quaternion& quaternion);
	// 正規化
	static Quaternion Normalize(const Quaternion& quaternion);
	// 逆
	static Quaternion Inverse(const Quaternion& quaternion);

	static float Dot(const Quaternion& q0, const Quaternion& q1);

	static Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);

public:
	
	/// <summary>
	/// 任意軸回転を表すQuaternion
	/// </summary>
	/// <param name="axis"></param>
	/// <param name="angle"></param>
	/// <returns></returns>
	static Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle);

};

