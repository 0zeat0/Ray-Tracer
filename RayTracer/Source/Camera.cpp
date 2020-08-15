#include "Camera.h"

Camera::Camera(Vector3 position, Vector3 viewDirection, float focalLength) : position(position), focalLength(focalLength)
{
	//Defining camera frame
	W = (viewDirection*-1).Normalize();
	U = Cross(Vector3(0, 1, 0), W).Normalize();
	V = Cross(U, W);
}
