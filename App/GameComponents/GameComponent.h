#pragma once
class GameComponent;

#include "../GameObject.h"

class GameComponent
{
public:
	virtual void DestroyResources() = 0;
	virtual void Draw() = 0;
	virtual void Initialize() = 0;
	virtual void Reload() = 0;
	virtual void Update() = 0;
public:
	GameObject* gameObject;
};

