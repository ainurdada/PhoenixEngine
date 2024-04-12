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
			m_fov * DEG_TO_RAD / zoomFactor,
			(float)Game::instance->window.ClientWidth / (float)Game::instance->window.ClientHeight,
			min_clip_distance,
			max_clip_distance);
	}
	else
	{
		m_projectionMatrix = XMMatrixOrthographicLH(
			(float)Game::instance->window.ClientWidth / zoomFactor * 0.025f,
			(float)Game::instance->window.ClientHeight / zoomFactor * 0.025f,
			min_clip_distance,
			max_clip_distance);
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

float Camera::fov() const
{
	return m_fov;
}

void Camera::maxClipDistance(float value)
{
	max_clip_distance = value;
	UpdateProjectionMatrix();
}

void Camera::minClipDistance(float value)
{
	min_clip_distance = value;
	UpdateProjectionMatrix();
}

float Camera::maxClipDistance() const
{
	return max_clip_distance;
}

float Camera::minClipDistance() const
{
	return min_clip_distance;
}
