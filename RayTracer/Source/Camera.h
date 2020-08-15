#pragma once

#include "Vector3.h"

struct Camera
{
	Camera(Vector3 position, Vector3 viewDirection, float focalLength);
	Vector3 position;
	float focalLength;
	Vector3 U;
	Vector3 V;
	Vector3 W;
};