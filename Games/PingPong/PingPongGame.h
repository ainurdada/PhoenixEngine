#pragma once
#include "../../PhoenixEngine.h"

class Player;
class Ball;

class PingPongGame : public Game
{
public:
	virtual void Create() override;


public:
	void Restart();

public:
	Player* player1;
	Player* player2;
	Ball* ball;
};

