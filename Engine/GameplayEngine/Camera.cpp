#include "Camera.h"
#include "../../App/Game.h"

using namespace SMath;
using namespace DirectX;
Camera::Camera() : GameObject()
{
	UpdateProjectionMatrix();
}

const SMath::Matrix& Camera::ViewMatrix()
{
	m_viewMatrix = XMMatrixLookAtLH(
		transform.position(),
		transform.position() + transform.Forward(),
		transform.Up()
	);
	return m_viewMatrix;
}


const SMath::Matrix& Camera::ProjectionMatrix()
{
	return m_projectionMatrix;
}

void Camera::UpdateProjectionMatrix()
{
	if (isPerspective)
	{
		m_projectionMatrix = XMMatrixPerspectiveFovLH(
			fov * DEG_TO_RAD / zoomFactor,
			(float)Game::instance->window.ClientWidth / (float)Game::instance->window.ClientHeight,
			minClipDistance,
			maxClipDistance);
	}
	else
	{
		m_projectionMatrix = XMMatrixOrthographicLH(
			(float)Game::instance->window.ClientWidth / zoomFactor * 0.025f,
			(float)Game::instance->window.ClientHeight / zoomFactor * 0.025f,
			minClipDistance,
			maxClipDistance);
	}
}

void Camera::SetPerspective(bool perspective)
{
	isPerspective = perspective;
	if (zoomFactor < 1 && isPerspective) zoomFactor = 1;
	UpdateProjectionMatrix();
}

void Camera::zoom(float value)
{
	zoomFactor = value;
	if (zoomFactor < 1 && isPerspective) zoomFactor = 1;
	UpdateProjectionMatrix();
}

float Camera::zoom()
{
	return zoomFactor;
}
