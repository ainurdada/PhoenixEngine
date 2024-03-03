#include "BoxCollider.h"

bool BoxCollider::IsCollided(BoxCollider** out)
{
	for (Collider* boxCol : Game::instance->physics->collidersInGame) {
		if (boxCol == this) continue;

		BoxCollider* res = (BoxCollider*)boxCol;
		if (oBox.Intersects(res->oBox))
		{
			*out = res;
			return true;
		}
	}

	// no collisions
	out = nullptr;
	return false;
}

void BoxCollider::Update()
{
	velocity = (gameObject->transform.position() - oBox.Center) / Game::instance->time.GetDeltaTime();
	oBox.Center = gameObject->transform.position();
}

void BoxCollider::FixedUpdate()
{
}

void BoxCollider::DestroyResources()
{
	Collider::DestroyResources();
}

void BoxCollider::Initialize()
{
	Collider::Initialize();
	oBox.Center = gameObject->transform.position();
	oBox.Extents = size / 2;
	SMath::Quaternion quat;
	oBox.Orientation;
}
