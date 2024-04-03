#pragma once
class GameObject;

#define GAMEOBJECT_H

#include <vector>
#include "GameComponents/GameComponent.h"
#include "Transform.h"



class GameObject
{
	friend class Game;
	friend class ShadowMap;
public:
	GameObject() {};

	void AddComponent(GameComponent& component);

	template <typename T>
	void RemoveComponent();

	template <typename T>
	T* GetComponent();

private:
	void Awake();
	void Start();
	void Draw();
	void DrawShadow(LightCamera* lightCamera);
	void Update(float deltaTime);
	void FixedUpdate();
	void Release();
	void Initialize();

public:
	Transform transform;
	std::vector<GameComponent*> components = {};
};

#include "GameObject.hpp"