#pragma once

#include "../PingPongGame.h"

class Player : public BehaviourScript
{
public:
	Player() {};

	bool isEnemy = false;

	// Inherited via GameComponent
	void DestroyResources() override;
	void Draw() override;
	void Initialize() override;
	void Reload() override;
	void Update() override;
	void Awake() override;
	void Start() override;
};

