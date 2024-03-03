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


	///// methods 
	SMath::Matrix LocalToWorld();

private:
	///// SRT
	SMath::Vector3 m_local_scale;
	SMath::Quaternion m_local_rotation;
	SMath::Vector3 m_local_position;
	/////


};