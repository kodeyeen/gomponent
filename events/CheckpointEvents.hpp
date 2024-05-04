#include <sdk.hpp>

#include "Singleton.hpp"
#include "Gomponent.hpp"
#include "Gamemode.hpp"

class CheckpointEvents : public PlayerCheckpointEventHandler, public Singleton<CheckpointEvents>
{
public:
	CheckpointEvents()
	{
		gamemode_ = Gomponent::Get()->getGamemode();
	}

	void onPlayerEnterCheckpoint(IPlayer& player) override
	{
		gamemode_->call<unsigned char>("onPlayerEnterCheckpoint", static_cast<void*>(&player));
	}

	void onPlayerLeaveCheckpoint(IPlayer& player) override
	{
		gamemode_->call<unsigned char>("onPlayerLeaveCheckpoint", static_cast<void*>(&player));
	}

	void onPlayerEnterRaceCheckpoint(IPlayer& player) override
	{
		gamemode_->call<unsigned char>("onPlayerEnterRaceCheckpoint", static_cast<void*>(&player));
	}

	void onPlayerLeaveRaceCheckpoint(IPlayer& player) override
	{
		gamemode_->call<unsigned char>("onPlayerLeaveRaceCheckpoint", static_cast<void*>(&player));
	}

private:
	Gamemode* gamemode_;
};
