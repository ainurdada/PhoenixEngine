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
	sunRender->shader = ShaderManager::Get(BaseResource::litShader);
	sunRender->texture = new Texture(BaseResource::brickTextur);
	radius = 1.f / 2;
	sunRender->modelPath = L"./Models/nanosuit/nanosuit.obj";
	//sunRender->mesh = &Basic::Sphere::Create(radius, 20, 20);
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

void Planet::Draw()
{
	Debug::DrawLine(
		gameObject->transform.position(),
		gameObject->transform.position() + gameObject->transform.Up(),
		{ 0,0,1,1 }
	);

	Debug::DrawLine(
		gameObject->transform.position(),
		Vector3::Zero,
		{ 1,0,0,1 }
	);
}
