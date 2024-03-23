#pragma once

#include "../../../Lib/Math/Math.h"

class LightManager
{
	struct DirectionalLightData {
		SMath::Vector3 direction;
		float intensity;
		SMath::Vector4 KaSpecPowKsX;
	};
public:
	DirectionalLightData dirLight;
};

