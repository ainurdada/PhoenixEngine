#pragma once

#include "../KatamariGame.h"
#include "CameraControl.h"

class Player : public BehaviourScript
{
	void Awake() override;
	void Update() override;
	void Draw() override;

	void OnCollide(Collider* other) override;
public:
	CameraControl* playerCamera;
	GameObject* skybox;
	float moveSpeed = 5.0f;
	float rotationSpeeed = 1.0f;

private:
	std::vector<Collider*> m_collidersToDelete;
};

