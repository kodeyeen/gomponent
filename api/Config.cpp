#include "api.hpp"
#include "Gomponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	GOMPONENT_EXPORT void config_setFloat(String key, float value)
	{
		IConfig* config = Gomponent::Get()->config;

		if (config)
		{
			*config->getFloat(StringView(key.buf, key.length)) = value;
		}
	}

	GOMPONENT_EXPORT void config_setInt(String key, int value)
	{
		IConfig* config = Gomponent::Get()->config;

		if (config)
		{
			*config->getInt(StringView(key.buf, key.length)) = value;
		}
	}

	GOMPONENT_EXPORT void config_setBool(String key, unsigned char value)
	{
		IConfig* config = Gomponent::Get()->config;

		if (config)
		{
			*config->getBool(StringView(key.buf, key.length)) = value != 0;
		}
	}

	GOMPONENT_EXPORT int config_getType(String key)
	{
		IConfig* config = Gomponent::Get()->config;

		if (config)
		{
			return config->getType(StringView(key.buf, key.length));
		}

		return -1;
	}

	GOMPONENT_EXPORT float config_getFloat(String key)
	{
		IConfig* config = Gomponent::Get()->config;

		if (config)
		{
			return *config->getFloat(StringView(key.buf, key.length));
		}

		return 0.0;
	}

	GOMPONENT_EXPORT int config_getInt(String key)
	{
		IConfig* config = Gomponent::Get()->config;

		if (config)
		{
			return *config->getInt(StringView(key.buf, key.length));
		}

		return 0;
	}

	GOMPONENT_EXPORT unsigned char config_getBool(String key)
	{
		IConfig* config = Gomponent::Get()->config;

		if (config)
		{
			return *config->getBool(StringView(key.buf, key.length));
		}

		return 0;
	}

	GOMPONENT_EXPORT unsigned char config_isBanned(String ip)
	{
		IConfig* config = Gomponent::Get()->config;

		BanEntry entry(StringView(ip.buf, ip.length));

		if (config)
		{
			return config->isBanned(entry) ? 1 : 0;
		}

		return 0;
	}

#ifdef __cplusplus
}
#endif
