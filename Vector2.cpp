#include "Vector2.h"

const Vector2 Vector2::Zero = Vector2(0, 0);
const Vector2 Vector2::One = Vector2(1, 1);
const Vector2 Vector2::Up = Vector2(0, 1);
const Vector2 Vector2::Down = Vector2(0, -1);
const Vector2 Vector2::Left = Vector2(-1, 0);
const Vector2 Vector2::Right = Vector2(1, 0);

Vector2::Vector2(const float x, const float y) : x(x), y(y) {}

Vector2::operator SDL_Point() const
{
	return { static_cast<int>(x), static_cast<int>(y) };
}

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