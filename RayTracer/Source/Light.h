#pragma once

#include "Vector3.h"

struct Light
{
	Light();
	Light(Vector3 position, float intensity);
	Vector3 position;
	float intensity;
};