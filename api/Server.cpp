#include "api.hpp"
#include "Gomponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	GOMPONENT_EXPORT void server_printLnU8(const char* fmt, ...)
	{
		ICore* core = Gomponent::Get()->core;

		va_list args;
		va_start(args, fmt);

		core->vprintLnU8(fmt, args);

		va_end(args);
	}

	GOMPONENT_EXPORT void server_logLnU8(int logLevel, const char* fmt, ...)
	{
		ICore* core = Gomponent::Get()->core;

		va_list args;
		va_start(args, fmt);

		core->vlogLnU8(LogLevel(logLevel), fmt, args);

		va_end(args);
	}

	GOMPONENT_EXPORT void server_setModeText(String text)
	{
		ICore* core = Gomponent::Get()->core;

		if (core)
		{
			core->setData(SettableCoreDataType::ModeText, StringView(text.buf, text.length));
		}
	}

	GOMPONENT_EXPORT void server_setWeather(int weather)
	{
		ICore* core = Gomponent::Get()->core;

		if (core)
		{
			core->setWeather(weather);
		}
	}

	GOMPONENT_EXPORT void server_setWorldTime(int hours)
	{
		ICore* core = Gomponent::Get()->core;

		if (core)
		{
			core->setWorldTime(Hours(hours));
		}
	}

	GOMPONENT_EXPORT void server_enableStuntBonuses()
	{
		ICore* core = Gomponent::Get()->core;

		if (core)
		{
			core->useStuntBonuses(true);
		}
	}

#ifdef __cplusplus
}
#endif
