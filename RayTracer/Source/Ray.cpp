#include "Ray.h"

Ray::Ray() : origin(Vector3()), direction(Vector3()){}
Ray::Ray(Vector3 origin, Vector3 direction) : origin(origin), direction(direction){}
