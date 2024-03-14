#pragma once
class Collider;

#include "GameComponent.h"

struct CollisionInfo 
{
	bool isCollide;
	DirectX::XMVECTOR nearestPoint;
};

class Collider : public GameComponent
{
protected:
	virtual void DestroyResources() override;
	virtual void Initialize() override;
	virtual CollisionInfo IsCollide(Collider* other) = 0;
private:
};

