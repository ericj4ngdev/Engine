#include "include.h"


Vector2::Vector2() {}
Vector2::~Vector2() {}

Vector2 Vector2::operator +(const Vector2& v) const
{
	return Vector2(x + v.x, y + v.y);
}
Vector2 Vector2::operator -(const Vector2& v) const
{
	return Vector2(x - v.x, y - v.y);
}
Vector2 Vector2::operator *(float v) const
{
	return Vector2(x * v, y * v);
}
Vector2 Vector2::operator /(float v) const
{
	return Vector2(x / v, y / v);
}
float Vector2::Dot(const Vector2& v) const {
	return x * v.x + y * v.y;
}
void Vector2::operator +=(const Vector2& v)
{
	*this = Vector2(x + v.x, y + v.y);
}
void Vector2::operator -=(const Vector2& v)
{
	*this = Vector2(x - v.x, y - v.y);
}
void Vector2::operator *=(float v) {
	*this = Vector2(x * v, y * v);
}
void Vector2::operator /=(float v)
{
	*this = Vector2(x / v, y / v);
}
bool Vector2::operator ==(const Vector2& v)const
{
	return x == v.x && y == v.y;
}
Vector2 Vector2::Cross(const Vector2& v) const
{
	return Vector2(x, y);
}
Vector2 Vector2::Normalize()
{
	float k = sqrt(pow(x, 2) + pow(y, 2));
	if (k == 0.0)
		return Vector2(0.0, 0.0);
	else
	{
		x = x / k;
		y = y / k;
		return Vector2(x, y);
	}
}
float Vector2::Length()
{
	float w = sqrt(pow((float)x, 2) + pow((float)y, 2));
	return w;
}