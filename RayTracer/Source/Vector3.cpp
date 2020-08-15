#include "Vector3.h"

#include "math.h"

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
Vector3::Vector3(float value) : x(value), y(value), z(value) {}
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

//Returns the length of the vector
float Vector3::Length()
{
	return sqrt((x * x) + (y * y) + (z * z));
}

//Normalizes the vector
Vector3& Vector3::Normalize()
{
	float length = Length();
	if (length != 0) {
		length = 1 / length;
		x = x * length;
		y = y * length;
		z = z * length;
	}
	return *this;
}


//Returns the dot product of two vectors
float Dot(const Vector3& a, const Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

//Returns the cross product of two vectors
Vector3 Cross(const Vector3& a, const Vector3& b)
{
	return Vector3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

std::ostream& operator<<(std::ostream& os, const Vector3& vector)
{
	os << "{ " << vector.x << ", " << vector.y << ", " << vector.z << " }";
	return os;
}

Vector3 operator*(const Vector3& vector, float value)
{
	return Vector3(vector.x * value, vector.y * value, vector.z * value);
}

Vector3 operator*(float value, const Vector3& vector)
{
	return Vector3(vector.x * value, vector.y * value, vector.z * value);
}

Vector3 operator/(const Vector3& vector, const float value)
{
	return Vector3(vector.x / value, vector.y / value, vector.z / value);
}

Vector3 operator+(const Vector3& a, const Vector3& b)
{
	return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3 operator-(const Vector3& a, const Vector3& b)
{
	return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}
