#include "api.hpp"

GOMPONENT_EXPORT Array* newArray()
{
	Array* arr = new Array();
	return arr;
}

GOMPONENT_EXPORT void freeArray(Array* arr)
{
	if (arr->buf)
	{
		delete[] arr->buf;
	}
	delete arr;
}