#pragma once
class GameObject;

#define GAMEOBJECT_H

#include <vector>
#include "GameComponents/GameComponent.h"
#include "Transform.h"



class GameObject
{
	friend class Game;
public:
	GameObject() {};

	void AddComponent(GameComponent& component);

	template <typename T>
	T* GetComponent();

private:
	void Awake();
	void Start();
	void Draw();
	void Update(float deltaTime);
	void FixedUpdate();
	void Release();
	void Initialize();

public:
	Transform transform;
	std::vector<GameComponent*> components = {};
};

#include "GameObject.hpp"