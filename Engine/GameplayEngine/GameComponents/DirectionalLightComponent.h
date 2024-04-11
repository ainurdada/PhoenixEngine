#pragma once

#include "GameComponent.h"
#include "../../GraphicsEngine/Light/ShadowMap.h"

class DirectionalLightComponent : public GameComponent
{

public:
	SMath::Vector3 direction;
	float intensity;
	float ambientKoeff;
	float specPow;
	float specKoeff;

private:
	ShadowMap shadow_map;

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

