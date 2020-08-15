#include "Sphere.h"

#include "math.h"

Sphere::Sphere() : center(Vector3()), radius(1.0f), material(Material()){}
Sphere::Sphere(Vector3 center, float radius) : center(center), radius(radius), material(Material()) {}
Sphere::Sphere(Vector3 center, float radius, Material material) : center(center), radius(radius), material(material) {}

Material Sphere::GetMaterial()
{
	return material;
}

//Finds whether the ray intersects the sphere
TraceResult Sphere::Trace(Ray ray)
{
	TraceResult result = TraceResult(false);

	float t1, t2, t;

	float discriminant = pow(Dot(ray.direction, (ray.origin - center)), 2) - 
		Dot(ray.direction, ray.direction) *
		(Dot((ray.origin - center), (ray.origin - center)) - 
		pow(radius, 2));

	if (discriminant < 0) { return result; } //No intersections
	else if (discriminant == 0) //One intersection
	{
		t1 = t2 = (Dot((ray.direction * -1), (ray.origin - center)) + sqrt(discriminant)) / Dot(ray.direction, ray.direction);
	}
	else //Two intersections
	{
		t1 = (Dot((ray.direction * -1), (ray.origin - center)) - sqrt(discriminant)) / Dot(ray.direction, ray.direction);
		t2 = (Dot((ray.direction * -1), (ray.origin - center)) + sqrt(discriminant)) / Dot(ray.direction, ray.direction);
	}

	// Find the closest non-negative intersection point
	if (t1 < t2) 
	{ 
		t = t1;  
		if (t < 0) 
		{
			t = t2; // If closest is negative use another one
			if (t < 0) return result; //Both negative 
		}
	}
	else
	{
		t = t2;
		if (t < 0) 
		{
			t = t1; // If closest is negative use another one
			if (t < 0) return result; //Both negative 
		}
	}

	result.isSuccessful = true;
	result.object = this;
	result.origin = ray.origin + ray.direction * t;
	result.normal = (result.origin - center) / radius;

	return result;
}
