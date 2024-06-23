#include <iostream>

#include "api.hpp"
#include "Gomponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	GOMPONENT_EXPORT void console_send(String command)
	{
		IConsoleComponent* console = Gomponent::Get()->console;

		if (console)
		{
			console->send(StringView(command.buf, command.length));
		}
	}

#ifdef __cplusplus
}
#endif
