#include <sdk.hpp>

#include "Singleton.hpp"
#include "Gomponent.hpp"
#include "Gamemode.hpp"

class GangZoneEvents : public GangZoneEventHandler, public Singleton<GangZoneEvents>
{
public:
	GangZoneEvents()
	{
		gamemode_ = Gamemode::Get();
	}

	void onPlayerEnterGangZone(IPlayer& player, IGangZone& zone) override
	{
		if (zone.getLegacyPlayer() == nullptr)
		{
			gamemode_->call<void>("onPlayerEnterGangZone", static_cast<void*>(&player), static_cast<void*>(&zone));
		}
		else if (auto data = queryExtension<IPlayerGangZoneData>(player))
		{
			gamemode_->call<void>("onPlayerEnterPlayerGangZone", static_cast<void*>(&player), static_cast<void*>(&zone));
		}
	}

	void onPlayerLeaveGangZone(IPlayer& player, IGangZone& zone) override
	{
		if (zone.getLegacyPlayer() == nullptr)
		{
			gamemode_->call<void>("onPlayerLeaveGangZone", static_cast<void*>(&player), static_cast<void*>(&zone));
		}
		else if (auto data = queryExtension<IPlayerGangZoneData>(player))
		{
			gamemode_->call<void>("onPlayerLeavePlayerGangZone", static_cast<void*>(&player), static_cast<void*>(&zone));
		}
	}

	void onPlayerClickGangZone(IPlayer& player, IGangZone& zone) override
	{
		if (zone.getLegacyPlayer() == nullptr)
		{
			gamemode_->call<void>("onPlayerClickGangZone", static_cast<void*>(&player), static_cast<void*>(&zone));
		}
		else if (auto data = queryExtension<IPlayerGangZoneData>(player))
		{
			gamemode_->call<void>("onPlayerClickPlayerGangZone", static_cast<void*>(&player), static_cast<void*>(&zone));
		}
	}

private:
	Gamemode* gamemode_;
};
