#pragma once

#include "Vector3.h"

class Object;

struct TraceResult
{
	TraceResult();
	TraceResult(bool isSuccessful);

	bool isSuccessful;

	Object* object;
	Vector3 normal;
	Vector3 origin;
};