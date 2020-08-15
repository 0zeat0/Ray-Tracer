#pragma once

#include "Color.h"

struct Material
{
	Material();
	Material(Color diffuse, Color specular, Color ambient, Color reflectiveness, float phongExponent);

	Color diffuse;
	Color specular;
	Color ambient;
	Color reflectiveness;
	float phongExponent;
};