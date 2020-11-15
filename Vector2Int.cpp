#include "Vector2.h"
#include "Vector2Int.h"

const Vector2Int Vector2Int::Zero = Vector2Int(0, 0);
const Vector2Int Vector2Int::One = Vector2Int(1, 1);
const Vector2Int Vector2Int::Up = Vector2Int(0, 1);
const Vector2Int Vector2Int::Down = Vector2Int(0, -1);
const Vector2Int Vector2Int::Left = Vector2Int(-1, 0);
const Vector2Int Vector2Int::Right = Vector2Int(1, 0);

Vector2Int::Vector2Int(const int x, const int y) : x(x), y(y) {}

Vector2Int::operator Vector2() const
{
	return Vector2(static_cast<float>(x), static_cast<float>(y));
}

Vector2Int& Vector2Int::operator+=(const Vector2Int& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}

Vector2Int& Vector2Int::operator-=(const Vector2Int& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}

Vector2Int& Vector2Int::operator*=(const Vector2Int& rhs)
{
	this->x *= rhs.x;
	this->y *= rhs.y;
	return *this;
}

Vector2Int& Vector2Int::operator/=(const Vector2Int& rhs)
{
	this->x /= rhs.x;
	this->y /= rhs.y;
	return *this;
}

Vector2Int& Vector2Int::operator+=(const int rhs)
{
	this->x += rhs;
	this->y += rhs;
	return *this;
}

Vector2Int& Vector2Int::operator-=(const int rhs)
{
	this->x -= rhs;
	this->y -= rhs;
	return *this;
}

Vector2Int& Vector2Int::operator*=(const int rhs)
{
	this->x *= rhs;
	this->y *= rhs;
	return *this;
}

Vector2Int& Vector2Int::operator/=(const int rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	return *this;
}