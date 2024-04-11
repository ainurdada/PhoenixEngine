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
		SMath::Matrix viewProjection;
		SMath::Vector3 color;
		SMath::Vector3 position;
		float intensity;
		float attenuation_a;
		float attenuation_b;
		float attenuation_c;
	};
public:
	void Initialize();


	DirectionalLightData dirLight;
	std::vector<PointLightData> pointLights;
	
};

