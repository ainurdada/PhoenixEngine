#pragma once
#include "../KatamariGame.h"

class CameraControl : public BehaviourScript {
	// Inherited via BehaviourScript
	void Awake() override;
	void Start() override;
	void Update() override;
	void FixedUpdate() override;
	void DestroyResources() override;
	void Reload() override;

	float moveSpeed;
	float mouseSensevity;

	void RotateCamera(const InputDevice::MouseMoveEventArgs& args);

public:
	float distanceFromCenter = 10.0f;
	Transform* player;
	bool rotateAroundCentre = false;

private:
};
