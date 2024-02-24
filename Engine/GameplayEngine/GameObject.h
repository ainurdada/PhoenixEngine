#pragma once
class GameObject;

#define GAMEOBJECT_H

#include "vector"
#include "GameComponents/GameComponent.h"
#include "../../Lib/Math/Math.h"
#include "../../App/Game.h"

struct Transform {
	SMath::Vector3 position = { 0,0,0 };
	//SMath::Vector3 scale = { 1,1,1 };
	//SMath::Quaternion rotation = SMath::Quaternion::Identity;
};

class GameObject
{
	friend class Game;
public:
	void AddComponent(GameComponent& component);
private:
	void Awake();
	void Start();
	void Draw();
	void Update(float deltaTime);
	void Release();
	void Initialize();

public:
	Transform transform;
	std::vector<GameComponent*> components;
};

