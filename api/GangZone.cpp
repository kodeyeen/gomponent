#include <sdk.hpp>
#include "Server/Components/GangZones/gangzones.hpp"

#include "api.hpp"
#include "Gomponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	GOMPONENT_EXPORT void* gangZone_create(float minX, float minY, float maxX, float maxY)
	{
		auto gamemode = Gomponent::Get()->getGamemode();
		IGangZonesComponent* component = gamemode->gangzones;

		if (component)
		{
			GangZonePos pos;
			pos.min.x = truncf(minX);
			pos.min.y = truncf(minY);
			pos.max.x = truncf(maxX);
			pos.max.y = truncf(maxY);

			IGangZone* gangZone = component->create(pos);

			return static_cast<void*>(gangZone);
		}

		return NULL;
	}

	GOMPONENT_EXPORT void gangZone_release(void* gangZone)
	{
		auto gamemode = Gomponent::Get()->getGamemode();
		IGangZonesComponent* component = gamemode->gangzones;

		if (component)
		{
			component->release(static_cast<IGangZone*>(gangZone)->getID());
		}
	}

	GOMPONENT_EXPORT void gangZone_useCheck(void* gangZone, unsigned char use)
	{
		auto gamemode = Gomponent::Get()->getGamemode();
		IGangZonesComponent* component = gamemode->gangzones;

		if (component)
		{
			component->useGangZoneCheck(*static_cast<IGangZone*>(gangZone), use != 0);
		}
	}

	GOMPONENT_EXPORT unsigned char gangZone_isShownForPlayer(void* gangZone, void* player)
	{
		return static_cast<IGangZone*>(gangZone)->isShownForPlayer(*static_cast<IPlayer*>(player)) ? 1 : 0;
	}

	GOMPONENT_EXPORT unsigned char gangZone_isFlashingForPlayer(void* gangZone, void* player)
	{
		return static_cast<IGangZone*>(gangZone)->isFlashingForPlayer(*static_cast<IPlayer*>(player)) ? 1 : 0;
	}

	GOMPONENT_EXPORT void gangZone_showForPlayer(void* gangZone, void* player, uint32_t colour)
	{
		return static_cast<IGangZone*>(gangZone)->showForPlayer(*static_cast<IPlayer*>(player), Colour::FromRGBA(colour));
	}

	GOMPONENT_EXPORT void gangZone_showForAll(void* gangZone, uint32_t colour)
	{
		auto gamemode = Gomponent::Get()->getGamemode();
		IPlayerPool* players = gamemode->players;

		for (IPlayer* player : players->entries())
		{
			static_cast<IGangZone*>(gangZone)->showForPlayer(*player, Colour::FromRGBA(colour));
		}
	}

	GOMPONENT_EXPORT void gangZone_hideForPlayer(void* gangZone, void* player)
	{
		return static_cast<IGangZone*>(gangZone)->hideForPlayer(*static_cast<IPlayer*>(player));
	}

	GOMPONENT_EXPORT void gangZone_hideForAll(void* gangZone)
	{
		auto gamemode = Gomponent::Get()->getGamemode();
		IPlayerPool* players = gamemode->players;

		for (IPlayer* player : players->entries())
		{
			static_cast<IGangZone*>(gangZone)->hideForPlayer(*player);
		}
	}

	GOMPONENT_EXPORT void gangZone_flashForPlayer(void* gangZone, void* player, uint32_t colour)
	{
		return static_cast<IGangZone*>(gangZone)->flashForPlayer(*static_cast<IPlayer*>(player), Colour::FromRGBA(colour));
	}

	GOMPONENT_EXPORT void gangZone_flashForAll(void* gangZone, uint32_t colour)
	{
		auto gamemode = Gomponent::Get()->getGamemode();
		IPlayerPool* players = gamemode->players;

		for (IPlayer* player : players->entries())
		{
			static_cast<IGangZone*>(gangZone)->flashForPlayer(*player, Colour::FromRGBA(colour));
		}
	}

	GOMPONENT_EXPORT void gangZone_stopFlashForPlayer(void* gangZone, void* player)
	{
		return static_cast<IGangZone*>(gangZone)->stopFlashForPlayer(*static_cast<IPlayer*>(player));
	}

	GOMPONENT_EXPORT void gangZone_stopFlashForAll(void* gangZone)
	{
		auto gamemode = Gomponent::Get()->getGamemode();
		IPlayerPool* players = gamemode->players;

		for (IPlayer* player : players->entries())
		{
			static_cast<IGangZone*>(gangZone)->stopFlashForPlayer(*player);
		}
	}

	GOMPONENT_EXPORT GangZonePos gangZone_getPosition(void* gangZone)
	{
		return static_cast<IGangZone*>(gangZone)->getPosition();
	}

	GOMPONENT_EXPORT void gangZone_setPosition(void* gangZone, float minX, float minY, float maxX, float maxY)
	{
		GangZonePos pos;
		pos.min.x = truncf(minX);
		pos.min.y = truncf(minY);
		pos.max.x = truncf(maxX);
		pos.max.y = truncf(maxY);

		return static_cast<IGangZone*>(gangZone)->setPosition(pos);
	}

	GOMPONENT_EXPORT unsigned char gangZone_isPlayerInside(void* gangZone, void* player)
	{
		return static_cast<IGangZone*>(gangZone)->isPlayerInside(*static_cast<IPlayer*>(player)) ? 1 : 0;
	}

	// getShownFor

	GOMPONENT_EXPORT uint32_t gangZone_getFlashingColourForPlayer(void* gangZone, void* player)
	{
		return static_cast<IGangZone*>(gangZone)->getFlashingColourForPlayer(*static_cast<IPlayer*>(player)).RGBA();
	}

	GOMPONENT_EXPORT uint32_t gangZone_getColourForPlayer(void* gangZone, void* player)
	{
		return static_cast<IGangZone*>(gangZone)->getColourForPlayer(*static_cast<IPlayer*>(player)).RGBA();
	}

#ifdef __cplusplus
}
#endif
