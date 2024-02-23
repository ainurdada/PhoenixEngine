#include "Game.h"

Game::Game()
{
	instance = this;
}

Game* Game::instance = nullptr;

void Game::Create()
{
	window.Create(name, size.x, size.y);
	graphics.Init(window.GetHWND(), window.ClientWidth, window.ClientHeight);
}

void Game::Run()
{
	isExitRequested = false;
	graphics.SetUpRasterizer();

	float lag = 0;
	while (!isExitRequested)
	{
		this->time.Update();
		lag += this->time.GetDeltaTime();

		processInput();

		while (lag >= ms_per_update)
		{
			update(this->time.GetDeltaTime());
			lag -= ms_per_update;
		}

		graphics.backgroundColor.x = (float)((int)(this->time.GetTime() * 100) % 100) / 100.0f;
		render(lag / ms_per_update);
	}
	ClearResources();
}

void Game::InstantiateGameObject(GameObject gameObject)
{
	for (GameComponent* comp : gameObject.components) {
		comp->Initialize();
	}
	gameObjects.push_back(gameObject);
}

static MSG msg = {};
void Game::processInput()
{
	// Handle the windows messages.
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// If windows signals to end the application then exit out.
	if (msg.message == WM_QUIT) {
		isExitRequested = true;
	}
}

void Game::update(float deltaTime)
{
	for (GameObject& gameObj : gameObjects) {
		gameObj.Update(deltaTime);
	}
}

void Game::render(float deltaFrame)
{
	graphics.UpdateState();
	graphics.SetUpViewPort(window.ClientWidth, window.ClientHeight);
	graphics.UpdateRenderTarget();
	for (GameObject& obj : gameObjects) 
	{
		obj.Draw();
	}
	graphics.Present();
}

void Game::ClearResources()
{
	for (GameObject& gameObj : gameObjects) {
		gameObj.Release();
	}
}
