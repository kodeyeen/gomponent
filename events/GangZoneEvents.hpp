#include <sdk.hpp>

#include "Singleton.hpp"
#include "Gomponent.hpp"
#include "Gamemode.hpp"

class GangZoneEvents : public GangZoneEventHandler, public Singleton<GangZoneEvents>
{
public:
	GangZoneEvents()
	{
		gamemode_ = Gomponent::Get()->getGamemode();
	}

	void onPlayerEnterGangZone(IPlayer& player, IGangZone& zone) override
	{
		if (zone.getLegacyPlayer() == nullptr)
		{
			gamemode_->call<unsigned char>("onPlayerEnterGangZone", static_cast<void*>(&player), static_cast<void*>(&zone));
		}
		else if (auto data = queryExtension<IPlayerGangZoneData>(player))
		{
			gamemode_->call<unsigned char>("onPlayerEnterPlayerGangZone", static_cast<void*>(&player), static_cast<void*>(&zone));
		}
	}

	void onPlayerLeaveGangZone(IPlayer& player, IGangZone& zone) override
	{
		if (zone.getLegacyPlayer() == nullptr)
		{
			gamemode_->call<unsigned char>("onPlayerLeaveGangZone", static_cast<void*>(&player), static_cast<void*>(&zone));
		}
		else if (auto data = queryExtension<IPlayerGangZoneData>(player))
		{
			gamemode_->call<unsigned char>("onPlayerLeavePlayerGangZone", static_cast<void*>(&player), static_cast<void*>(&zone));
		}
	}

	void onPlayerClickGangZone(IPlayer& player, IGangZone& zone) override
	{
		if (zone.getLegacyPlayer() == nullptr)
		{
			gamemode_->call<unsigned char>("onPlayerClickGangZone", static_cast<void*>(&player), static_cast<void*>(&zone));
		}
		else if (auto data = queryExtension<IPlayerGangZoneData>(player))
		{
			gamemode_->call<unsigned char>("onPlayerClickPlayerGangZone", static_cast<void*>(&player), static_cast<void*>(&zone));
		}
	}

private:
	Gamemode* gamemode_;
};
