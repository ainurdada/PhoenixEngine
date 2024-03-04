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
	return LocalToWorld().Translation();
}

void Transform::position(const SMath::Vector3& newPosition)
{
	if (parent != nullptr)
	{
		m_local_position = XMVector3TransformCoord(newPosition, XMMatrixInverse(nullptr, parent->LocalToWorld()));
	}
	else
	{
		m_local_position = newPosition;
	}
}

const SMath::Quaternion& Transform::localRotation() const
{
	return m_local_rotation;
}

void Transform::localRotation(const SMath::Quaternion& newLocalRotation)
{
	m_local_rotation = newLocalRotation;
}

SMath::Matrix Transform::LocalToWorld() const
{
	XMMATRIX m;
	m = XMMatrixScalingFromVector(m_local_scale)
		* XMMatrixRotationQuaternion(m_local_rotation)
		* XMMatrixTranslationFromVector(m_local_position);
	Transform* next = parent;
	while (next != nullptr)
	{
		XMMATRIX mNext;
		mNext = XMMatrixScalingFromVector(next->m_local_scale)
			* XMMatrixRotationQuaternion(next->m_local_rotation)
			* XMMatrixTranslationFromVector(next->m_local_position);
		m *= mNext;
		next = next->parent;
	}
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
	position(position() + dir);
}

void Transform::SetParent(Transform* parent)
{
	if (parent != nullptr)
	{
		this->parent->childs.erase(std::remove(childs.begin(), childs.end(), this),
					 childs.end());
	}
	this->parent = parent;
	if (this->parent != nullptr)
	{
		this->parent->childs.push_back(this);
	}
}

Vector3 Transform::Right() const
{
	return XMVector3TransformNormal(Vector3::Right, LocalToWorld());
}

Vector3 Transform::Up() const
{
	return XMVector3TransformNormal(Vector3::Up, LocalToWorld());
}

Vector3 Transform::Forward() const
{
	return XMVector3TransformNormal(-Vector3::Forward, LocalToWorld());
}
