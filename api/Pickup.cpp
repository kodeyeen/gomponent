#include "api.hpp"
#include "Gomponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

// Pickup

	GOMPONENT_EXPORT void* pickup_create(int modelId, uint8_t type, float posX, float posY, float posZ, uint32_t virtualWorld, int isStatic)
	{
		auto gamemode = Gomponent::Get()->getGamemode();
		IPickupsComponent* component = gamemode->pickups;

		if (component)
		{
			IPickup* pickup = component->create(modelId, type, Vector3(posX, posY, posZ), virtualWorld, false);

			return static_cast<void*>(pickup);
		}

		return NULL;
	}

	GOMPONENT_EXPORT void pickup_release(void* pickup)
	{
		auto gamemode = Gomponent::Get()->getGamemode();
		IPickupsComponent* component = gamemode->pickups;

		if (component)
		{
			component->release(static_cast<IPickup*>(pickup)->getID());
		}
	}

	GOMPONENT_EXPORT int pickup_getID(void* pickup)
	{
		return static_cast<IPickup*>(pickup)->getID();
	}

	GOMPONENT_EXPORT void pickup_setType(void* pickup, uint8_t type)
	{
		return static_cast<IPickup*>(pickup)->setType(type);
	}

	GOMPONENT_EXPORT uint8_t pickup_getType(void* pickup)
	{
		return static_cast<IPickup*>(pickup)->getType();
	}

	GOMPONENT_EXPORT void pickup_setModel(void* pickup, int model)
	{
		return static_cast<IPickup*>(pickup)->setModel(model);
	}

	GOMPONENT_EXPORT int pickup_getModel(void* pickup)
	{
		return static_cast<IPickup*>(pickup)->getModel();
	}

	GOMPONENT_EXPORT unsigned char pickup_isStreamedInForPlayer(void* pickup, void* player)
	{
		return static_cast<IPickup*>(pickup)->isStreamedInForPlayer(*static_cast<IPlayer*>(player)) ? 1 : 0;
	}

	GOMPONENT_EXPORT void pickup_setPickupHiddenForPlayer(void* pickup, void* player, unsigned char hidden)
	{
		return static_cast<IPickup*>(pickup)->setPickupHiddenForPlayer(*static_cast<IPlayer*>(player), hidden != 0);
	}

	GOMPONENT_EXPORT unsigned char pickup_isPickupHiddenForPlayer(void* pickup, void* player)
	{
		return static_cast<IPickup*>(pickup)->isPickupHiddenForPlayer(*static_cast<IPlayer*>(player)) ? 1 : 0;
	}

	// entity

	GOMPONENT_EXPORT void pickup_setPosition(void* pickup, float posX, float posY, float posZ)
	{
		return static_cast<IPickup*>(pickup)->setPosition(Vector3(posX, posY, posZ));
	}

	GOMPONENT_EXPORT Vector3 pickup_getPosition(void* pickup)
	{
		return static_cast<IPickup*>(pickup)->getPosition();
	}

	GOMPONENT_EXPORT void pickup_setVirtualWorld(void* pickup, int vw)
	{
		return static_cast<IPickup*>(pickup)->setVirtualWorld(vw);
	}

	GOMPONENT_EXPORT int pickup_getVirtualWorld(void* pickup)
	{
		return static_cast<IPickup*>(pickup)->getVirtualWorld();
	}

#ifdef __cplusplus
}
#endif
