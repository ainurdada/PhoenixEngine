#pragma once

#include "../KatamariGame.h"
#include "CameraControl.h"

class Player : public BehaviourScript
{
	void Awake() override;
	void Update() override;
	void Draw() override;

public:
	CameraControl* playerCamera;
	float moveSpeed = 5.0f;
};

