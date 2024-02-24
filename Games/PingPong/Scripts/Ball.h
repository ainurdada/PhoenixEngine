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
};

