#include "Light.h"

Light::Light() : position(Vector3()), intensity(1){}
Light::Light(Vector3 position, float intensity) : position(position), intensity(intensity) {}

