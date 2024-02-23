#pragma once
class GameObject;

#define GAMEOBJECT_H

#include "vector"
#include "GameComponents/GameComponent.h"
#include "../../Lib/Math/Math.h"

struct Transform {
	SMath::Vector3 position = { 0.0f, 0.0f, 0.0f };
};

class GameObject
{
public:
	void AddComponent(GameComponent& component);
	void Draw();
	void Update(float deltaTime);
	void Release();

	Transform transform;
public:
	std::vector<GameComponent*> components;
};

