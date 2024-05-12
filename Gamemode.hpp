#pragma once

#include <string>
#include <sdk.hpp>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	#include <Windows.h>
#else
	#include <dlfcn.h>
#endif

#include "Singleton.hpp"

class Gamemode final : public Singleton<Gamemode>
{
public:
	~Gamemode();
	void load(const std::string& name);
	void unload();

	template <typename R, typename... Args>
	R call(const std::string& callbackName, Args... args);

private:
	void* handle;
	FlatHashMap<std::string, void*> callbacks;

	void* findCallback(const std::string& name);
};

template <typename R, typename... Args>
R Gamemode::call(const std::string& callbackName, Args... args)
{
	auto it = callbacks.find(callbackName);
	void* callbackAddr = nullptr;

	if (it == callbacks.end())
	{
		callbackAddr = findCallback(callbackName);
		callbacks.emplace(callbackName, callbackAddr);
	}
	else
	{
		callbackAddr = it->second;
	}

	// R ret;
	// if callbackAddr == nullptr {
	//     return ret;
	// }

	typedef R (* CallbackType)(Args...);

	CallbackType callback = (CallbackType)callbackAddr;

	return (*callback)(std::forward<Args>(args)...);
}
