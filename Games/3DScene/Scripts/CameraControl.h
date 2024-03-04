#pragma once
#include "../Scene3DTest.h"

class CameraControl : public BehaviourScript {
	// Inherited via BehaviourScript
	void Awake() override;
	void Start() override;
	void Update() override;
	void FixedUpdate() override;
	void DestroyResources() override;
	void Reload() override;

	float moveSpeed = 5.0f;
	float mouseSensevity = 1.f;

	void RotateCamera(const InputDevice::MouseMoveEventArgs& args);
};
