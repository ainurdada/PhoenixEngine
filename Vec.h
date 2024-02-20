#pragma once

struct Vec4
{
	Vec4(float x, float y, float z, float a) : x(x), y(y), z(z), a(a) {};
	float x, y, z, a;
};

struct Vec2Int
{
	Vec2Int(int x, int y) : x(x), y(y) {};
	int x, y;
};

