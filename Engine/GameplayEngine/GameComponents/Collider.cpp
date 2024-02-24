#include "Collider.h"

#include "../../../Lib/Math/Math.h"
#include "../../PhysicsEngine/Physics.h"

void Collider::Awake()
{
}

void Collider::Start()
{
}

void Collider::DestroyResources()
{
	Game::instance->physics->RemoveCollider(this);
}

void Collider::Draw()
{
}

void Collider::Initialize()
{
	Game::instance->physics->collidersInGame.emplace_back(this);
}

void Collider::Reload()
{
}
