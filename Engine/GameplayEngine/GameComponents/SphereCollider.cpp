#include "SphereCollider.h"

using namespace SMath;
using namespace DirectX;

void SphereCollider::Awake()
{
}

void SphereCollider::Start()
{
}

void SphereCollider::Update()
{
}

void SphereCollider::FixedUpdate()
{
}

#include "../../DebugSystem/DebugSystem.h"
void SphereCollider::Draw()
{
	Vector3 pos = gameObject->transform.position() + centerOffset;
	DebugTool::Debug::DrawWiredSphere(pos, radius, { 0,1,0,1 });
}

void SphereCollider::Reload()
{
}

CollisionInfo SphereCollider::CheckCollision(Collider* other)
{
	return CollisionInfo();
}

SMath::Vector3 SphereCollider::FindFurthestPoint(SMath::Vector3 direction) const
{
	Vector3 globalPosition = position();
	Vector3 dir = direction;
	dir.Normalize();
	globalPosition += dir * radius;
	return globalPosition;
}

SMath::Vector3 SphereCollider::position() const
{
	return gameObject->transform.position() + Vector3(XMVector3TransformNormal(centerOffset, gameObject->transform.LocalToWorld()));
}
