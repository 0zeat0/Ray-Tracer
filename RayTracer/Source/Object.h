#pragma once

#include "TraceResult.h"
#include "Ray.h"
#include "Material.h"

class Object
{
public:
	virtual Material GetMaterial() = 0;
	virtual TraceResult Trace(Ray ray) = 0;
};
