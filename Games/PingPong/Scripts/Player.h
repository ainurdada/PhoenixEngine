#pragma once

#include "../PingPongGame.h"

class Player : public BehaviourScript
{
public:
	Player() {};

	bool isEnemy = false;
	SMath::Vector3 startPosition;

	// Inherited via GameComponent
	void DestroyResources() override;
	void Reload() override;
	void Update() override;
	void Awake() override;
	void Start() override;
};

