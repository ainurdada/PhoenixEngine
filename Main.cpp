#include "Games/PingPong/PingPongGame.h"
#include "Games/3DScene/Scene3DTest.h"
#include "Games/SolarSystem/SolarSystem.h"

int main() {
	SolarSystem game;
	game.Create();

	game.Run();

	return 0;
}
