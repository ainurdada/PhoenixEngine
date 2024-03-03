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

SMath::Matrix Transform::LocalToWorld()
{
	SMath::Matrix m;
	m.Translation(m_local_position);
	return m;
}
