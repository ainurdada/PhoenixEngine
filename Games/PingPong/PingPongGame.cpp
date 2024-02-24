#include "PingPongGame.h"

#include "Scripts/Player.h"
#include "Scripts/Ball.h"

#include "iostream"

void initPlayer(Player* player);

void PingPongGame::Create()
{
	Game::Create();


	Player* player = new Player;
	initPlayer(player);
	Player* player2 = new Player;
	player2->isEnemy = true;
	initPlayer(player2);

	GameObject* ball = new GameObject;;
	Ball* ballScript = new Ball;
	ball->AddComponent(*ballScript);
	ballScript->player = player;
	ballScript->enemy = player2;
	ballScript->velocity = { 0.0f,0.5f };
	InstantiateGameObject(ball);
}

void initPlayer(Player* player) {
	GameObject* gameObj1 = new GameObject;
	RenderComponent* renderComponent = new RenderComponent();
	renderComponent->shaderPath = L"./Shaders/MyVeryFirstShader.hlsl";
	renderComponent->mesh = Basic::Box2D::Create(0.05f, 0.2f);
	gameObj1->AddComponent(*renderComponent);
	gameObj1->AddComponent(*player);
	BoxCollider* collider = new BoxCollider;
	collider->size = { 0.05, 0.2f };
	gameObj1->AddComponent(*collider);
	gameObj1->transform.position.x = -0.9f;
	Game::instance->InstantiateGameObject(gameObj1);
}