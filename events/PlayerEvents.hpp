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

	// Player spawn events

	bool onPlayerRequestSpawn(IPlayer& player) override {
		return gamemode_->call<bool>("onPlayerRequestSpawn", static_cast<void*>(&player)) ? 1 : 0;
	}

	void onPlayerSpawn(IPlayer& player) override
	{
		gamemode_->call<unsigned char>("onPlayerSpawn", static_cast<void*>(&player));
	}

	// Player connect events

	void onIncomingConnection(IPlayer& player, StringView ipAddress, unsigned short port) override
	{
		String ipAddressStr = { ipAddress.data(), ipAddress.length() };

		gamemode_->call<unsigned char>("onIncomingConnection", static_cast<void*>(&player), ipAddressStr, port);
	}

	void onPlayerConnect(IPlayer& player) override
	{
		gamemode_->call<unsigned char>("onPlayerConnect", static_cast<void*>(&player));
	}

	void onPlayerDisconnect(IPlayer& player, PeerDisconnectReason reason) override
	{
		gamemode_->call<unsigned char>("onPlayerDisconnect", static_cast<void*>(&player), static_cast<int>(reason));
	}

	void onPlayerClientInit(IPlayer& player) override
	{
		gamemode_->call<unsigned char>("onPlayerClientInit", static_cast<void*>(&player));
	}

	// Player stream events

	void onPlayerStreamIn(IPlayer& player, IPlayer& forPlayer) override
	{
		gamemode_->call<unsigned char>("onPlayerStreamIn", static_cast<void*>(&player), static_cast<void*>(&forPlayer));
	}

	void onPlayerStreamOut(IPlayer& player, IPlayer& forPlayer) override
	{
		gamemode_->call<unsigned char>("onPlayerStreamOut", static_cast<void*>(&player), static_cast<void*>(&forPlayer));
	}

	// Player text events

	bool onPlayerText(IPlayer& player, StringView message) override
	{
		String msgStr = { message.data(), message.length() };

		return gamemode_->call<unsigned char>("onPlayerText", static_cast<void*>(&player), msgStr) != 0;
	}

	bool onPlayerCommandText(IPlayer& player, StringView message) override
	{
		String msgStr = { message.data(), message.length() };

		return gamemode_->call<unsigned char>("onPlayerCommandText", static_cast<void*>(&player), msgStr) != 0;
	}

	// Player shot events

	bool onPlayerShotMissed(IPlayer& player, const PlayerBulletData& bulletData) override
	{
		return gamemode_->call<unsigned char>("onPlayerShotMissed", static_cast<void*>(&player), bulletData) != 0;
	}

	bool onPlayerShotPlayer(IPlayer& player, IPlayer& target, const PlayerBulletData& bulletData) override
	{
		return gamemode_->call<unsigned char>("onPlayerShotPlayer", static_cast<void*>(&player), static_cast<void*>(&target), bulletData) != 0;
	}

	bool onPlayerShotVehicle(IPlayer& player, IVehicle& target, const PlayerBulletData& bulletData) override
	{
		return gamemode_->call<unsigned char>("onPlayerShotVehicle", static_cast<void*>(&player), static_cast<void*>(&target), bulletData) != 0;
	}

	bool onPlayerShotObject(IPlayer& player, IObject& target, const PlayerBulletData& bulletData) override
	{
		return gamemode_->call<unsigned char>("onPlayerShotObject", static_cast<void*>(&player), static_cast<void*>(&target), bulletData) != 0;
	}

	bool onPlayerShotPlayerObject(IPlayer& player, IPlayerObject& target, const PlayerBulletData& bulletData) override
	{
		return gamemode_->call<unsigned char>("onPlayerShotPlayerObject", static_cast<void*>(&player), static_cast<void*>(&target), bulletData) != 0;
	}

	// Player change events

	void onPlayerScoreChange(IPlayer& player, int score) override
	{
		gamemode_->call<unsigned char>("onPlayerScoreChange", static_cast<void*>(&player), score);
	}

	void onPlayerNameChange(IPlayer& player, StringView oldName) override
	{
		String oldNameStr = { oldName.data(), oldName.length() };

		gamemode_->call<unsigned char>("onPlayerNameChange", static_cast<void*>(&player), oldNameStr);
	}

	void onPlayerInteriorChange(IPlayer& player, unsigned newInterior, unsigned oldInterior) override
	{
		gamemode_->call<unsigned char>("onPlayerInteriorChange", static_cast<void*>(&player), newInterior, oldInterior);
	}

	void onPlayerStateChange(IPlayer& player, PlayerState newState, PlayerState oldState) override
	{
		gamemode_->call<unsigned char>("onPlayerStateChange", static_cast<void*>(&player), int(newState), int(oldState));
	}

	void onPlayerKeyStateChange(IPlayer& player, uint32_t newKeys, uint32_t oldKeys) override
	{
		gamemode_->call<unsigned char>("onPlayerKeyStateChange", static_cast<void*>(&player), newKeys, oldKeys);
	}

	// Player damage events

	void onPlayerDeath(IPlayer& player, IPlayer* killer, int reason) override
	{
		gamemode_->call<unsigned char>("onPlayerDeath", static_cast<void*>(&player), static_cast<void*>(killer), reason);
	}

	void onPlayerTakeDamage(IPlayer& player, IPlayer* from, float amount, unsigned weapon, BodyPart part) override
	{
		gamemode_->call<unsigned char>("onPlayerTakeDamage", static_cast<void*>(&player), static_cast<void*>(from), amount, weapon, int(part));
	}

	void onPlayerGiveDamage(IPlayer& player, IPlayer& to, float amount, unsigned weapon, BodyPart part) override
	{
		gamemode_->call<unsigned char>("onPlayerGiveDamage", static_cast<void*>(&player), static_cast<void*>(&to), amount, weapon, int(part));
	}

	// Player click events

	void onPlayerClickMap(IPlayer& player, Vector3 pos) override
	{
		gamemode_->call<unsigned char>("onPlayerClickMap", static_cast<void*>(&player), pos);
	}

	void onPlayerClickPlayer(IPlayer& player, IPlayer& clicked, PlayerClickSource source) override
	{
		gamemode_->call<unsigned char>("onPlayerClickPlayer", static_cast<void*>(&player), static_cast<void*>(&clicked), int(source));
	}

	// Player check events

	void onClientCheckResponse(IPlayer& player, int actionType, int address, int results) override
	{
		gamemode_->call<unsigned char>("onClientCheckResponse", static_cast<void*>(&player), actionType, address, results);
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
