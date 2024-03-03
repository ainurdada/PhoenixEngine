#pragma once
class Camera;

#include "GameObject.h"

class Camera : public GameObject
{
public:
	Camera();

	const SMath::Matrix& ViewMatrix();
	const SMath::Matrix& ProjectionMatrix();

private:
	float minClipDistance = 0.1f;
	float maxClipDistance = 100.0f;
	float fov = 67.0f;
	float aspectRation = 16.0f / 9.0f;

	SMath::Matrix m_viewMatrix;
	SMath::Matrix m_projectionMatrix;
};