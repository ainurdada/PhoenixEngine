#pragma once
class GameObject;

#include "GameComponents/GameComponent.h"
#include "vector"

class GameObject
{
public:
	void AddComponent(GameComponent& component);
	void Draw();
public:
	std::vector<GameComponent*> components;
};

