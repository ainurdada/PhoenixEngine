#include "Collider.h"

#include "../../../Lib/Math/Math.h"
#include "../../PhysicsEngine/Physics.h"

bool Collider::IsCollisionEnter(GameObject* out)
{
	for (GameObject& obj : Game::instance->gameObjects) 
	{
		if (&obj == gameObject) continue;

		Collider* col = obj.GetComponent<Collider>();
		if (col != nullptr) {
			//SMath::Rectangle::In
		}
	}
	//SMath::Rectangle::Intersects


	// no collisions
	out = nullptr;
	return false;
}

void Collider::Awake()
{
}

void Collider::Start()
{
}

void Collider::Update()
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
