#pragma once

#include "Vector3.h"

struct Ray
{
	Ray();
	Ray(Vector3 origin, Vector3 direction);
	Vector3 origin;
	Vector3 direction;
};