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
	ballScript->velocity = { 0.5f,0.0f };
	ballScript->size = { 0.05f, 0.05f };
	InstantiateGameObject(ball);

	this->player1 = player;
	this->player2 = player2;
	this->ball = ballScript;
}

void initPlayer(Player* player) {
	GameObject* gameObj1 = new GameObject;
	gameObj1->AddComponent(*player);
	player->size = { 0.05f, 0.2f };
	Game::instance->InstantiateGameObject(gameObj1);
}

void PingPongGame::Restart()
{
	player1->gameObject->transform.position.y = 0;
	player2->gameObject->transform.position.y = 0;
	ball->gameObject->transform.position.x = 0;
	ball->gameObject->transform.position.y = 0;
	ball->velocity.y = 0;
	if (std::signbit(ball->velocity.x)) {
		ball->velocity.x = -0.5f;
	}
	else {
		ball->velocity.x = 0.5f;
	}
}