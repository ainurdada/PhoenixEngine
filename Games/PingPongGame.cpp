#include "PingPongGame.h"

#include "../GraphicsEngine/GraphicsEngine.h"
#include "../App/GameComponents/BaseGameComponents.h"
#include "../Scripts/Player.h"

static Mesh& CreateMesh();

void PingPongGame::Create()
{
	Game::Create();

	GameObject* gameObj = new GameObject;

	RenderComponent* renderComponent = new RenderComponent();
	renderComponent->shaderPath = L"./Shaders/MyVeryFirstShader.hlsl";
	D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(0.0f, 1.0f, 0.0f, 1.0f)", nullptr, nullptr };
	renderComponent->shader.PSMacros = Shader_Macros;
	renderComponent->mesh = CreateMesh();
	gameObj->AddComponent(*renderComponent);


	Player* player = new Player;
	gameObj->AddComponent(*player);


	gameObj->transform.position.x += 0.0f;


	InstantiateGameObject(*gameObj);
}

static Mesh& CreateMesh() {
	std::vector<Vec4> points = {
		Vec4(0.5f, 0.5f, 0.5f, 1.0f), Vec4(1.0f, 0.0f, 0.0f, 1.0f),
		Vec4(-0.5f, -0.5f, 0.5f, 1.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Vec4(0.5f, -0.5f, 0.5f, 1.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f),
		Vec4(-0.5f, 0.5f, 0.5f, 1.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f),
	};
	std::vector<int> indeces = { 0,1,2, 1,0,3 };

	Mesh* pTriangle = new Mesh(points, indeces);
	return *pTriangle;
}
