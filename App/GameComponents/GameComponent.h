//#pragma once
#ifndef GAME_COMPONENT_DECLARATION
#define GAME_COMPONENT_DECLARATION
class GameComponent;
#endif 

#include "../GameObject.h"


#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H
class GameComponent
{
public:
	virtual void DestroyResources() = 0;
	virtual void Draw() = 0;
	virtual void Initialize() = 0;
	virtual void Reload() = 0;
	virtual void Update() = 0;
public:
	GameObject* gameObject = nullptr;
};
#endif 

