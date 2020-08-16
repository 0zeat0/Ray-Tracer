#pragma once
#include "Object.h"

#include "Vector3.h"
#include "Material.h"


class Sphere : public Object
{
public:
	Sphere();
	Sphere(Vector3 center, float radius);
	Sphere(Vector3 center, float radius, const Material& material);

	virtual Material GetMaterial() override;
	virtual TraceResult Trace(Ray ray) override;

	Vector3 center;
	float radius;
	Material material;
};

