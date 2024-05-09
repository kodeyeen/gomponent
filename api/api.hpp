#pragma once

#include <sdk.hpp>

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

typedef struct
{
	int model;
	int bone;
	Vector3 offset;
	Vector3 rotation;
	Vector3 scale;
	uint32_t colour1;
	uint32_t colour2;
} PlayerAttachedObject;

#ifdef __cplusplus
extern "C"
{
#endif

	GOMPONENT_EXPORT Array newArray(size_t size);

	GOMPONENT_EXPORT void freeArray(Array arr);

#ifdef __cplusplus
}
#endif
