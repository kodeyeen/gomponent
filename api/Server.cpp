#include "api.hpp"
#include "GompComponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	GOMP_EXPORT void server_setModeText(String text)
	{
		auto gamemode = GompComponent::Get()->getGamemode();

		if (gamemode->core)
		{
			gamemode->core->setData(SettableCoreDataType::ModeText, StringView(text.buf, text.length));
		}
	}

	GOMP_EXPORT void server_setWeather(int weather)
	{
		auto gamemode = GompComponent::Get()->getGamemode();

		if (gamemode->core)
		{
			gamemode->core->setWeather(weather);
		}
	}

	GOMP_EXPORT void server_setWorldTime(int hours)
	{
		auto gamemode = GompComponent::Get()->getGamemode();

		if (gamemode->core)
		{
			gamemode->core->setWorldTime(Hours(hours));
		}
	}

	GOMP_EXPORT void server_enableStuntBonuses()
	{
		auto gamemode = GompComponent::Get()->getGamemode();

		if (gamemode->core)
		{
			gamemode->core->useStuntBonuses(true);
		}
	}

#ifdef __cplusplus
}
#endif
