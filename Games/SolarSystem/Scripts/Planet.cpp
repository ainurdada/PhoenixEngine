#include "Planet.h"

void Planet::Init(Vector3& worldPosition, Transform* orbitCenter, Vector3& orbitAxisRotation, float orbitAngleVelocity, Vector3& selfRotationAxis, float selfAngleVelocity)
{
	this->orbitCenter = orbitCenter;
	this->orbitAxisRotation = orbitAxisRotation;
	this->orbitAngleVelocity = orbitAngleVelocity;
	this->selfRotationAxis = selfRotationAxis;
	this->selfAngleVelocity = selfAngleVelocity;
	gameObject->transform.position(worldPosition);

	RenderComponent* sunRender = new RenderComponent;
	sunRender->shaderPath = BaseResource::litShader;
	sunRender->mesh = Basic::Sphere::Create(2.f / 2, 20, 20);
	gameObject->AddComponent(*sunRender);
}



void Planet::Update()
{
	float deltaTime = Game::instance->time.GetDeltaTime();
	gameObject->transform.RotateAroundAxis(selfRotationAxis, selfAngleVelocity * deltaTime);

	if (orbitCenter != nullptr)
	{
		gameObject->transform.RotateAroundPoint(
			orbitCenter->position(),
			orbitAxisRotation,
			orbitAngleVelocity * deltaTime
		);
	}
}
