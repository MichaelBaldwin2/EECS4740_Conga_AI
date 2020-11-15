#pragma once

#include "Vector2.h"

class Vector2Int
{
public:
	const static Vector2Int Zero;
	const static Vector2Int One;
	const static Vector2Int Up;
	const static Vector2Int Down;
	const static Vector2Int Left;
	const static Vector2Int Right;

public:
	int x;
	int y;

public:
	Vector2Int(int x = 0, int y = 0);

	operator Vector2() const;
	Vector2Int& operator+=(const Vector2Int& rhs);
	Vector2Int& operator-=(const Vector2Int& rhs);
	Vector2Int& operator*=(const Vector2Int& rhs);
	Vector2Int& operator/=(const Vector2Int& rhs);
	Vector2Int& operator+=(int rhs);
	Vector2Int& operator-=(int rhs);
	Vector2Int& operator*=(int rhs);
	Vector2Int& operator/=(int rhs);

	friend Vector2Int operator+(Vector2Int lhs, const Vector2Int& rhs) { lhs += rhs; return lhs; }
	friend Vector2Int operator-(Vector2Int lhs, const Vector2Int& rhs) { lhs -= rhs; return lhs; }
	friend Vector2Int operator*(Vector2Int lhs, const Vector2Int& rhs) { lhs *= rhs; return lhs; }
	friend Vector2Int operator/(Vector2Int lhs, const Vector2Int& rhs) { lhs /= rhs; return lhs; }
	friend Vector2Int operator+(Vector2Int lhs, const int rhs) { lhs += rhs; return lhs; }
	friend Vector2Int operator-(Vector2Int lhs, const int rhs) { lhs -= rhs; return lhs; }
	friend Vector2Int operator*(Vector2Int lhs, const int rhs) { lhs *= rhs; return lhs; }
	friend Vector2Int operator/(Vector2Int lhs, const int rhs) { lhs /= rhs; return lhs; }
};