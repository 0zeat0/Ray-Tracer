#pragma once

#include <vector>

#include "Object.h"
#include "Light.h"

class Scene
{
public:
	Scene();
	void Attach(Object* object);
	void Attach(Light light);
	std::vector<Object*> GetObjects();
	std::vector<Light> GetLights();
private:
	std::vector<Object*> objects;
	std::vector<Light> lights;
};

