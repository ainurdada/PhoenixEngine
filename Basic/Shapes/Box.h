#pragma once
#include "../../Lib/Math/Math.h"
#include "../../Engine/GraphicsEngine/Mesh.h"

namespace Basic {
	class Box
	{
	public:
		static Mesh& Create(SMath::Vector3& extents, SMath::Vector3& color);
	};
}