#pragma once
#include "../PingPongGame.h"

class Ball : public BehaviourScript
{
	// Inherited via BehaviourScript
	void Awake() override;
	void Update() override;
	void DestroyResources() override;
	void Reload() override;
	void Start() override;

public:
	RenderComponent renderComponent;
};

