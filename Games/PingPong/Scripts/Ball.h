#pragma once
#include "../PingPongGame.h"

class Player;

class Ball : public BehaviourScript
{
public:
	// Inherited via BehaviourScript
	void Awake() override;
	void Update() override;
	void DestroyResources() override;
	void Reload() override;
	void Start() override;

public:
	Player* player;
	Player* enemy;

	SMath::Vector2 velocity;
	BoxCollider* col;

private:
	float speed_increase = 1.1f;
	float max_speed = 2;
	float friction = 0.5f;
	float spread = 0.9f;
};

