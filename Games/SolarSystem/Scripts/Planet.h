#pragma once
#include "../SolarSystem.h"

class Planet : public BehaviourScript
{
public:
	void Init(Vector3& worldPosition, 
			  Transform* orbitCenter, 
			  Vector3& orbitAxisRotation,
			  float orbitAngleVelocity,
			  Vector3& selfRotationAxis,
			  float selfAngleVelocity);
	void Awake() override;
	void Update() override;
private:
	Transform* orbitCenter = nullptr;
	Vector3 orbitAxisRotation;
	float orbitAngleVelocity;
	Vector3 selfRotationAxis;
	float selfAngleVelocity;
};

