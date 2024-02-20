#pragma once

struct Vec4
{
	Vec4() : x(0), y(0), z(0), a(0) {};
	Vec4(float x, float y, float z, float a) : x(x), y(y), z(z), a(a) {};
	float x, y, z, a;
};

struct Vec2Int
{
	Vec2Int() : x(0), y(0) {};
	Vec2Int(int x, int y) : x(x), y(y) {};
	int x, y;
};

