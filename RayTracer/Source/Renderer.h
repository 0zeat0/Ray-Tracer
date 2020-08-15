#pragma once

#include "Color.h"
#include "Scene.h"
#include "Camera.h"
#include "Ray.h"


class Renderer
{
public:
	Renderer(unsigned int width, unsigned int height, Scene& scene, Camera camera, Color backgroundColor, float ambientIntensity);
	~Renderer();
	Ray ComputeRay(unsigned int i, unsigned int j);
	void Render(void(*OnRenderFinished)(unsigned char* result, unsigned int width, unsigned int height));
	Color Shade(TraceResult traceResult, bool shouldComputeReflections);
	unsigned char* GetResult();

private:
	unsigned int width;
	unsigned int height;
	float aspectRatio;

	float viewPlaneLeftEdge;
	float viewPlaneRightEdge;
	float viewPlaneBottomEdge;
	float viewPlaneTopEdge;

	Color backgroundColor;
	float ambientIntensity;

	Scene& scene;
	Camera camera;
	Color* image;
};

