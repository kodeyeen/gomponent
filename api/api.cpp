#include "api.hpp"

GOMPONENT_EXPORT Array newArray(size_t size)
{
	Array arr;
	arr.length = size;
	arr.buf = new void*[arr.length];

	return arr;
}

GOMPONENT_EXPORT void freeArray(Array arr)
{
	if (arr.buf)
	{
		delete[] arr.buf;
	}
}
