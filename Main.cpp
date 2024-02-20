#include <windows.h>
#include <chrono>

#include "Window.h"
#include "Time.h"
#include "GraphicsEngine.h"
#include "MeshComponent.h"

#include <iostream>
#include <thread>

#define MS_PER_UPDATE 0.16

void processInput();
void update(float deltaTime);
void render(MeshComponent& mesh, Shader& shader, float deltaFrame);
MeshComponent& CreateMesh(Graphics& grapgics);

static Window window;
static Graphics graphics;
static Time game_time;
static HRESULT res;
static bool isExitRequested = false;

int main() {
	window.Create(L"test", 800, 800);
	graphics.Init(window.GetHWND(), window.ClientWidth, window.ClientHeight);

	Shader shader(L"./Shaders/MyVeryFirstShader.hlsl", graphics.GetDevice());
	res = shader.CompileVS(nullptr, nullptr);
	if (FAILED(res)) {
		window.ShowMessageBox(L"MyVeryFirstShader.hlsl", L"Missing Shader File");
		return 0;
	}
	D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(0.0f, 1.0f, 0.0f, 1.0f)", nullptr, nullptr };
	res = shader.CompilePS(Shader_Macros, nullptr);
	res = shader.CreateInputLayout();

	MeshComponent triangle = CreateMesh(graphics);

	graphics.SetUpRasterizer();

	float lag = 0;
	while (!isExitRequested)
	{
		game_time.Update();
		lag += game_time.GetDeltaTime();

		processInput();

		while (lag >= MS_PER_UPDATE)
		{
			update(game_time.GetDeltaTime());
			lag -= MS_PER_UPDATE;
		}

		render(triangle, shader, lag / MS_PER_UPDATE);
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return 0;
}


static MSG msg = {};
void processInput()
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

void update(float deltaTime)
{
}

void render(MeshComponent& mesh, Shader& shader, float deltaFrame)
{
	graphics.UpdateState();
	graphics.SetUpViewPort(window.ClientWidth, window.ClientHeight);
	graphics.SetUpIA(shader.layout, mesh, shader);
	graphics.SetShader(shader);
	graphics.UpdateRenderTarget();
	mesh.Draw();
	graphics.Present();
}

MeshComponent& CreateMesh(Graphics& grapgics) {
	std::vector<Vec4> points = {
		Vec4(0.5f, 0.5f, 0.5f, 1.0f), Vec4(1.0f, 0.0f, 0.0f, 1.0f),
		Vec4(-0.5f, -0.5f, 0.5f, 1.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Vec4(0.5f, -0.5f, 0.5f, 1.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f),
		Vec4(-0.5f, 0.5f, 0.5f, 1.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f),
	};
	std::vector<int> indeces = { 0,1,2, 1,0,3 };
	MeshComponent* pTriangle = new MeshComponent(grapgics, points, indeces);
	return *pTriangle;
}
