#include "PingPongGame.h"

#include "../../Engine/GraphicsEngine/GraphicsEngine.h"
#include "../../Engine/GameplayEngine/GameComponents/BaseGameComponents.h"
#include "Scripts/Player.h"
#include "../../Basic/Shapes/Box2D.h"

void PingPongGame::Create()
{
	Game::Create();


	GameObject* gameObj1 = new GameObject;
	RenderComponent* renderComponent = new RenderComponent();
	renderComponent->shaderPath = L"./Shaders/MyVeryFirstShader.hlsl";
	renderComponent->mesh = Basic::Box2D::Create(0.05f, 0.2f);
	gameObj1->AddComponent(*renderComponent);
	Player* player = new Player;
	gameObj1->AddComponent(*player);
	gameObj1->transform.position.x = -0.9f;
	InstantiateGameObject(*gameObj1);


	GameObject* gameObj2 = new GameObject;
	RenderComponent* renderComponent2 = new RenderComponent();
	renderComponent2->shaderPath = L"./Shaders/MyVeryFirstShader.hlsl";
	renderComponent2->mesh = Basic::Box2D::Create(0.05f, 0.2f);
	gameObj2->AddComponent(*renderComponent2);
	Player* player2 = new Player;
	player2->isEnemy = true;
	gameObj2->AddComponent(*player2);
	gameObj2->transform.position.x = 0.9f;
	InstantiateGameObject(*gameObj2);
}
