#include "api.hpp"
#include "Gomponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

// Pickup

	GOMPONENT_EXPORT void* pickup_create(int modelId, unsigned char type, float x, float y, float z, unsigned int virtualWorld, int isStatic, void* player)
	{
		auto gamemode = Gomponent::Get()->getGamemode();
		IPickupsComponent* pickups = gamemode->pickups;

		if (player == NULL)
		{
			if (pickups)
			{
				int id = pickups->reserveLegacyID();
				if (id == INVALID_PICKUP_ID)
				{
					return NULL;
				}

				IPickup* pickup = pickups->create(modelId, type, Vector3(x, y, z), virtualWorld, isStatic != 0);
				if (pickup)
				{
					pickups->setLegacyID(id, pickup->getID());
					return pickup;
				}
				else
				{
					pickups->releaseLegacyID(id);
					return NULL;
				}
			}
		}
		else
		{
			auto data = queryExtension<IPlayerPickupData>(static_cast<IPlayer*>(player));

			if (pickups && data)
			{
				int id = data->reserveLegacyID();
				if (id == INVALID_PICKUP_ID)
				{
					return NULL;
				}

				IPickup* pickup = pickups->create(modelId, type, Vector3(x, y, z), virtualWorld, isStatic != 0);
				if (pickup)
				{
					data->setLegacyID(id, pickup->getID());
					pickup->setLegacyPlayer(static_cast<IPlayer*>(player));
					return pickup;
				}
				else
				{
					data->releaseLegacyID(id);
					return NULL;
				}
			}
		}

		return NULL;
	}

#ifdef __cplusplus
}
#endif
