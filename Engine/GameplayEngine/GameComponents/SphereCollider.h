#pragma once

#include "Collider.h"

class SphereCollider final : public Collider
{
public:
	SMath::Vector3 centerOffset = { .0f,.0f,.0f };
	float radius = 1.0f;

private:

	// Inherited via Collider
	void Awake() override;
	void Start() override;
	void Update() override;
	void FixedUpdate() override;
	void Draw() override;
	void Reload() override;
	CollisionInfo IsCollide(Collider* other) override;
};

