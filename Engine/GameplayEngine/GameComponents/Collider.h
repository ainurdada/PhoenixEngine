#pragma once
class Collider;

#include "GameComponent.h"
#include "../../Lib/Math/Math.h"

struct CollisionInfo 
{
	bool isCollide;
	SMath::Vector3 nearestPoint;
};

class Collider : public GameComponent
{
public:
	virtual SMath::Vector3 FindFurthestPoint(SMath::Vector3 direction) const = 0;
	virtual SMath::Vector3 position() const = 0;

protected:
	virtual void DestroyResources() override;
	virtual void Initialize() override;
	virtual CollisionInfo CheckCollision(Collider* other) = 0;
private:
};

