#pragma once
class Game;

#include "Time.h"
#include <chrono>
#include "Window.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../Math/MathEngine.h"
#include "GameObject.h"
#include "iostream"
#include "../InputSystem/InputDevice.h"

class Game
{
public:
	Game();
public:
	virtual void Create();
	virtual void Run();
	virtual void InstantiateGameObject(GameObject gameObject);
public:
	static Game* instance;
	Time time;
	LPCWSTR name = L"My game";
	Vec2Int size = Vec2Int(800, 800);
	Window window;
	Graphics graphics;
	InputDevice* input;

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

