#include "Transform.h"

using namespace SMath;

Matrix Transform::GetMatrix()
{
	return Matrix::CreateTranslation(position);
}

inline Vector3 Transform::Forward()
{
	return { 0.f, 0.f, 1.f };
}

inline Vector3 Transform::Right()
{
	return { 1.f, 0.f, 0.f };
}

inline Vector3 Transform::Up()
{
	return { 0.f, 1.f, 0.f };
}

Matrix Transform::LocalToWorld()
{
	Matrix res;
	res.Forward(Forward());
	res.Right(Right());
	res.Up(Up());
	res.Translation(position);
	return res;
}
