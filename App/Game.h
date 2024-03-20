#pragma once
class Game;

#include "Time.h"
#include <chrono>
#include "Window.h"
#include "../Engine/GraphicsEngine/GraphicsEngine.h"
#include "../Engine/PhysicsEngine/Physics.h"
#include "../Lib/Math/Math.h"
#include "../Engine/GameplayEngine/GameObject.h"
#include <iostream>
#include "../Engine/InputSystem/InputDevice.h"
#include "../Engine/GameplayEngine/Camera.h"
#include "../Engine/DebugSystem/DebugSystem.h"

class Game
{
	friend class Collider;

public:
	Game();
	~Game();
public:
	virtual void Create();
	virtual void Run();
	virtual void InstantiateGameObject(GameObject* gameObject);
	virtual void Quit();
public:
	static Game* instance;

	bool isRun = false;

	Time time;
	LPCWSTR name = L"My game";
	Vec2Int size = Vec2Int(1920, 1080);
	Window window;
	Graphics graphics;
	InputDevice* input;
	Physics physics;
	Camera* mainCamera;

private:
	std::vector<GameObject*> gameObjects;
	virtual void processInput();
	virtual void update(float deltaTime);
	virtual void fixedUpdate();
	virtual void render(float deltaFrame);
	virtual void ClearResources();
private:
	DebugTool::Debug debug;
	HRESULT res;
	bool isExitRequested = false;

protected:
	virtual void OnCreated() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnFixedUpdate() = 0;
	virtual void OnDebugRender() = 0;
	virtual void OnClearResources() = 0;
};

