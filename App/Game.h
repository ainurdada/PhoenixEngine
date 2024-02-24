#pragma once
class Game;

#include "Time.h"
#include <chrono>
#include "Window.h"
#include "../Engine/GraphicsEngine/GraphicsEngine.h"
#include "../Engine/PhysicsEngine/Physics.h"
#include "../Lib/Math/Math.h"
#include "../Engine/GameplayEngine/GameObject.h"
#include "iostream"
#include "../Engine/InputSystem/InputDevice.h"

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
	Vec2Int size = Vec2Int(800, 800);
	Window window;
	Graphics graphics;
	InputDevice* input;
	Physics* physics;

private:
	std::vector<GameObject> gameObjects;
	virtual void processInput();
	virtual void update(float deltaTime);
	virtual void render(float deltaFrame);
	virtual void ClearResources();
private:
	HRESULT res;
	bool isExitRequested = false;
	float ms_per_update = 0.01f;
};

