#include <sdk.hpp>
#include <iostream>
#include <Server/Components/Objects/objects.hpp>

#include "api.hpp"
#include "Gomponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	GOMPONENT_EXPORT void* object_create(int modelId, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float drawDistance)
	{
		auto gamemode = Gomponent::Get()->getGamemode();
		IObjectsComponent* component = gamemode->objects;

		if (component)
		{
			IObject* object = component->create(modelId, Vector3(posX, posY, posZ), Vector3(rotX, rotY, rotZ), drawDistance);
			if (object)
			{
				return static_cast<void*>(object);
			}
		}
		return NULL;
	}

#ifdef __cplusplus
}
#endif
