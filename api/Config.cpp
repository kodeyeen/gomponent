#include "api.hpp"
#include "GompComponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	GOMP_EXPORT void config_setPlayerMarkerMode(int mode)
	{
		auto gamemode = GompComponent::Get()->getGamemode();

		if (gamemode->config)
		{
			*gamemode->config->getInt("game.player_marker_mode") = mode;
		}
	}

	GOMP_EXPORT void config_setNametagDrawRadius(float radius)
	{
		auto gamemode = GompComponent::Get()->getGamemode();

		if (gamemode->config)
		{
			*gamemode->config->getFloat("game.nametag_draw_radius") = radius;
		}
	}
	
	GOMP_EXPORT void config_useEntryExitMarkers(int use)
	{
		auto gamemode = GompComponent::Get()->getGamemode();

		if (gamemode->config)
		{
			*gamemode->config->getBool("game.use_entry_exit_markers") = use != 0;
		}
	}

	GOMP_EXPORT void config_useManualEngineAndLights(int use)
	{
		auto gamemode = GompComponent::Get()->getGamemode();

		if (gamemode->config)
		{
			*gamemode->config->getBool("game.use_manual_engine_and_lights") = use != 0;
		}
	}

	GOMP_EXPORT void config_useNametags(int use)
	{
		auto gamemode = GompComponent::Get()->getGamemode();

		if (gamemode->config)
		{
			*gamemode->config->getBool("game.use_nametags") = use != 0;
		}
	}

#ifdef __cplusplus
}
#endif
