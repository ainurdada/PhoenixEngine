#pragma once
class Camera;

#include "GameObject.h"

class Camera : public GameObject
{
public:
	Camera();

	const SMath::Matrix& ViewMatrix();
	const SMath::Matrix& ProjectionMatrix();

	void UpdateProjectionMatrix();
	void SetPerspective(bool perspective);
	void zoom(float value);
	float zoom();
	float fov() const;

private:
	bool isPerspective = true;

	float minClipDistance = 0.1f;
	float maxClipDistance = 100.0f;
	float m_fov = 90.0f;
	float aspectRation = 16.0f / 9.0f;

	float zoomFactor = 1.0f;

	SMath::Matrix m_viewMatrix;
	SMath::Matrix m_projectionMatrix;
};