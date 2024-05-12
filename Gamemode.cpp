#include <sstream>

#include "Gamemode.hpp"

Gamemode::~Gamemode()
{
	unload();
}

void Gamemode::load(const std::string& name)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	handle = LoadLibrary(("gamemodes/" + name + ".dll").c_str());

	if (handle == NULL)
	{
		DWORD error = GetLastError();
		std::stringstream errMsg;
		errMsg << "error code " << error;

		throw std::runtime_error(errMsg.str());
	}
#else
	handle = dlopen(("gamemodes/" + name + ".so").c_str(), RTLD_GLOBAL | RTLD_NOW);

	if (handle == NULL)
	{
		const char* errMsg = dlerror();

		if (errMsg != NULL)
		{
			throw std::runtime_error(std::string(errMsg));
		}
	}
#endif
}

void Gamemode::unload()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	FreeLibrary((HMODULE)handle);
#else
	dlclose(handle);
#endif
}

void* Gamemode::findCallback(const std::string& name)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	return (void*)GetProcAddress((HMODULE)handle, name.c_str());
#else
	return dlsym(handle, name.c_str());
#endif
}
