#include <sdk.hpp>
#include <iostream>
#include "Server/Components/Classes/classes.hpp"

#include "api.hpp"
#include "Gomponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct ClassData
	{
		int team;
		int skin;
		float spawnX;
		float spawnY;
		float spawnZ;
		float angle;
		uint8_t weapon1;
		uint32_t ammo1;
		uint8_t weapon2;
		uint32_t ammo2;
		uint8_t weapon3;
		uint32_t ammo3;
	} ClassData;

	GOMPONENT_EXPORT void* class_create(ClassData* data)
	{
		auto gamemode = Gomponent::Get()->getGamemode();
		IClassesComponent* classes = gamemode->classes;

		if (classes)
		{
			WeaponSlots slots = {
				WeaponSlotData { data->weapon1, data->ammo1 },
				WeaponSlotData { data->weapon2, data->ammo2 },
				WeaponSlotData { data->weapon3, data->ammo3 }
			};

			IClass* _class = classes->create(data->skin, data->team, Vector3(data->spawnX, data->spawnY, data->spawnZ), data->angle, slots);
			if (_class)
			{
				return _class;
			}
		}

		return NULL;
	}

	GOMPONENT_EXPORT int class_getID(void* class_)
	{
		return static_cast<IClass*>(class_)->getID();
	}

	GOMPONENT_EXPORT void class_setClass(void* class_, ClassData* data)
	{
		WeaponSlots weapons;
		weapons[0].id = data->weapon1;
		weapons[0].ammo = data->ammo1;
		weapons[1].id = data->weapon2;
		weapons[1].ammo = data->ammo2;
		weapons[2].id = data->weapon3;
		weapons[2].ammo = data->ammo3;

		PlayerClass playerCls = PlayerClass(data->skin, data->team, Vector3(data->spawnX, data->spawnY, data->spawnZ), data->angle, weapons);

		static_cast<IClass*>(class_)->setClass(playerCls);
	}

	GOMPONENT_EXPORT ClassData class_getClass(void* class_)
	{
		const PlayerClass& playerCls = static_cast<IClass*>(class_)->getClass();

		return {
			playerCls.team,
			playerCls.skin,
			playerCls.spawn.x,
			playerCls.spawn.y,
			playerCls.spawn.z,
			playerCls.angle,
			playerCls.weapons[0].id,
			playerCls.weapons[0].ammo,
			playerCls.weapons[1].id,
			playerCls.weapons[1].ammo,
			playerCls.weapons[2].id,
			playerCls.weapons[2].ammo,
		};
	}

#ifdef __cplusplus
}
#endif
