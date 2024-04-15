#include <sdk.hpp>

#include <api/api.hpp>
#include "Singleton.hpp"
#include "Gomponent.hpp"
#include "Gamemode.hpp"

class PlayerEvents : public PlayerSpawnEventHandler, public PlayerConnectEventHandler, public PlayerStreamEventHandler, public PlayerTextEventHandler, public PlayerShotEventHandler, public PlayerChangeEventHandler, public PlayerDamageEventHandler, public PlayerClickEventHandler, public PlayerCheckEventHandler, public PlayerUpdateEventHandler, public Singleton<PlayerEvents>
{
public:
	PlayerEvents()
	{
		gamemode_ = Gomponent::Get()->getGamemode();
	}

	void onPlayerSpawn(IPlayer& player) override
	{
		return gamemode_->call<void>("onPlayerSpawn", static_cast<void*>(&player));
	}

	void onIncomingConnection(IPlayer& player, StringView ipAddress, unsigned short port) override
	{
		return gamemode_->call<void>("onIncomingConnection", static_cast<void*>(&player), std::string(ipAddress).c_str(), port);
	}

	void onPlayerConnect(IPlayer& player) override
	{
		return gamemode_->call<void>("onPlayerConnect", static_cast<void*>(&player));
	}

	void onPlayerDisconnect(IPlayer& player, PeerDisconnectReason reason) override
	{
		return gamemode_->call<void>("onPlayerDisconnect", static_cast<void*>(&player), static_cast<int>(reason));
	}

	void onPlayerClientInit(IPlayer& player) override
	{
		// gamemode_->call<void>("onPlayerClientInit", static_cast<void*>(&player));
	}

	bool onPlayerText(IPlayer& player, StringView message) override
	{
		std::cout << "Message: " << message << std::endl;
		return true;
	}

	bool onPlayerCommandText(IPlayer& player, StringView message) override
	{
		String str = { message.data(), message.length() };

		return gamemode_->call<unsigned char>("onPlayerCommandText", static_cast<void*>(&player), str) != 0;
	}

	void onPlayerDeath(IPlayer& player, IPlayer* killer, int reason) override
	{
		return gamemode_->call<void>("onPlayerDeath", static_cast<void*>(&player), static_cast<void*>(killer), reason);
	}

	bool onPlayerUpdate(IPlayer& player, TimePoint now) override
	{
		auto nowMs = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
		auto value = nowMs.time_since_epoch();
		long nowMillis = value.count();

		return gamemode_->call<unsigned char>("onPlayerUpdate", static_cast<void*>(&player), nowMillis) != 0;
	}

private:
	Gamemode* gamemode_;
};
