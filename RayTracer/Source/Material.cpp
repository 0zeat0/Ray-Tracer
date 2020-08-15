#include "Material.h"

Material::Material() : diffuse(Color(1.0f,1.0f,1.0f)),
	specular(Color(0.5f, 0.5f, 0.5f)), 
	ambient(Color(1.0f,1.0f,1.0f)),
	reflectiveness(Color(0.0f,0.0f,0.0f)),
	phongExponent(10.0f) {}

Material::Material(Color diffuse, Color specular, Color ambient, Color reflectiveness, float phongExponent) : diffuse(diffuse),
	specular(specular), 
	ambient(ambient), 
	reflectiveness(reflectiveness),
	phongExponent(phongExponent){}

