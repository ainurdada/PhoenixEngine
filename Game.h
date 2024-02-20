#pragma once
class Game;

#include "Time.h"
#include "Window.h"
#include "GraphicsEngine.h"
#include "MathEngine.h"
#include "GameObject.h"

class Game
{
public:
	Game();
public:
	void Create();
	void Run();
	void InstantiateGameObject(GameObject gameObject);
public:
	static Game* instance;
	Time time;
	LPCWSTR name = L"My game";
	Vec2Int size = Vec2Int(800, 800);
	Window window;
	Graphics graphics;

private:
	std::vector<GameObject> gameObjects;
	void processInput();
	void update(float deltaTime);
	void render(float deltaFrame);
private:
	HRESULT res;
	bool isExitRequested = false;
	float ms_per_update = 0.16f;
};

