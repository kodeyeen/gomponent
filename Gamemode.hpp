#pragma once

#include <iostream>
#include <string>
#include <sdk.hpp>
#include <Windows.h>

class Gamemode
{
public:
	Gamemode(const std::string& path);
	~Gamemode();
	void init();

	template <typename... Args>
	void call(const std::string& callbackName, Args... args);

private:
	void* handle;
	FlatHashMap<std::string, void*> callbacks;

	void* openLib(const std::string& path);
	void closeLib(void* handle);
	void* findCallback(const std::string& name);
};

template <typename... Args>
void Gamemode::call(const std::string& callbackName, Args... args)
{
	auto it = callbacks.find(callbackName);

	if (it == callbacks.end())
	{
		return;
	}

	typedef void (* CallbackType)(Args...);

	CallbackType callback = (CallbackType)it->second;

	(*callback)(std::forward<Args>(args)...);
}
