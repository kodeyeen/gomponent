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
	callbacks.emplace("onGameModeInit", findCallback("onGameModeInit"));
	callbacks.emplace("onPlayerSpawn", findCallback("onPlayerSpawn"));
	callbacks.emplace("onIncomingConnection", findCallback("onIncomingConnection"));
	callbacks.emplace("onPlayerConnect", findCallback("onPlayerConnect"));
	callbacks.emplace("onPlayerDisconnect", findCallback("onPlayerDisconnect"));
	callbacks.emplace("onPlayerClientInit", findCallback("onPlayerClientInit"));
	callbacks.emplace("onPlayerText", findCallback("onPlayerText"));
	callbacks.emplace("onPlayerCommandText", findCallback("onPlayerCommandText"));
	callbacks.emplace("onPlayerDeath", findCallback("onPlayerDeath"));
	callbacks.emplace("onPlayerUpdate", findCallback("onPlayerUpdate"));
	callbacks.emplace("onPlayerRequestClass", findCallback("onPlayerRequestClass"));

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
