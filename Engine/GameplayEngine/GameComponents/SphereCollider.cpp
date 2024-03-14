#include "SphereCollider.h"

using namespace SMath;

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

CollisionInfo SphereCollider::IsCollide(Collider* other)
{
	return CollisionInfo();
}
