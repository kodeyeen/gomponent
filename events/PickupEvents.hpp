#include <sdk.hpp>

#include "Singleton.hpp"
#include "Gomponent.hpp"
#include "Gamemode.hpp"

class PickupEvents : public PickupEventHandler, public Singleton<PickupEvents>
{
public:
	PickupEvents()
	{
		gamemode_ = Gamemode::Get();
	}

	void onPlayerPickUpPickup(IPlayer& player, IPickup& pickup) override
	{
		if (pickup.getLegacyPlayer() == nullptr)
		{
			gamemode_->call<void>("onPlayerPickUpPickup", static_cast<void*>(&player), static_cast<void*>(&pickup));
		}
		else if (auto data = queryExtension<IPlayerPickupData>(player))
		{
			gamemode_->call<void>("onPlayerPickUpPlayerPickup", static_cast<void*>(&player), static_cast<void*>(&pickup));
		}
	}

private:
	Gamemode* gamemode_;
};
