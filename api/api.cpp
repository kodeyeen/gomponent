#include "api.hpp"
#include "Gomponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

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

	GOMPONENT_EXPORT uint8_t getWeaponSlotIndex(uint8_t weapon)
	{
		return WeaponSlotData { weapon }.slot();
	}

	GOMPONENT_EXPORT unsigned char getVehicleModelInfo(int model, int type, Vector3* out)
	{
		return Impl::getVehicleModelInfo(model, VehicleModelInfoType(type), *out) ? 1 : 0;
	}

#ifdef __cplusplus
}
#endif
