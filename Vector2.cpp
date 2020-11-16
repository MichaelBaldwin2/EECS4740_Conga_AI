/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#include "Vector2.h"

const Vector2 Vector2::Zero = Vector2(0, 0);
const Vector2 Vector2::One = Vector2(1, 1);
const Vector2 Vector2::Up = Vector2(0, 1);
const Vector2 Vector2::Down = Vector2(0, -1);
const Vector2 Vector2::Left = Vector2(-1, 0);
const Vector2 Vector2::Right = Vector2(1, 0);

Vector2::Vector2(const float x, const float y) : x(x), y(y) {}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}

Vector2& Vector2::operator*=(const Vector2& rhs)
{
	this->x *= rhs.x;
	this->y *= rhs.y;
	return *this;
}

Vector2& Vector2::operator/=(const Vector2& rhs)
{
	this->x /= rhs.x;
	this->y /= rhs.y;
	return *this;
}

Vector2& Vector2::operator+=(const float rhs)
{
	this->x += rhs;
	this->y += rhs;
	return *this;
}

Vector2& Vector2::operator-=(const float rhs)
{
	this->x -= rhs;
	this->y -= rhs;
	return *this;
}

Vector2& Vector2::operator*=(const float rhs)
{
	this->x *= rhs;
	this->y *= rhs;
	return *this;
}

Vector2& Vector2::operator/=(const float rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	return *this;
}