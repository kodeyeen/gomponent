#include <sdk.hpp>

#include "Singleton.hpp"
#include "Gomponent.hpp"
#include "Gamemode.hpp"

class VehicleEvents : public VehicleEventHandler, public Singleton<VehicleEvents>
{
public:
	VehicleEvents()
	{
		gamemode_ = Gomponent::Get()->getGamemode();
	}

	void onVehicleStreamIn(IVehicle& vehicle, IPlayer& player) override
	{
		gamemode_->call<void>("onVehicleStreamIn", static_cast<void*>(&vehicle), static_cast<void*>(&player));
	}

	void onVehicleStreamOut(IVehicle& vehicle, IPlayer& player) override
	{
		gamemode_->call<void>("onVehicleStreamOut", static_cast<void*>(&vehicle), static_cast<void*>(&player));
	}

	void onVehicleDeath(IVehicle& vehicle, IPlayer& player) override
	{
		gamemode_->call<void>("onVehicleDeath", static_cast<void*>(&vehicle), static_cast<void*>(&player));
	}

	void onPlayerEnterVehicle(IPlayer& player, IVehicle& vehicle, bool passenger) override
	{
		gamemode_->call<void>("onPlayerEnterVehicle", static_cast<void*>(&player), static_cast<void*>(&vehicle), (unsigned char)(passenger ? 1 : 0));
	}

	void onPlayerExitVehicle(IPlayer& player, IVehicle& vehicle) override
	{
		gamemode_->call<void>("onPlayerExitVehicle", static_cast<void*>(&player), static_cast<void*>(&vehicle));
	}

	void onVehicleDamageStatusUpdate(IVehicle& vehicle, IPlayer& player) override
	{
		gamemode_->call<void>("onVehicleDamageStatusUpdate", static_cast<void*>(&vehicle), static_cast<void*>(&player));
	}

	bool onVehiclePaintJob(IPlayer& player, IVehicle& vehicle, int paintJob) override
	{
		return gamemode_->call<unsigned char>("onVehiclePaintJob", static_cast<void*>(&player), static_cast<void*>(&vehicle), paintJob) != 0;
	}

	bool onVehicleMod(IPlayer& player, IVehicle& vehicle, int component) override
	{
		return gamemode_->call<unsigned char>("onVehicleMod", static_cast<void*>(&player), static_cast<void*>(&vehicle), component) != 0;
	}

	bool onVehicleRespray(IPlayer& player, IVehicle& vehicle, int colour1, int colour2) override
	{
		return gamemode_->call<unsigned char>("onVehicleRespray", static_cast<void*>(&player), static_cast<void*>(&vehicle), colour1, colour2) != 0;
	}

	void onEnterExitModShop(IPlayer& player, bool enterexit, int interiorID) override
	{
		gamemode_->call<void>("onEnterExitModShop", static_cast<void*>(&player), (unsigned char)(enterexit ? 1 : 0), interiorID);
	}

	void onVehicleSpawn(IVehicle& vehicle) override
	{
		gamemode_->call<void>("onVehicleSpawn", static_cast<void*>(&vehicle));
	}

	bool onUnoccupiedVehicleUpdate(IVehicle& vehicle, IPlayer& player, UnoccupiedVehicleUpdate const updateData) override
	{
		return gamemode_->call<unsigned char>("onUnoccupiedVehicleUpdate", static_cast<void*>(&vehicle), static_cast<void*>(&player), updateData) != 0;
	}

	bool onTrailerUpdate(IPlayer& player, IVehicle& trailer) override
	{
		return gamemode_->call<unsigned char>("onTrailerUpdate", static_cast<void*>(&player), static_cast<void*>(&trailer)) != 0;
	}

	bool onVehicleSirenStateChange(IPlayer& player, IVehicle& vehicle, uint8_t sirenState) override
	{
		return gamemode_->call<unsigned char>("onVehicleSirenStateChange", static_cast<void*>(&player), static_cast<void*>(&vehicle), sirenState) != 0;
	}

private:
	Gamemode* gamemode_;
};
