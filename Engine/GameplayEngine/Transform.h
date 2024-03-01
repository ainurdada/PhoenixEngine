#pragma once

#include "../../Lib/Math/Math.h"

struct Transform {
	SMath::Vector3 position = { 0,0,0 };
	SMath::Vector3 scale = { 1,1,1 };
	SMath::Quaternion rotation;

	SMath::Vector3 Forward();
	SMath::Vector3 Right();
	SMath::Vector3 Up();

	SMath::Matrix LocalToWorld();
	SMath::Matrix GetMatrix();

private:
	SMath::Matrix matrix;
};