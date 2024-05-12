#include <iostream>

#include "Gamemode.hpp"

Gamemode::~Gamemode()
{
	unload();
}

void Gamemode::load(const std::string& name)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	handle = LoadLibrary(("gamemodes/" + name + ".dll").c_str());
#else
	handle = dlopen(("gamemodes/" + name + ".so").c_str(), RTLD_GLOBAL | RTLD_NOW);
#endif

	if (handle == NULL)
	{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
		// std::cerr << "Failed to load gamemode. Error code: " << GetLastError() << std::endl;
		// return;
#else
	
#endif
	}
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
