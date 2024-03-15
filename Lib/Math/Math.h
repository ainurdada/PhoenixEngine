#pragma once

#include "src/Vec.h"

//#include "../../Inc/DirectXTK-main/Inc/SimpleMath.h"

#include <SimpleMath.h>

namespace SMath = DirectX::SimpleMath;

typedef DirectX::SimpleMath::Vector4 Vec4;

#define DEG_TO_RAD 0.017453
#define RAD_TO_DEG 57.29578

inline bool SameDirection(const SMath::Vector3& a, const SMath::Vector3& b)
{
	return a.Dot(b) > 0;
}