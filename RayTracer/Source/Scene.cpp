#include "Scene.h"

Scene::Scene(){}

void Scene::Attach(Object* object)
{
	objects.push_back(object);
}

void Scene::Attach(Light light)
{
	lights.push_back(light);
}

std::vector<Object*> Scene::GetObjects()
{
	return objects;
}

std::vector<Light> Scene::GetLights()
{
	return lights;
}
