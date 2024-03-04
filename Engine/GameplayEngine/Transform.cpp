#include "Transform.h"

using namespace SMath;
using namespace DirectX;

const SMath::Vector3& Transform::localPosition() const
{
	return m_local_position;
}

void Transform::localPosition(const SMath::Vector3& newLocalPosition)
{
	m_local_position = newLocalPosition;
}

const SMath::Vector3& Transform::position() const
{
	return m_local_position;
}

void Transform::position(const SMath::Vector3& newPosition)
{
	m_local_position = newPosition;
}

const SMath::Quaternion& Transform::localRotation() const
{
	return m_local_rotation;
}

void Transform::localRotation(const SMath::Quaternion& newLocalRotation)
{
	m_local_rotation = newLocalRotation;
}

SMath::Matrix Transform::LocalToWorld()
{
	XMMATRIX m;
	m = XMMatrixScalingFromVector(m_local_scale)
		* XMMatrixRotationQuaternion(Quaternion::Identity)
		* XMMatrixTranslationFromVector(m_local_position);
	return m;
}

void Transform::RotateAroundAxis(const SMath::Vector3& axis, float angle)
{
	Quaternion q = Quaternion::CreateFromAxisAngle(axis, angle);
	Quaternion inv;
	q.Inverse(inv);
	m_local_rotation *= inv;
}

void Transform::Move(const SMath::Vector3& dir)
{
	m_local_position += dir;
}

Vector3 Transform::Right() const
{
	return Vector3::Transform(Vector3::Right, m_local_rotation);
}

Vector3 Transform::Up() const
{
	return Vector3::Transform(Vector3::Up, m_local_rotation);
}

Vector3 Transform::Forward() const
{
	return Vector3::Transform(-Vector3::Forward, m_local_rotation);
}
