#include "Game.h"
#include "../Engine/DebugSystem/DebugSystem.h"

Game::Game()
{
	instance = this;
	input = new InputDevice(this);
}

Game::~Game()
{
}

Game* Game::instance = nullptr;

void Game::Create()
{
	size = { 1024, 720 };
	window.Create(name, size.x, size.y);
	graphics.Init(window.GetHWND(), window.ClientWidth, window.ClientHeight);
	debug.Init();

	mainCamera = new Camera;

	OnCreated();
}

void Game::Run()
{
	InstantiateGameObject(mainCamera);

	isExitRequested = false;
	graphics.SetUpRasterizer();

	auto previousTime = std::chrono::steady_clock::now();
	float lag = 0;
	for (GameObject* gameObj : gameObjects)
	{
		gameObj->Start();
	}

	isRun = true;
	while (!isExitRequested)
	{
		auto currentTime = std::chrono::steady_clock::now();
		lag += std::chrono::duration_cast<std::chrono::microseconds>(currentTime - previousTime).count() / 1000000.0f;
		previousTime = currentTime;

		processInput();

		while (lag >= time.GetFixedDeltaTime())
		{
			fixedUpdate();
			lag -= time.GetFixedDeltaTime();
		}
		this->time.Update();
		update(this->time.GetDeltaTime());

		render(lag / time.GetFixedDeltaTime());
	}
	isRun = false;
	ClearResources();
}

void Game::InstantiateGameObject(GameObject* gameObject)
{
	gameObject->Awake();
	gameObject->Initialize();
	if (isRun)
	{
		gameObject->Start();
	}
	gameObjects.push_back(gameObject);
}

void Game::Quit()
{
	isExitRequested = true;
}

static MSG msg = {};
void Game::processInput()
{
	// Handle the windows messages.
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// If windows signals to end the application then exit out.
	if (msg.message == WM_QUIT)
	{
		isExitRequested = true;
	}
}

void Game::update(float deltaTime)
{
	OnUpdate();
	for (GameObject* gameObj : gameObjects)
	{
		gameObj->Update(deltaTime);
	}
}
void Game::fixedUpdate()
{
	OnFixedUpdate();
	for (GameObject* gameObj : gameObjects)
	{
		gameObj->FixedUpdate();
	}
	physics.Update();
}

void Game::render(float deltaFrame)
{
	graphics.UpdateState();

	pointLights[0]->GenerateShadowMaps(gameObjects.data(), gameObjects.size());

	graphics.SetUpViewPort(window.ClientWidth, window.ClientHeight);
	graphics.GetGBuffer().SetRenderTargets(graphics.GetContext());
	for (GameObject* obj : gameObjects)
	{
		graphics.GetGBuffer().PrepareToDrawObject(graphics.GetContext());
		graphics.GetContext()->PSSetSamplers(0, 1, &graphics.pSampler);
		Game::instance->graphics.SetSolidRasterizer();
		obj->Draw();
	}
	OnDebugRender();
	graphics.Output();
	graphics.Present();
}

void Game::ClearResources()
{
	OnClearResources();
	debug.ShotDown();
	for (GameObject* gameObj : gameObjects)
	{
		gameObj->Release();
	}
	graphics.Cleanup();
}

