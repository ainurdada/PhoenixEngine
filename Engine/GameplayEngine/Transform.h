#pragma once

#include "../../Lib/Math/Math.h"

class Transform {
public:
	Transform() {};

	///// get / set
	const SMath::Vector3& localPosition() const;
	void localPosition(const SMath::Vector3& newLocalPosition);

	const SMath::Vector3& position() const;
	void position(const SMath::Vector3& newPosition);

	const SMath::Quaternion& localRotation() const;
	void localRotation(const SMath::Quaternion& newLocalRotation);

	///// methods 
	SMath::Matrix LocalToWorld();
	/// <summary>
	/// rotates object around axis
	/// </summary>
	/// <param name="angle">in radians</param>
	void RotateAroundAxis(const SMath::Vector3& axis, float angle);

private:
	///// SRT
	SMath::Vector3 m_local_scale = { 1.f, 1.f, 1.f };
	SMath::Quaternion m_local_rotation;
	SMath::Vector3 m_local_position;
	/////


};