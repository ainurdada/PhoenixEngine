#pragma once
#include "../../Lib/Math/Math.h"
#include "../../Engine/GraphicsEngine/Mesh.h"

namespace Basic {
	class Box
	{
	public:
		static Mesh& Create(GMath::Vector3& extents, GMath::Vector3& color);
	};
}