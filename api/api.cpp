#include "api.hpp"

GOMP_EXPORT Array* newArray()
{
	Array* arr = new Array();
	return arr;
}

GOMP_EXPORT void freeArray(Array* arr)
{
	if (arr->buf)
	{
		delete[] arr->buf;
	}
	delete arr;
}