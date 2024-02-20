#include <windows.h>
#include <chrono>

#include "Window.h"
#include "Time.h"
#include "GraphicsEngine.h"
#include "Mesh.h"
#include "Game.h"
#include "GameObject.h"

#include <iostream>
#include <thread>

Mesh& CreateMesh();


int main() {
	Game game;
	game.Create();

	GameObject gameObj;

	RenderComponent renderComponent;
	renderComponent.shaderPath = L"./Shaders/MyVeryFirstShader.hlsl";
	D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(0.0f, 1.0f, 0.0f, 1.0f)", nullptr, nullptr };
	renderComponent.shader.PSMacros = Shader_Macros;
	renderComponent.mesh = CreateMesh();

	gameObj.AddComponent(renderComponent);

	game.InstantiateGameObject(gameObj);

	game.Run();

	return 0;
}


Mesh& CreateMesh() {
	std::vector<Vec4> XMPoints = {
		Vec4(0.5f, 0.5f, 0.5f, 1.0f), Vec4(1.0f, 0.0f, 0.0f, 1.0f),
		Vec4(-0.5f, -0.5f, 0.5f, 1.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Vec4(0.5f, -0.5f, 0.5f, 1.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f),
		Vec4(-0.5f, 0.5f, 0.5f, 1.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f),
	};
	std::vector<int> indeces = { 0,1,2, 1,0,3 };
	Mesh* pTriangle = new Mesh(XMPoints, indeces);
	return *pTriangle;
}
