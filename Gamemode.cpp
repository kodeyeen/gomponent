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
	callbacks.emplace("onGameModeInit", findCallback("onGameModeInit"));

	// Actor events
	callbacks.emplace("onPlayerGiveDamageActor", findCallback("onPlayerGiveDamageActor"));
	callbacks.emplace("onActorStreamOut", findCallback("onActorStreamOut"));
	callbacks.emplace("onActorStreamIn", findCallback("onActorStreamIn"));

	// Checkpoint events
	callbacks.emplace("onPlayerEnterCheckpoint", findCallback("onPlayerEnterCheckpoint"));
	callbacks.emplace("onPlayerLeaveCheckpoint", findCallback("onPlayerLeaveCheckpoint"));
	callbacks.emplace("onPlayerEnterRaceCheckpoint", findCallback("onPlayerEnterRaceCheckpoint"));
	callbacks.emplace("onPlayerLeaveRaceCheckpoint", findCallback("onPlayerLeaveRaceCheckpoint"));

	// Class events
	callbacks.emplace("onPlayerRequestClass", findCallback("onPlayerRequestClass"));

	// Console events
	callbacks.emplace("onConsoleText", findCallback("onConsoleText"));
	callbacks.emplace("onRconLoginAttempt", findCallback("onRconLoginAttempt"));

	// Custom model events
	callbacks.emplace("onPlayerFinishedDownloading", findCallback("onPlayerFinishedDownloading"));
	callbacks.emplace("onPlayerRequestDownload", findCallback("onPlayerRequestDownload"));

	// Dialog events
	callbacks.emplace("onDialogResponse", findCallback("onDialogResponse"));

	// GangZone events
	callbacks.emplace("onPlayerEnterGangZone", findCallback("onPlayerEnterGangZone"));
	callbacks.emplace("onPlayerEnterPlayerGangZone", findCallback("onPlayerEnterPlayerGangZone"));
	callbacks.emplace("onPlayerLeaveGangZone", findCallback("onPlayerLeaveGangZone"));
	callbacks.emplace("onPlayerLeavePlayerGangZone", findCallback("onPlayerLeavePlayerGangZone"));
	callbacks.emplace("onPlayerClickGangZone", findCallback("onPlayerClickGangZone"));
	callbacks.emplace("onPlayerClickPlayerGangZone", findCallback("onPlayerClickPlayerGangZone"));

	// Menu events
	callbacks.emplace("onPlayerSelectedMenuRow", findCallback("onPlayerSelectedMenuRow"));
	callbacks.emplace("onPlayerExitedMenu", findCallback("onPlayerExitedMenu"));

	// Object events
	callbacks.emplace("onObjectMoved", findCallback("onObjectMoved"));
	callbacks.emplace("onPlayerObjectMoved", findCallback("onPlayerObjectMoved"));
	callbacks.emplace("onObjectSelected", findCallback("onObjectSelected"));
	callbacks.emplace("onPlayerObjectSelected", findCallback("onPlayerObjectSelected"));
	callbacks.emplace("onObjectEdited", findCallback("onObjectEdited"));
	callbacks.emplace("onPlayerObjectEdited", findCallback("onPlayerObjectEdited"));
	callbacks.emplace("onPlayerAttachedObjectEdited", findCallback("onPlayerAttachedObjectEdited"));

	// Pickup events
	callbacks.emplace("onPlayerPickUpPickup", findCallback("onPlayerPickUpPickup"));
	callbacks.emplace("onPlayerPickUpPlayerPickup", findCallback("onPlayerPickUpPlayerPickup"));

	// Player spawn events
	callbacks.emplace("onPlayerRequestSpawn", findCallback("onPlayerRequestSpawn"));
	callbacks.emplace("onPlayerSpawn", findCallback("onPlayerSpawn"));

	// Player connect events
	callbacks.emplace("onIncomingConnection", findCallback("onIncomingConnection"));
	callbacks.emplace("onPlayerConnect", findCallback("onPlayerConnect"));
	callbacks.emplace("onPlayerDisconnect", findCallback("onPlayerDisconnect"));
	callbacks.emplace("onPlayerClientInit", findCallback("onPlayerClientInit"));

	// Player stream events
	callbacks.emplace("onPlayerStreamIn", findCallback("onPlayerStreamIn"));
	callbacks.emplace("onPlayerStreamOut", findCallback("onPlayerStreamOut"));

	// Player text events
	callbacks.emplace("onPlayerText", findCallback("onPlayerText"));
	callbacks.emplace("onPlayerCommandText", findCallback("onPlayerCommandText"));

	// Player shot events
	callbacks.emplace("onPlayerShotMissed", findCallback("onPlayerShotMissed"));
	callbacks.emplace("onPlayerShotPlayer", findCallback("onPlayerShotPlayer"));
	callbacks.emplace("onPlayerShotVehicle", findCallback("onPlayerShotVehicle"));
	callbacks.emplace("onPlayerShotObject", findCallback("onPlayerShotObject"));
	callbacks.emplace("onPlayerShotPlayerObject", findCallback("onPlayerShotPlayerObject"));

	// Player change events
	callbacks.emplace("onPlayerScoreChange", findCallback("onPlayerScoreChange"));
	callbacks.emplace("onPlayerNameChange", findCallback("onPlayerNameChange"));
	callbacks.emplace("onPlayerInteriorChange", findCallback("onPlayerInteriorChange"));
	callbacks.emplace("onPlayerStateChange", findCallback("onPlayerStateChange"));
	callbacks.emplace("onPlayerKeyStateChange", findCallback("onPlayerKeyStateChange"));

	// Player damage events
	callbacks.emplace("onPlayerDeath", findCallback("onPlayerDeath"));
	callbacks.emplace("onPlayerTakeDamage", findCallback("onPlayerTakeDamage"));
	callbacks.emplace("onPlayerGiveDamage", findCallback("onPlayerGiveDamage"));

	// Player click events
	callbacks.emplace("onPlayerClickMap", findCallback("onPlayerClickMap"));
	callbacks.emplace("onPlayerClickPlayer", findCallback("onPlayerClickPlayer"));

	// Player check events
	callbacks.emplace("onClientCheckResponse", findCallback("onClientCheckResponse"));

	// Player update events
	callbacks.emplace("onPlayerUpdate", findCallback("onPlayerUpdate"));

	// TextDraw events
	callbacks.emplace("onPlayerClickTextDraw", findCallback("onPlayerClickTextDraw"));
	callbacks.emplace("onPlayerClickPlayerTextDraw", findCallback("onPlayerClickPlayerTextDraw"));
	callbacks.emplace("onPlayerCancelTextDrawSelection", findCallback("onPlayerCancelTextDrawSelection"));
	callbacks.emplace("onPlayerCancelPlayerTextDrawSelection", findCallback("onPlayerCancelPlayerTextDrawSelection"));

	// Vehicle events
	callbacks.emplace("onVehicleStreamIn", findCallback("onVehicleStreamIn"));
	callbacks.emplace("onVehicleStreamOut", findCallback("onVehicleStreamOut"));
	callbacks.emplace("onVehicleDeath", findCallback("onVehicleDeath"));
	callbacks.emplace("onPlayerEnterVehicle", findCallback("onPlayerEnterVehicle"));
	callbacks.emplace("onPlayerExitVehicle", findCallback("onPlayerExitVehicle"));
	callbacks.emplace("onVehicleDamageStatusUpdate", findCallback("onVehicleDamageStatusUpdate"));
	callbacks.emplace("onVehiclePaintJob", findCallback("onVehiclePaintJob"));
	callbacks.emplace("onVehicleMod", findCallback("onVehicleMod"));
	callbacks.emplace("onVehicleRespray", findCallback("onVehicleRespray"));
	callbacks.emplace("onEnterExitModShop", findCallback("onEnterExitModShop"));
	callbacks.emplace("onVehicleSpawn", findCallback("onVehicleSpawn"));
	callbacks.emplace("onUnoccupiedVehicleUpdate", findCallback("onUnoccupiedVehicleUpdate"));
	callbacks.emplace("onTrailerUpdate", findCallback("onTrailerUpdate"));
	callbacks.emplace("onVehicleSirenStateChange", findCallback("onVehicleSirenStateChange"));

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
