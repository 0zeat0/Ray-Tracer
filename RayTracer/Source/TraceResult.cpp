#include "TraceResult.h"

TraceResult::TraceResult() : isSuccessful(false), normal(Vector3()), origin(Vector3()), object(nullptr) {}
TraceResult::TraceResult(bool isSuccessful) : isSuccessful(isSuccessful), normal(Vector3()), origin(Vector3()), object(nullptr) {}

