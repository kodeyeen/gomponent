#include <iostream>

#include "Gamemode.hpp"

Gamemode::Gamemode(const std::string& path)
{
	handle = openLib(path);

	if (handle == NULL)
	{
		std::cerr << "Failed to open library. Error code: " << GetLastError() << std::endl;
		return;
	}
}

void Gamemode::init() {
	call<void>("onGameModeInit");
}

Gamemode::~Gamemode()
{
	closeLib(handle);
}

void* Gamemode::openLib(const std::string& path)
{
	return LoadLibrary(path.c_str());
}

void Gamemode::closeLib(void* handle)
{
	FreeLibrary((HMODULE)handle);
}

void* Gamemode::findCallback(const std::string& name)
{
	FARPROC callback = GetProcAddress((HMODULE)handle, name.c_str());

	return (void*)(callback);
}
