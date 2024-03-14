#include "Collider.h"

#include "../../../Lib/Math/Math.h"
#include "../../PhysicsEngine/Physics.h"
#include "../../App/Game.h"

void Collider::DestroyResources()
{
	Game::instance->physics->RemoveCollider(this);
}

void Collider::Initialize()
{
	Game::instance->physics->collidersInGame.emplace_back(this);
}
