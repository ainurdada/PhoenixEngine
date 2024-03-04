#pragma once

#include "../../Lib/Math/Math.h"
#include "../../Engine/GraphicsEngine/Mesh.h"

namespace Basic {
	class Sphere
	{
	public:
		static Mesh& Create(float radius);
	};
}
