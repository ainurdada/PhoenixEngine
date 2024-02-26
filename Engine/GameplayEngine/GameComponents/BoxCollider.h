#pragma once

#include "Collider.h"

class BoxCollider : public Collider
{
public:
	bool IsCollided(BoxCollider** out);

public:
	SMath::Vector3 size;
	SMath::Vector3 velocity;
private:
	DirectX::BoundingOrientedBox oBox;

private:
	// Inherited via Collider
	void Update() override;
	void DestroyResources() override;
	void Initialize() override;
};

