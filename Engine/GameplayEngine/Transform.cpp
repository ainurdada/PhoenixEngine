#include "Transform.h"

using namespace SMath;

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
	SMath::Matrix m;
	m = Matrix::CreateScale(m_local_scale);
	m *= Matrix::CreateFromQuaternion(m_local_rotation);
	m *= Matrix::CreateTranslation(m_local_position);
	return m;
}

void Transform::RotateAroundAxis(const SMath::Vector3& axis, float angle)
{
	Quaternion q = Quaternion::CreateFromAxisAngle(axis, angle);
	m_local_rotation *= q;
}

void Transform::Move(const SMath::Vector3& dir)
{
	m_local_position += dir;
}

Vector3 Transform::Right() const
{
	Vector3 res;
	Matrix m = Matrix::CreateFromQuaternion(m_local_rotation);
	Vector3::Transform(Vector3::Right, m, res);
	return res;
}

Vector3 Transform::Up() const
{
	Vector3 res;
	Matrix m = Matrix::CreateFromQuaternion(m_local_rotation);
	Vector3::Transform(Vector3::Up, m, res);
	return res;
}

Vector3 Transform::Forward() const
{
	Vector3 res;
	Matrix m = Matrix::CreateFromQuaternion(m_local_rotation);
	Vector3::Transform(Vector3::Forward, m, res);
	return res;
}
