#pragma once

#include <vector>
#include "../../Lib/Math/Math.h"
#include "../../Engine/GraphicsEngine/Mesh.h"

namespace Basic {
	class Box2D
	{
	public:
		static Mesh& Create(float width, float height);
	};
}

