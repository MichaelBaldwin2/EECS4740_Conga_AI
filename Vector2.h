/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#pragma once

/// <summary>
/// A 2 part floating point vecotr class
/// </summary>
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