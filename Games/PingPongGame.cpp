#include "PingPongGame.h"

#include "../Engine/GraphicsEngine/GraphicsEngine.h"
#include "../Engine/GameplayEngine/GameComponents/BaseGameComponents.h"
#include "../Scripts/Player.h"

static Mesh& CreateQuadMesh(SMath::Vector4 leftDown, SMath::Vector4 rightTop);

void PingPongGame::Create()
{
	Game::Create();

	GameObject* gameObj1 = new GameObject;

	RenderComponent* renderComponent = new RenderComponent();
	renderComponent->shaderPath = L"./Shaders/MyVeryFirstShader.hlsl";
	//D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(0.0f, 1.0f, 0.0f, 1.0f)", nullptr, nullptr };
	//renderComponent->shader.PSMacros = Shader_Macros;
	renderComponent->mesh = CreateQuadMesh({ -0.9f,-0.9f,0.5f,1.0f }, { -0.9f + 0.05f,-0.9f + 0.2f,0.5f,1.0f });
	gameObj1->AddComponent(*renderComponent);

	Player* player = new Player;
	gameObj1->AddComponent(*player);

	InstantiateGameObject(*gameObj1);


	GameObject* gameObj2 = new GameObject;

	RenderComponent* renderComponent2 = new RenderComponent();
	renderComponent2->shaderPath = L"./Shaders/MyVeryFirstShader.hlsl";
	renderComponent2->mesh = CreateQuadMesh({ 0.9f - 0.05f,-0.9f,0.5f,1.0f }, { 0.9f,-0.9f + 0.2f,0.5f,1.0f });
	gameObj2->AddComponent(*renderComponent2);
	Player* player2 = new Player;
	player2->isEnemy = true;
	gameObj2->AddComponent(*player2);

	InstantiateGameObject(*gameObj2);
}

static Mesh& CreateQuadMesh(SMath::Vector4 leftDown, SMath::Vector4 rightTop) {
	std::vector<Vec4> points = {
		leftDown, Vec4(1.0f, 0.0f, 0.0f, 1.0f),
		rightTop, Vec4(0.0f, 1.0f, 0.0f, 1.0f),
		Vec4(rightTop.x, leftDown.y, rightTop.x, 1.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f),
		Vec4(leftDown.x, rightTop.y, leftDown.z, 1.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f),
	};
	std::vector<int> indeces = { 0,1,2, 1,0,3 };

	Mesh* pTriangle = new Mesh(points, indeces);
	return *pTriangle;
}
