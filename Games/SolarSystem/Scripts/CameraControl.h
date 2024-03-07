#pragma once
#include "../SolarSystem.h"

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

private:
	Vector3 centerPoint = { 0,2,0 };
	bool rotateAroundCentre = false;
	float distanceFromCenter = 10.0f;
};
