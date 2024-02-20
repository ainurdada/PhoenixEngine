#pragma once
class GameObject;

#include "GameComponent.h"
#include "vector"

class GameObject
{
public:
	void AddComponent(GameComponent& component);
	void Draw();
public:
	std::vector<GameComponent*> components;
};

