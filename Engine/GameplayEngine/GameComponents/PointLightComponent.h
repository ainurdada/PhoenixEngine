#pragma once

#include "GameComponent.h"

class PointLightComponent : public GameComponent
{
public:
	SMath::Vector3 color;
	float intensity;
	float attenuation_a = 1.0f;
	float attenuation_b = 0.1f;
	float attenuation_c = 0.1f;
private:
	int index;


	// Inherited via GameComponent
	void Awake() override;
	void Start() override;
	void Update() override;
	void FixedUpdate() override;
	void DestroyResources() override;
	void Draw() override;
	void Initialize() override;
	void Reload() override;
};

