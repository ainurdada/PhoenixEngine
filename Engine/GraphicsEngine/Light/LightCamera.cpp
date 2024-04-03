#include "LightCamera.h"

#include "../../../App/Game.h"

using namespace SMath;
using namespace DirectX;
LightCamera::LightCamera()
{
	UpdateProjectionMatrix();
}

const SMath::Matrix& LightCamera::ViewMatrix()
{
	m_viewMatrix = XMMatrixLookAtLH(
		transform.position(),
		transform.position() + transform.Forward(),
		transform.Up()
	);
	return m_viewMatrix;
}
const SMath::Matrix& LightCamera::ProjectionMatrix()
{
	return m_projectionMatrix;
}

void LightCamera::UpdateProjectionMatrix()
{
	if (isPerspective)
	{
		m_projectionMatrix = XMMatrixPerspectiveFovLH(
			m_fov * DEG_TO_RAD,
			(float)Game::instance->window.ClientWidth / (float)Game::instance->window.ClientHeight,
			minClipDistance,
			maxClipDistance);
	}
	else
	{
		m_projectionMatrix = XMMatrixOrthographicLH(
			(float)Game::instance->window.ClientWidth,
			(float)Game::instance->window.ClientHeight,
			minClipDistance,
			maxClipDistance);
	}
}

void LightCamera::SetPerspective(bool perspective)
{
	isPerspective = perspective;
	UpdateProjectionMatrix();
}

float LightCamera::fov() const
{
	return m_fov;
}

void LightCamera::fov(float value)
{
	m_fov = value;
	UpdateProjectionMatrix();
}
