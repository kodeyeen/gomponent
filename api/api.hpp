#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define GOMPONENT_EXPORT __declspec(dllexport)
#else
#define GOMPONENT_EXPORT __attribute__((visibility("default")))
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

GOMPONENT_EXPORT Array* newArray();

GOMPONENT_EXPORT void freeArray(Array* arr);
