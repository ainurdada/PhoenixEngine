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
	// ������������� ������� ����
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);    // ���� �������

	XMVECTOR Eye = XMVectorSet(0.0f, 5.0f, -10.0f, 0.0f);  // ������ �������

	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);    // ����������� �����

	m_viewMatrix = XMMatrixLookAtLH(
		transform.position(),
		transform.position() + transform.Forward(),
		transform.Up()
	);

	//m_viewMatrix = XMMatrixLookAtLH(Eye, At, Up);

	return m_viewMatrix;
}

const SMath::Matrix& Camera::ProjectionMatrix()
{
	m_projectionMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV4, aspectRation, minClipDistance, maxClipDistance);
	return m_projectionMatrix;
}
