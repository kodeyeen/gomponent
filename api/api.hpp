#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define GOMP_EXPORT __declspec(dllexport)
#else
#define GOMP_EXPORT __attribute__((visibility("default")))
#endif

typedef struct
{
	int primary;
	int secondary;
} VehicleColour;

typedef struct
{
	const char* buf;
	size_t length;
} String;

typedef struct
{
	void** buf;
	size_t length;
} Array;

GOMP_EXPORT Array* newArray();

GOMP_EXPORT void freeArray(Array* arr);
