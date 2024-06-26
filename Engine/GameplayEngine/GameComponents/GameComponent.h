//#pragma once
#ifndef GAME_COMPONENT_DECLARATION
#define GAME_COMPONENT_DECLARATION
class GameComponent;
#endif 

#include "../GameObject.h"
#include "Collider.h"
#include "../../GraphicsEngine/Light/LightCamera.h"

#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H
class GameComponent
{
	friend class GameObject;

protected:
	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void DestroyResources() = 0;
	virtual void Draw() = 0;
	virtual void DrawShadow(LightCamera* lightCamera) {};
	virtual void Initialize() = 0;
	virtual void Reload() = 0;
public:
	virtual void OnCollide(Collider* other) {};
	/// <summary>
	/// The game object that this component is linked to
	/// </summary>
	GameObject* gameObject = nullptr;
	bool isEnable = true;
};
#endif 

