#pragma once

#include "../../../Lib/Math/Math.h"

#include <vector>
class LightManager
{
	struct DirectionalLightData {
		SMath::Vector3 direction;
		float intensity;
		SMath::Vector4 KaSpecPowKsX;
	};

	struct PointLightData {
		SMath::Vector3 position;
		float intensity;
	};
public:
	DirectionalLightData dirLight;
	std::vector<PointLightData> pointLights;
};

