#pragma once

#include "../../../Lib/Math/Math.h"
#include "../../GameplayEngine/Transform.h"

class LightCamera
{
public:
	LightCamera();
	const SMath::Matrix& ViewProjectionMatrix() const;
	const SMath::Matrix& ViewMatrix() const;
	const SMath::Matrix& ProjectionMatrix() const;

	void UpdateProjectionMatrix();
	void SetPerspective(bool perspective);
	void SetRotation(const SMath::Vector3& forward, const SMath::Vector3& up);

	float fov() const;
	void fov(float value);

	Transform transform;
private:
	bool isPerspective = true;
	float minClipDistance = 0.1f;
	float maxClipDistance = 50.0f;
	float m_fov = 90.0f;
	float aspectRation = 1;
	SMath::Matrix m_projectionMatrix;
};

