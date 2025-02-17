/******************************************************************************/
/*!
\file	Vector3.cpp
\author Wen Sheng Tang \ Lim Chian Song
\par	email: tang_wen_sheng\@nyp.edu.sg
\brief
Struct to define a 3D vector
*/
/******************************************************************************/
#include <cmath>
#include "Vector3.h"

Vector3::Vector3(float a, float b, float c) : x(a), y(b), z(c)
{
}

Vector3::Vector3(const Vector3& rhs) : x(rhs.x), y(rhs.y), z(rhs.z)
{
}

Vector3::Vector3(glm::vec3 anotherVec) : x(anotherVec.x), y(anotherVec.y), z(anotherVec.z)
{
}

Vector3::~Vector3()
{
}

void Vector3::Set(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

void Vector3::SetZero(void)
{
	Set(0.0f, 0.0f, 0.0f);
}

Vector3 Vector3::operator+(const Vector3& rhs) const
{
	return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& rhs) const
{
	return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector3 Vector3::operator-(void) const
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator*(float scalar) const
{
	return Vector3(scalar * x, scalar * y, scalar * z);
}

Vector3& Vector3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

bool Vector3::operator==(const Vector3& rhs) const
{
	return (x == rhs.x) &&
		(y == rhs.y) &&
		(z == rhs.z);
}

bool Vector3::operator!= (const Vector3& rhs) const
{
	return !(x == rhs.x) &&
		!(y == rhs.y) &&
		!(z == rhs.z);
}

Vector3& Vector3::operator=(const Vector3& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

float Vector3::Length(void) const
{
	return sqrt(x * x + y * y + z * z);
}

float Vector3::LengthSquared(void) const
{
	return x * x + y * y + z * z;
}

float Vector3::Distance(const Vector3& rhs) const
{
	return (*this - rhs).Length();
}

float Vector3::DistanceSquared(const Vector3& rhs) const
{
	return (*this - rhs).LengthSquared();
}

float Vector3::Distance(const Vector3& lhs, const Vector3& rhs)
{
	return (lhs - rhs).Length();
}

float Vector3::DistanceSquared(const Vector3& lhs, const Vector3& rhs)
{
	return (lhs - rhs).LengthSquared();
}

float Vector3::Dot(const Vector3& rhs) const
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vector3 Vector3::Cross(const Vector3& rhs) const
{
	return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

Vector3 Vector3::Normalized(void) const
{
	float length = Length();
	return Vector3(x / length, y / length, z / length);
}

Vector3& Vector3::Normalize(void)
{
	float length = Length();
	x /= length;
	y /= length;
	z /= length;
	return *this;
}

Vector3 Vector3::RotateVector(const Vector3& v, float rad)
{
	float cosA = cos(rad);
	float sinA = sin(rad);

	return Vector3{ cosA * v.x - sinA * v.y, sinA * v.x + cosA * v.y };
}

glm::vec3 Vector3::convert2glm()
{
	return glm::vec3(x, y, z);
}

Vector3 operator*(float scalar, const Vector3& rhs)
{
	return rhs * scalar;
}
