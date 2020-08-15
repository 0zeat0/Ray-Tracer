#include "Renderer.h"

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>


#include "TraceResult.h"

Renderer::Renderer(unsigned int width, unsigned int height, Scene& scene, Camera camera, Color backgroundColor, float ambientIntensity) : 
	width(width),
	height(height),
	scene(scene),
	camera(camera),
	backgroundColor(backgroundColor),
	ambientIntensity(ambientIntensity) 
{
	aspectRatio = static_cast<float>(width) / height;

	viewPlaneLeftEdge = -1 * aspectRatio;
	viewPlaneRightEdge = 1 * aspectRatio;
	viewPlaneBottomEdge = -1;
	viewPlaneTopEdge = 1;

	image = new Color[width * height];
	for (unsigned int i = 0; i < width * height; i++)
	{
		image[i] = backgroundColor;
	}
}

Renderer::~Renderer()
{
	delete[] image;
}

//Finds ray origin and direction by pixel coordinates
Ray Renderer::ComputeRay(unsigned int i, unsigned int j)
{
	float u = viewPlaneLeftEdge + (viewPlaneRightEdge - viewPlaneLeftEdge) * (i + 0.5f) / width;
	float v = viewPlaneBottomEdge + (viewPlaneTopEdge - viewPlaneBottomEdge) * (j + 0.5f) / height;

	return Ray(
		camera.position,
		(camera.W * (camera.focalLength * -1)) + (camera.U * u) + (camera.V * v)
	);
}



// Renders the image and calls a callback when rendering is finished
void Renderer::Render(void(*OnRenderFinished)(unsigned char* result, unsigned int width, unsigned int height))
{
	std::cout << "Rendering started!\n";

	std::vector<Object*> objects = scene.GetObjects();

	//Go through all pixels in the image
	for (unsigned int i = 0; i < width; i++)
	{
		for (unsigned int j = 0; j < height; j++)
		{
			//For each pixel compute the ray origin
			//and direction by pixel coordinates
			Ray ray = ComputeRay(i, j);

			TraceResult traceResult = TraceResult(false);

			float closestZ = -std::numeric_limits<float>::infinity(); 

			//Go through all objects in the scene and 
			//trace a ray(find the closest intersection point if such exists)
			for (int k = 0; k < objects.size(); k++) {
				TraceResult perObjectResult = objects[k]->Trace(ray);
				if (perObjectResult.isSuccessful && perObjectResult.origin.z > closestZ) { 
					closestZ = perObjectResult.origin.z; 
					traceResult = perObjectResult;
				}
			}

			//If trace is successful(intersection exists and valid)
			//shade the pixel
			if (traceResult.isSuccessful) {
				image[j * width + i] = Shade(traceResult, true);
			}
		}
	}

	std::cout << "Rendering finished!\n";
	OnRenderFinished(GetResult(), width, height);
}

Color Renderer::Shade(TraceResult traceResult, bool shouldComputeReflections)
{
	std::vector<Object*> objects = scene.GetObjects();
	std::vector<Light> lights = scene.GetLights();

	Material material = traceResult.object->GetMaterial();

	//By default resulting color is equal to ambient color
	Color color = material.ambient * ambientIntensity;

	//Variables below are used to prevent 
	//shadow and reflection rays from intersection 
	//with surface located at ray's origin
	float shadowRayAdjustment = 0.8f; 
	float reflectionRayAdjustment;

	float distance = (camera.position - traceResult.origin).Length();

	if (distance < 20) {
		reflectionRayAdjustment = 0.3f;
	}
	else
	{
		reflectionRayAdjustment = 5.0f;
	}

	//Go through all light sources in the scene
	for (int i = 0; i < lights.size(); i++) {

		Vector3 toLight = (lights[i].position - traceResult.origin).Normalize();
		
		Ray shadowRay = Ray(traceResult.origin + toLight * shadowRayAdjustment, toLight);

		bool isInShadow = false;

		//Find whether the current point is in shadow by 
		//tracing a ray toward the light source
		for (int j = 0; j < objects.size() && isInShadow == false; j++) {
		TraceResult perObjectResult = objects[j]->Trace(shadowRay);
			if (perObjectResult.isSuccessful) {
				isInShadow = true;
			}
		}

		//If not in shadow then also compute diffuse and specular
		if (!isInShadow)
		{
			Color diffuse = Color(
				material.diffuse.R * lights[i].intensity * std::max(0.0f, Dot(traceResult.normal, toLight)),
				material.diffuse.G * lights[i].intensity * std::max(0.0f, Dot(traceResult.normal, toLight)),
				material.diffuse.B * lights[i].intensity * std::max(0.0f, Dot(traceResult.normal, toLight))
			);

			Vector3 toCamera = (camera.position - traceResult.origin).Normalize();

			Vector3 halfVector = (toCamera + toLight).Normalize();

			Color specular = Color(
				material.specular.R * lights[i].intensity * pow(std::max(0.0f, Dot(traceResult.normal, halfVector)), material.phongExponent),
				material.specular.G * lights[i].intensity * pow(std::max(0.0f, Dot(traceResult.normal, halfVector)), material.phongExponent),
				material.specular.B * lights[i].intensity * pow(std::max(0.0f, Dot(traceResult.normal, halfVector)), material.phongExponent)
			);

			//The resulting color is the sum of ambient, diffuse and specular
			//for each light source
			color = color + diffuse + specular;
		}

	}

	//Add reflection to the resulting color 
	if (shouldComputeReflections) {

		Vector3 toOrigin = (traceResult.origin - camera.position).Normalize();
		Vector3 reflectionDirection = toOrigin - 2 * Dot(toOrigin, traceResult.normal) * traceResult.normal;

		Ray reflectionRay = Ray(traceResult.origin + reflectionDirection * reflectionRayAdjustment, reflectionDirection);

		TraceResult reflectionResult = TraceResult(false);

		float closestZ = -std::numeric_limits<float>::infinity();

		//Go through all objects in the scene and 
		//trace a ray(find the closest intersection point if such exists)
		for (int j = 0; j < objects.size(); j++) {
			TraceResult perObjectResult = objects[j]->Trace(reflectionRay);
			if (perObjectResult.isSuccessful && perObjectResult.origin.z > closestZ) {
				closestZ = perObjectResult.origin.z;
				reflectionResult = perObjectResult;
			}
		}

		//If the trace is successful(object reflects another object) 
		if (reflectionResult.isSuccessful) {

			//Find the color of reflection by shading using the intersection point
			Color reflectionColor = Shade(reflectionResult, false);

			Color reflection = Color(
				material.reflectiveness.R * reflectionColor.R,
				material.reflectiveness.G * reflectionColor.G,
				material.reflectiveness.B * reflectionColor.B
			);

			//The resulting color is the sum of ambient, diffuse, specular and reflection
			color = color + reflection;
		}	
	}
	
	return color;
}

//Returns resulting image as an array of bytes
unsigned char* Renderer::GetResult()
{
	unsigned char* result = new unsigned char[(width * height * 3U)];

	unsigned int i = 0;
	unsigned int j = 0;

	while (i < width * height) {
		result[j] = static_cast<unsigned char>(image[i].R * 255);
		result[j + 1] = static_cast<unsigned char>(image[i].G * 255);
		result[j + 2] = static_cast<unsigned char>(image[i].B * 255);
		i++;
		j += 3;
	}
	return result;
}
