#pragma once

#include "../../../Engine/GameplayEngine/GameComponents/GameComponent.h"
#include "../../../App/Game.h"
#include "../../../Engine/InputSystem/InputDevice.h"

class Player : public GameComponent
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
};

