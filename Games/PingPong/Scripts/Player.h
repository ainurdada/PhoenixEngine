#pragma once

#include "../PingPongGame.h"

class Player : public BehaviourScript
{
public:
	Player() {};

	SMath::Vector3 startPosition = { 0.0f, 0.0f, 0.0f };
	SMath::Vector2 size = { 0.05f, 0.2f };
	float speed = 0.5f;
	unsigned score = 0;
	bool isEnemy = false;

	// Inherited via GameComponent
	void DestroyResources() override;
	void Reload() override;
	void Update() override;
	void Awake() override;
	void Start() override;
};

