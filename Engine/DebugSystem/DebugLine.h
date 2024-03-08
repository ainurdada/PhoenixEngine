#pragma once

#include <directxmath.h>

namespace Debug 
{
	class DebugLine
	{
	public:
		static void Draw(const DirectX::XMFLOAT3& from, const DirectX::XMFLOAT3& to, const DirectX::XMFLOAT3& color);
	};
}

