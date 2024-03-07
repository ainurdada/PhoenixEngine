#include "Planet.h"

void Planet::Init(Vector3& worldPosition, Transform* orbitCenter, Vector3& orbitAxisRotation, float orbitAngleVelocity, Vector3& selfRotationAxis, float selfAngleVelocity)
{
	this->orbitCenter = orbitCenter;
	this->orbitAxisRotation = orbitAxisRotation;
	this->orbitAngleVelocity = orbitAngleVelocity;
	this->selfRotationAxis = selfRotationAxis;
	this->selfAngleVelocity = selfAngleVelocity;
	gameObject->transform.position(worldPosition);

	if (orbitCenter != nullptr)
	{
		centerOffset = Transform::Distance(orbitCenter, &gameObject->transform);
	}
}

void Planet::Awake()
{
	RenderComponent* sunRender = new RenderComponent;
	sunRender->shaderPath = BaseResource::litShader;
	radius = 1.f / 2;
	sunRender->mesh = Basic::Sphere::Create(radius, 20, 20);
	Vector3 size = { 1,1,1 };
	//sunRender->mesh = Basic::Box::Create(size, size);
	gameObject->AddComponent(*sunRender);
}



void Planet::Update()
{
	float deltaTime = Game::instance->time.GetDeltaTime();
	gameObject->transform.RotateAroundLocalAxis(selfRotationAxis, selfAngleVelocity * deltaTime);
	if (orbitCenter != nullptr)
	{
		gameObject->transform.position(orbitCenter->position() + centerOffset);
		gameObject->transform.RotateAroundPoint(
			orbitCenter->position(),
			orbitAxisRotation,
			orbitAngleVelocity * deltaTime
		);
		Vector3 orbCenterPos = orbitCenter->position();
		centerOffset = Transform::Distance(orbitCenter, &gameObject->transform);
	}
}
