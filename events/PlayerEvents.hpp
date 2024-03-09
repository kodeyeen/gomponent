#include <sdk.hpp>
#include <iostream>

#include "Singleton.hpp"
#include "GompComponent.hpp"

class PlayerEvents : public PlayerSpawnEventHandler, public PlayerConnectEventHandler, public PlayerStreamEventHandler, public PlayerTextEventHandler, public PlayerShotEventHandler, public PlayerChangeEventHandler, public PlayerDamageEventHandler, public PlayerClickEventHandler, public PlayerCheckEventHandler, public PlayerUpdateEventHandler, public Singleton<PlayerEvents>
{
public:
	void onPlayerConnect(IPlayer& player) override
	{
		auto gamemode_ = GompComponent::Get()->getGamemode();
		std::cout << "CALLING ON PLAYER CONNECT" << '\n';
		gamemode_->call("onPlayerConnect", static_cast<void*>(&player));
	}
};
