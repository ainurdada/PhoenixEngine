#pragma once

#include "GameComponent.h"
#include "../../GraphicsEngine/Light/ShadowMap.h"

#include <vector>

class PointLightComponent : public GameComponent
{
	friend class Game;
public:
	void GenerateShadowMaps(GameObject* gameObjects[], int count);
	const std::vector<LightCamera> GetCameras() const;
	const std::vector<ShadowMap> GetShadowMaps() const;

	SMath::Vector3 color;
	float intensity;
	float attenuation_a = 1.0f;
	float attenuation_b = 0.1f;
	float attenuation_c = 0.1f;
private:
	int index;
	std::vector<ShadowMap> shadow_map = std::vector<ShadowMap>(6);
	std::vector<LightCamera> cameras = std::vector<LightCamera>(6);

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

