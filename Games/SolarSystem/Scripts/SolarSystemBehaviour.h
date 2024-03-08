#pragma once
#include "../SolarSystem.h"
#include "CameraControl.h"
#include <vector>

class SolarSystemBehaviour : public BehaviourScript
{
	void Awake() override;
	void Update() override;
	void Draw() override;

	std::vector<GameObject*> planets;
	int focusIndex;
	CameraControl* cameraControl;

	bool isPressed;
};

