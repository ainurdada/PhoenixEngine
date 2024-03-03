#include "Camera.h"

using namespace SMath;
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
	m_viewMatrix = Matrix::CreateLookAt(
		transform.position(),
		transform.position() + transform.Forward(),
		transform.Up());
	DirectX::XMMatrixLookAtLH(
		transform.position(),
		transform.position() + transform.Forward(),
		transform.Up());
	return DirectX::XMMatrixLookAtLH(
		transform.position(),
		transform.position() + transform.Forward(),
		transform.Up());
}

#include <DirectXMath.h>

const SMath::Matrix& Camera::ProjectionMatrix()
{
	m_projectionMatrix = Matrix::CreatePerspectiveFieldOfView(
		fov,
		aspectRation,
		minClipDistance,
		maxClipDistance
	);
	DirectX::XMMatrixPerspectiveFovLH(
		fov,
		aspectRation,
		minClipDistance,
		maxClipDistance
	);
	return DirectX::XMMatrixPerspectiveFovLH(
		fov,
		aspectRation,
		minClipDistance,
		maxClipDistance
	);
}
