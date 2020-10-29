#pragma once

#include <sdl.h>

class Vector2
{
public:
	const static Vector2 Zero;
	const static Vector2 One;
	const static Vector2 Up;
	const static Vector2 Down;
	const static Vector2 Left;
	const static Vector2 Right;

public:
	float x;
	float y;

public:
	Vector2(float x = 0, float y = 0);
	explicit operator SDL_Point() const;
	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator-=(const Vector2& rhs);
	Vector2& operator*=(const Vector2& rhs);
	Vector2& operator/=(const Vector2& rhs);
	Vector2& operator+=(float rhs);
	Vector2& operator-=(float rhs);
	Vector2& operator*=(float rhs);
	Vector2& operator/=(float rhs);

	friend Vector2 operator+(Vector2 lhs, const Vector2& rhs) { lhs += rhs; return lhs; }
	friend Vector2 operator-(Vector2 lhs, const Vector2& rhs) { lhs -= rhs; return lhs; }
	friend Vector2 operator*(Vector2 lhs, const Vector2& rhs) { lhs *= rhs; return lhs; }
	friend Vector2 operator/(Vector2 lhs, const Vector2& rhs) { lhs /= rhs; return lhs; }
	friend Vector2 operator+(Vector2 lhs, const float rhs) { lhs += rhs; return lhs; }
	friend Vector2 operator-(Vector2 lhs, const float rhs) { lhs -= rhs; return lhs; }
	friend Vector2 operator*(Vector2 lhs, const float rhs) { lhs *= rhs; return lhs; }
	friend Vector2 operator/(Vector2 lhs, const float rhs) { lhs /= rhs; return lhs; }
};