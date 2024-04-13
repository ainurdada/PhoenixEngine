#include "LightCamera.h"

#include "../../../App/Game.h"

using namespace SMath;
using namespace DirectX;
LightCamera::LightCamera()
{
	UpdateProjectionMatrix();
}

const SMath::Matrix& LightCamera::ViewProjectionMatrix() const
{
	Matrix view = ViewMatrix();
	return XMMatrixTranspose(view * m_projectionMatrix);
}

const SMath::Matrix& LightCamera::ViewMatrix() const
{
	return XMMatrixLookAtLH(
		transform.position(),
		transform.position() + transform.Forward(),
		transform.Up());
}
const SMath::Matrix& LightCamera::ProjectionMatrix() const
{
	return m_projectionMatrix;
}

void LightCamera::UpdateProjectionMatrix()
{
	if (isPerspective)
	{
		m_projectionMatrix = XMMatrixPerspectiveFovLH(
			m_fov * DEG_TO_RAD,
			aspectRation,
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

void LightCamera::SetRotation(const SMath::Vector3& forward, const SMath::Vector3& up)
{
	transform.LookAt(transform.position() + forward, up);
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
