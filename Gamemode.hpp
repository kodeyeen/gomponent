#pragma once

#include <iostream>
#include <string>
#include <sdk.hpp>
#include <Server/Components/Actors/actors.hpp>
#include <Server/Components/Classes/classes.hpp>
#include <Server/Components/GangZones/gangzones.hpp>
#include <Server/Components/Menus/menus.hpp>
#include <Server/Components/CustomModels/custommodels.hpp>
#include <Server/Components/Objects/objects.hpp>
#include <Server/Components/Pickups/pickups.hpp>
#include <Server/Components/TextDraws/textdraws.hpp>
#include <Server/Components/TextLabels/textlabels.hpp>
#include <Server/Components/Vehicles/vehicles.hpp>
#include <Windows.h>

class Gamemode
{
public:
	ICore* core;
	IConfig* config;
	IPlayerPool* players;
	IActorsComponent* actors;
	IClassesComponent* classes;
	ICustomModelsComponent* models;
	IGangZonesComponent* gangzones;
	IMenusComponent* menus;
	IObjectsComponent* objects;
	IPickupsComponent* pickups;
	ITextDrawsComponent* textdraws;
	ITextLabelsComponent* textlabels;
	IVehiclesComponent* vehicles;

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
