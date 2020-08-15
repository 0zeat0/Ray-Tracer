#pragma once

#include <iostream>

class Vector3
{
public:
	Vector3();
	Vector3(float value);
	Vector3(float x, float y, float z);

	float Length();

	Vector3& Normalize();

	friend float Dot(const Vector3& a, const Vector3& b);
	friend Vector3 Cross(const Vector3& a, const Vector3& b);
	friend std::ostream& operator<<(std::ostream& os, const Vector3& vector);

	float x;
	float y;
	float z;

};

Vector3 operator * (const Vector3& vector, const float value);
Vector3 operator * (const float value, const Vector3& vector);
Vector3 operator / (const Vector3& vector, const float value);
Vector3 operator + (const Vector3& a, const Vector3& b);
Vector3 operator - (const Vector3& a, const Vector3& b);
