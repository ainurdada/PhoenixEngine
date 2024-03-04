#include "Camera.h"

using namespace SMath;
using namespace DirectX;
Camera::Camera() : GameObject()
{
	m_viewMatrix = Matrix::CreatePerspectiveFieldOfView(
		fov,
		aspectRation,
		minClipDistance,
		maxClipDistance
	);
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

#include "../../App/Game.h"

const SMath::Matrix& Camera::ProjectionMatrix()
{
	m_projectionMatrix = XMMatrixPerspectiveFovLH(
		XM_PIDIV4, 
		Game::instance->window.ClientWidth / Game::instance->window.ClientHeight,
		minClipDistance, 
		maxClipDistance);
	return m_projectionMatrix;
}
