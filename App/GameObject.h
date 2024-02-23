#pragma once
class GameObject;

#include "vector"
#include "GameComponents/GameComponent.h"
#include "GameComponents/TransformComponent.h"

class GameObject
{
public:
	void AddComponent(GameComponent& component);
	void Draw();
	void Update(float deltaTime);

	TransformComponent transform;
public:
	std::vector<GameComponent*> components;
};

