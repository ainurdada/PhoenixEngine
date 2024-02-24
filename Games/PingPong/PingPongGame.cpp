#include "PingPongGame.h"

#include "Scripts/Player.h"
#include "Scripts/Ball.h"

#include "iostream"

void initPlayer(Player* player);

void PingPongGame::Create()
{
	Game::Create();


	Player* player = new Player;
	player->startPosition.x = -0.9f;
	initPlayer(player);
	Player* player2 = new Player;
	player2->startPosition.x = 0.9f;
	player2->isEnemy = true;
	initPlayer(player2);

	GameObject* ball = new GameObject;;
	Ball* ballScript = new Ball;
	ball->AddComponent(*ballScript);
	ballScript->player = player;
	ballScript->enemy = player2;
	ballScript->velocity = { 0.5f,0.1f };
	InstantiateGameObject(ball);
}

void initPlayer(Player* player) {
	GameObject* gameObj1 = new GameObject;
	gameObj1->AddComponent(*player);
	Game::instance->InstantiateGameObject(gameObj1);
}