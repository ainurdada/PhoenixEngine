#pragma once

#include "../App/GameComponents/GameComponent.h"
#include "../App/Game.h"
#include "../InputSystem/InputDevice.h"

class Player : public GameComponent
{
public:
	Player() {};

	// Inherited via GameComponent
	void DestroyResources() override;
	void Draw() override;
	void Initialize() override;
	void Reload() override;
	void Update() override;
};

