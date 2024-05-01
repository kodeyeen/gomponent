#include "api.hpp"
#include "Gomponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

// Pickup

	GOMPONENT_EXPORT void* pickup_create(int modelId, uint8_t type, float posX, float posY, float posZ, uint32_t virtualWorld, int isStatic)
	{
		IPickupsComponent* pickups = Gomponent::Get()->pickups;

		if (pickups)
		{
			int id = pickups->reserveLegacyID();
			if (id == INVALID_PICKUP_ID)
			{
				return NULL;
			}

			IPickup* pickup = pickups->create(modelId, type, Vector3(posX, posY, posZ), virtualWorld, false);

			if (pickup)
			{
				pickups->setLegacyID(id, pickup->getID());
				return static_cast<void*>(pickup);
			}
			else
			{
				pickups->releaseLegacyID(id);
			}
		}

		return NULL;
	}

	GOMPONENT_EXPORT void pickup_release(void* pickup)
	{
		IPickupsComponent* pickups = Gomponent::Get()->pickups;

		if (pickups)
		{
			int legacyid = static_cast<IPickup*>(pickup)->getID();
			int realid = pickups->fromLegacyID(legacyid);
			if (realid)
			{
				pickups->release(realid);
				pickups->releaseLegacyID(legacyid);
			}
		}
	}

	GOMPONENT_EXPORT int pickup_getID(void* pickup)
	{
		return static_cast<IPickup*>(pickup)->getID();
	}

	GOMPONENT_EXPORT void pickup_setType(void* pickup, uint8_t type)
	{
		static_cast<IPickup*>(pickup)->setType(type);
	}

	GOMPONENT_EXPORT uint8_t pickup_getType(void* pickup)
	{
		return static_cast<IPickup*>(pickup)->getType();
	}

	GOMPONENT_EXPORT void pickup_setModel(void* pickup, int model)
	{
		static_cast<IPickup*>(pickup)->setModel(model);
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
		static_cast<IPickup*>(pickup)->setPickupHiddenForPlayer(*static_cast<IPlayer*>(player), hidden != 0);
	}

	GOMPONENT_EXPORT unsigned char pickup_isPickupHiddenForPlayer(void* pickup, void* player)
	{
		return static_cast<IPickup*>(pickup)->isPickupHiddenForPlayer(*static_cast<IPlayer*>(player)) ? 1 : 0;
	}

	// entity

	GOMPONENT_EXPORT void pickup_setPosition(void* pickup, float posX, float posY, float posZ)
	{
		static_cast<IPickup*>(pickup)->setPosition(Vector3(posX, posY, posZ));
	}

	GOMPONENT_EXPORT Vector3 pickup_getPosition(void* pickup)
	{
		return static_cast<IPickup*>(pickup)->getPosition();
	}

	GOMPONENT_EXPORT void pickup_setVirtualWorld(void* pickup, int vw)
	{
		static_cast<IPickup*>(pickup)->setVirtualWorld(vw);
	}

	GOMPONENT_EXPORT int pickup_getVirtualWorld(void* pickup)
	{
		return static_cast<IPickup*>(pickup)->getVirtualWorld();
	}

	// PlayerPickup

	GOMPONENT_EXPORT void* playerPickup_create(void* player, int modelId, uint8_t type, float posX, float posY, float posZ, uint32_t virtualWorld, int isStatic)
	{
		IPickupsComponent* pickups = Gomponent::Get()->pickups;
		IPlayerPickupData* data = queryExtension<IPlayerPickupData>(static_cast<IPlayer*>(player));

		if (pickups && data)
		{
			int id = data->reserveLegacyID();
			if (id == INVALID_PICKUP_ID)
			{
				return NULL;
			}

			IPickup* pickup = pickups->create(modelId, type, Vector3(posX, posY, posZ), virtualWorld, false);
			if (pickup)
			{
				data->setLegacyID(id, pickup->getID());
				pickup->setLegacyPlayer(static_cast<IPlayer*>(player));
				return static_cast<void*>(pickup);
			}
			else
			{
				data->releaseLegacyID(id);
			}
		}

		return NULL;
	}

	GOMPONENT_EXPORT void playerPickup_release(void* pickup, void* player)
	{
		IPickupsComponent* pickups = Gomponent::Get()->pickups;
		IPlayerPickupData* data = queryExtension<IPlayerPickupData>(static_cast<IPlayer*>(player));

		if (pickups && data)
		{
			int legacyid = static_cast<IPickup*>(pickup)->getID();
			int realid = data->fromLegacyID(legacyid);
			if (realid)
			{
				pickups->release(realid);
				data->releaseLegacyID(legacyid);
			}
		}
	}

#ifdef __cplusplus
}
#endif
