#include "api.hpp"
#include "Gomponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	GOMPONENT_EXPORT void config_setFloat(String key, float value)
	{
		auto gamemode = Gomponent::Get()->getGamemode();

		if (gamemode->config)
		{
			*gamemode->config->getFloat(StringView(key.buf, key.length)) = value;
		}
	}

	GOMPONENT_EXPORT void config_setInt(String key, int value)
	{
		auto gamemode = Gomponent::Get()->getGamemode();

		if (gamemode->config)
		{
			*gamemode->config->getInt(StringView(key.buf, key.length)) = value;
		}
	}

	GOMPONENT_EXPORT void config_setBool(String key, unsigned char value)
	{
		auto gamemode = Gomponent::Get()->getGamemode();

		if (gamemode->config)
		{
			*gamemode->config->getBool(StringView(key.buf, key.length)) = value != 0;
		}
	}

	GOMPONENT_EXPORT int config_getType(String key)
	{
		auto gamemode = Gomponent::Get()->getGamemode();

		if (gamemode->config)
		{
			return gamemode->config->getType(StringView(key.buf, key.length));
		}

		return -1;
	}

	GOMPONENT_EXPORT float config_getFloat(String key)
	{
		auto gamemode = Gomponent::Get()->getGamemode();

		if (gamemode->config)
		{
			return *gamemode->config->getFloat(StringView(key.buf, key.length));
		}

		return 0.0;
	}

	GOMPONENT_EXPORT int config_getInt(String key, int value)
	{
		auto gamemode = Gomponent::Get()->getGamemode();

		if (gamemode->config)
		{
			return *gamemode->config->getInt(StringView(key.buf, key.length));
		}

		return 0;
	}

	GOMPONENT_EXPORT unsigned char config_getBool(String key)
	{
		auto gamemode = Gomponent::Get()->getGamemode();

		if (gamemode->config)
		{
			return *gamemode->config->getBool(StringView(key.buf, key.length));
		}

		return 0;
	}

	GOMPONENT_EXPORT unsigned char config_isBanned(String ip)
	{
		auto gamemode = Gomponent::Get()->getGamemode();
		BanEntry entry(StringView(ip.buf, ip.length));

		if (gamemode->config)
		{
			return gamemode->config->isBanned(entry) ? 1 : 0;
		}

		return 0;
	}

#ifdef __cplusplus
}
#endif
