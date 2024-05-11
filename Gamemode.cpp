#include <iostream>

#include "Gamemode.hpp"

Gamemode::Gamemode(const std::string& path)
{
	handle = openLib(path);

	if (handle == NULL)
	{
		std::cerr << "Failed to load gamemode. Error code: " << GetLastError() << std::endl;
		return;
	}
}

Gamemode::~Gamemode()
{
	closeLib(handle);
}

void* Gamemode::openLib(const std::string& path)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	return LoadLibrary(path.c_str());
#else
	return dlopen(path.c_str(), RTLD_GLOBAL | RTLD_NOW);
#endif
}

void Gamemode::closeLib(void* handle)
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
