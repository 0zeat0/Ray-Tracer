#include <iostream>

#include <Windows.h>
#include "shellapi.h"
#include <filesystem>

#include "Vector3.h"
#include "JPGExporter.h"
#include "Sphere.h"
#include "Light.h"
#include "Scene.h"
#include "Material.h"
#include "Renderer.h"


//Exports rendered image as jpg file
void OnRenderFinished(unsigned char* result, unsigned int width, unsigned int height) {
    JPGExporter exporter = JPGExporter();
    exporter.Export(result, width, height, "output.jpg");
}


int main() {

    unsigned int width = 1920U;
    unsigned int height = 1080U;


    //Define materials by diffuse, specular, ambient, reflectiveness and phongExponent
    Material green = Material(
        Color(0.67f, 0.92f, 0.2f),
        Color(0.5f, 0.5f, 0.5f),
        Color(0.67f, 0.92f, 0.20f),
        Color(0.0f, 0.0f, 0.0f),
        100.0f
    );

    Material red = Material(
        Color(0.87f, 0.12f, 0.2f),
        Color(0.5f, 0.5f, 0.5f),
        Color(0.87f, 0.12f, 0.2f),
        Color(0.0, 0.0, 0.0),
        100.0f
    );

    Material orange = Material(
        Color(0.96f, 0.61f, 0.25f),
        Color(0.5f, 0.5f, 0.5f),
        Color(0.96f, 0.61f, 0.25f),
        Color(0.3f, 0.3f, 0.3f),
        1000.0f
    );

    Material blue = Material(
        Color(0.45f, 0.54f, 0.69f),
        Color(0.5f, 0.5f, 0.5f),
        Color(0.45f, 0.54f, 0.69f),
        Color(0.3f, 0.3f, 0.3f),
        1000.0f
    );


    //Create scene
    Scene scene = Scene(); 

    //Attach spheres defined by position and radius to the scene
    scene.Attach(
        &Sphere(Vector3(0.0f, 0.0f, 0.0f), 1.0f, green)
    );
    scene.Attach(
        &Sphere(Vector3(-2.0f, 1.0f, -2.0f), 2.0f, red)
    );

    scene.Attach(
        &Sphere(Vector3(1.2f, 3.0f, 1.5f), 0.8f, orange)
    );

    scene.Attach(
        &Sphere(Vector3(0.0f, -100001.0f, 0.0f), 100000.0f, blue)
    );

    //Attach light sources defined by position and intensity to the scene
    scene.Attach(
        Light(Vector3(-8.0f, 5.0f, 3.0f), 1.0f)
    );
    scene.Attach(
        Light(Vector3(2.0f, 5.0f, 5.0f), 0.5f)
    );

    //Define camera by position view direction and focal length
    Camera camera = Camera(Vector3(0.0f, 5.5f, 8.0f), Vector3(0.0f, -0.6f, -1.0f), 2.0f);

    //Define renderer
    Renderer renderer = Renderer(
        width,
        height,
        scene, 
        camera,
        Color(0.45f, 0.54f, 0.69f)*0.2f,  //background color
        0.2f //ambient intensity
    );

    //Start rendering
    renderer.Render(&OnRenderFinished);
	return 0;
}