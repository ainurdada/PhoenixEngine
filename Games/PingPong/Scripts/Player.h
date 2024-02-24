#pragma once

#include "../PingPongGame.h"

class Player : public BehaviourScript
{
public:
	Player() {};

	SMath::Vector3 startPosition;
	unsigned score;
	bool isEnemy = false;

	// Inherited via GameComponent
	void DestroyResources() override;
	void Reload() override;
	void Update() override;
	void Awake() override;
	void Start() override;
};

