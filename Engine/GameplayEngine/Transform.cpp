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
		m_local_position = XMVector3Transform(newPosition, XMMatrixInverse(nullptr, parent->LocalToWorld()));
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

const SMath::Vector3& Transform::localScale() const
{
	return m_local_scale;
}

void Transform::localScale(const SMath::Vector3& newLocalScale)
{
	m_local_scale = newLocalScale;
}

const SMath::Vector3& Transform::scale() const
{
	if (parent != nullptr)
	{
		return XMVector3TransformNormal(m_local_scale, parent->LocalToWorld());
	}
	else
	{
		return m_local_scale;
	}
}

void Transform::scale(const SMath::Vector3& newScale)
{
	if (parent != nullptr)
	{
		m_local_scale = newScale / parent->scale();
	}
	else
	{
		m_local_scale = newScale;
	}
}

SMath::Matrix Transform::LocalToWorld() const
{
	XMMATRIX m;
	m = XMMatrixAffineTransformation(
		m_local_scale,
		g_XMZero,
		m_local_rotation,
		m_local_position
	);
	Transform* next = parent;
	while (next != nullptr)
	{
		XMMATRIX mNext;
		mNext = XMMatrixAffineTransformation(
			next->m_local_scale,
			g_XMZero,
			next->m_local_rotation,
			next->m_local_position
		);
		m = XMMatrixMultiply(m, mNext);
		next = next->parent;
	}
	return m;
}

void Transform::RotateAroundAxis(const SMath::Vector3& axis, float angle)
{
	Vector3 globalAxis = axis;
	if (parent != nullptr)
	{
		globalAxis = XMVector3TransformNormal(axis, parent->LocalToWorld());
	}
	m_local_rotation *= Quaternion::CreateFromAxisAngle(globalAxis, angle);
}

void Transform::RotateAroundLocalAxis(const SMath::Vector3& axis, float angle)
{
	Vector3 local = XMVector3Rotate(axis, m_local_rotation);
	m_local_rotation *= Quaternion::CreateFromAxisAngle(local, angle);
}

void Transform::RotateAroundPoint(const SMath::Vector3& point, const SMath::Vector3& axisAlongRotation, float angle)
{
	Quaternion q = Quaternion::CreateFromAxisAngle(axisAlongRotation, angle);
	Vector3 origin = point;
	Vector3 dif = point - position();
	Vector3 newDif = XMVector3Rotate(dif, q);
	position(origin - newDif);
	m_local_rotation *= q;
}

void Transform::Move(const SMath::Vector3& dir)
{
	position(position() + dir);
}

void Transform::SetParent(Transform* parent)
{
	if (parent == this->parent) return;
	if (this->parent != nullptr)
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

void Transform::SetParent(Transform* parent, bool safePositionRotationScale)
{
	if (safePositionRotationScale)
	{
		Vector3 scale = this->scale();
		Quaternion rot = this->localRotation();
		Vector3 pos = this->position();
		SetParent(parent);
		this->scale(scale);
		this->localRotation(rot);
		this->position(pos);
	}
	else
	{
		SetParent(parent);
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

SMath::Vector3 Transform::Distance(const Transform* from, const Transform* to)
{
	Vector3 t1Pos = from->position();
	return to->position() - t1Pos;
}
