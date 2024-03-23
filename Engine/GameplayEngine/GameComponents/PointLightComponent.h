#pragma once

#include "GameComponent.h"

class PointLightComponent : public GameComponent
{
public:
	float intensity;
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

