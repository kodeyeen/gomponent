#pragma once

#include <string>
#include <sdk.hpp>
#include <Windows.h>

#include "Singleton.hpp"

class Gamemode final : public Singleton<Gamemode>
{
public:
	Gamemode(const std::string& path);
	~Gamemode();
	void init();

	template <typename R, typename... Args>
	R call(const std::string& callbackName, Args... args);

private:
	void* handle;
	FlatHashMap<std::string, void*> callbacks;

	void* openLib(const std::string& path);
	void closeLib(void* handle);
	void* findCallback(const std::string& name);
};

template <typename R, typename... Args>
R Gamemode::call(const std::string& callbackName, Args... args)
{
	auto it = callbacks.find(callbackName);

	/*if (it == callbacks.end())
	{
		return;
	}*/

	typedef R (* CallbackType)(Args...);

	CallbackType callback = (CallbackType)it->second;

	return (*callback)(std::forward<Args>(args)...);
}
