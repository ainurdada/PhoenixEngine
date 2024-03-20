#pragma once

#include "../../Lib/Math/Math.h"
#include <vector>

class Transform {
public:
	Transform() {};

	///// get / set
	const SMath::Vector3& localPosition() const;
	const SMath::Vector3& position() const;
	const SMath::Quaternion& localRotation() const;
	const SMath::Vector3& localScale() const;
	const SMath::Vector3& scale() const;

	void localPosition(const SMath::Vector3& newLocalPosition);
	void position(const SMath::Vector3& newPosition);
	void localRotation(const SMath::Quaternion& newLocalRotation);
	void localScale(const SMath::Vector3& newLocalScale);
	void scale(const SMath::Vector3& newScale);



	///// methods 
	SMath::Matrix LocalToWorld() const;
	/// <summary>
	/// rotates object around axis
	/// </summary>
	/// <param name="angle">in radians</param>
	void RotateAroundAxis(const SMath::Vector3& axis, float angle);
	void RotateAroundLocalAxis(const SMath::Vector3& axis, float angle);
	void RotateAroundPoint(const SMath::Vector3& point, const SMath::Vector3& axisAlongRotation, float angle);
	void Move(const SMath::Vector3& dir);
	void SetParent(Transform* parent);
	void SetParent(Transform* parent, bool safePositionRotationScale);

	SMath::Vector3 Right() const;
	SMath::Vector3 Up() const;
	SMath::Vector3 Forward() const;


	static SMath::Vector3 Distance(const Transform* from, const Transform* to);

private:
	///// SRT
	SMath::Vector3 m_local_scale = { 1.f, 1.f, 1.f };
	SMath::Quaternion m_local_rotation;
	SMath::Vector3 m_local_position;
	/////

	Transform* parent = nullptr;
	std::vector<Transform*> childs;
};