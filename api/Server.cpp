#include "api.hpp"
#include "Gomponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	GOMPONENT_EXPORT void server_setModeText(String text)
	{
		auto gamemode = Gomponent::Get()->getGamemode();

		if (gamemode->core)
		{
			gamemode->core->setData(SettableCoreDataType::ModeText, StringView(text.buf, text.length));
		}
	}

	GOMPONENT_EXPORT void server_setWeather(int weather)
	{
		auto gamemode = Gomponent::Get()->getGamemode();

		if (gamemode->core)
		{
			gamemode->core->setWeather(weather);
		}
	}

	GOMPONENT_EXPORT void server_setWorldTime(int hours)
	{
		auto gamemode = Gomponent::Get()->getGamemode();

		if (gamemode->core)
		{
			gamemode->core->setWorldTime(Hours(hours));
		}
	}

	GOMPONENT_EXPORT void server_enableStuntBonuses()
	{
		auto gamemode = Gomponent::Get()->getGamemode();

		if (gamemode->core)
		{
			gamemode->core->useStuntBonuses(true);
		}
	}

#ifdef __cplusplus
}
#endif
