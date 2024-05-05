#include <sdk.hpp>

#include <api/api.hpp>
#include "Singleton.hpp"
#include "Gomponent.hpp"
#include "Gamemode.hpp"

typedef struct
{
	Vector3 origin;
	Vector3 hitPos;
	Vector3 offset;
	uint8_t weapon;
	uint8_t hitType;
	uint16_t hitID;
} CPlayerBulletData;

class PlayerEvents : public PlayerSpawnEventHandler, public PlayerConnectEventHandler, public PlayerStreamEventHandler, public PlayerTextEventHandler, public PlayerShotEventHandler, public PlayerChangeEventHandler, public PlayerDamageEventHandler, public PlayerClickEventHandler, public PlayerCheckEventHandler, public PlayerUpdateEventHandler, public Singleton<PlayerEvents>
{
public:
	PlayerEvents()
	{
		gamemode_ = Gomponent::Get()->getGamemode();
	}

	// Player spawn events

	bool onPlayerRequestSpawn(IPlayer& player) override {
		return gamemode_->call<unsigned char>("onPlayerRequestSpawn", static_cast<void*>(&player)) != 0;
	}

	void onPlayerSpawn(IPlayer& player) override
	{
		gamemode_->call<void>("onPlayerSpawn", static_cast<void*>(&player));
	}

	// Player connect events

	void onIncomingConnection(IPlayer& player, StringView ipAddress, unsigned short port) override
	{
		String ipAddressStr = { ipAddress.data(), ipAddress.length() };

		gamemode_->call<void>("onIncomingConnection", static_cast<void*>(&player), ipAddressStr, port);
	}

	void onPlayerConnect(IPlayer& player) override
	{
		gamemode_->call<void>("onPlayerConnect", static_cast<void*>(&player));
	}

	void onPlayerDisconnect(IPlayer& player, PeerDisconnectReason reason) override
	{
		gamemode_->call<void>("onPlayerDisconnect", static_cast<void*>(&player), static_cast<int>(reason));
	}

	void onPlayerClientInit(IPlayer& player) override
	{
		gamemode_->call<void>("onPlayerClientInit", static_cast<void*>(&player));
	}

	// Player stream events

	void onPlayerStreamIn(IPlayer& player, IPlayer& forPlayer) override
	{
		gamemode_->call<void>("onPlayerStreamIn", static_cast<void*>(&player), static_cast<void*>(&forPlayer));
	}

	void onPlayerStreamOut(IPlayer& player, IPlayer& forPlayer) override
	{
		gamemode_->call<void>("onPlayerStreamOut", static_cast<void*>(&player), static_cast<void*>(&forPlayer));
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
		gamemode_->call<void>("onPlayerScoreChange", static_cast<void*>(&player), score);
	}

	void onPlayerNameChange(IPlayer& player, StringView oldName) override
	{
		String oldNameStr = { oldName.data(), oldName.length() };

		gamemode_->call<void>("onPlayerNameChange", static_cast<void*>(&player), oldNameStr);
	}

	void onPlayerInteriorChange(IPlayer& player, unsigned newInterior, unsigned oldInterior) override
	{
		gamemode_->call<void>("onPlayerInteriorChange", static_cast<void*>(&player), newInterior, oldInterior);
	}

	void onPlayerStateChange(IPlayer& player, PlayerState newState, PlayerState oldState) override
	{
		gamemode_->call<void>("onPlayerStateChange", static_cast<void*>(&player), int(newState), int(oldState));
	}

	void onPlayerKeyStateChange(IPlayer& player, uint32_t newKeys, uint32_t oldKeys) override
	{
		gamemode_->call<void>("onPlayerKeyStateChange", static_cast<void*>(&player), newKeys, oldKeys);
	}

	// Player damage events

	void onPlayerDeath(IPlayer& player, IPlayer* killer, int reason) override
	{
		gamemode_->call<void>("onPlayerDeath", static_cast<void*>(&player), static_cast<void*>(killer), reason);
	}

	void onPlayerTakeDamage(IPlayer& player, IPlayer* from, float amount, unsigned weapon, BodyPart part) override
	{
		gamemode_->call<void>("onPlayerTakeDamage", static_cast<void*>(&player), static_cast<void*>(from), amount, weapon, int(part));
	}

	void onPlayerGiveDamage(IPlayer& player, IPlayer& to, float amount, unsigned weapon, BodyPart part) override
	{
		gamemode_->call<void>("onPlayerGiveDamage", static_cast<void*>(&player), static_cast<void*>(&to), amount, weapon, int(part));
	}

	// Player click events

	void onPlayerClickMap(IPlayer& player, Vector3 pos) override
	{
		gamemode_->call<void>("onPlayerClickMap", static_cast<void*>(&player), pos);
	}

	void onPlayerClickPlayer(IPlayer& player, IPlayer& clicked, PlayerClickSource source) override
	{
		gamemode_->call<void>("onPlayerClickPlayer", static_cast<void*>(&player), static_cast<void*>(&clicked), int(source));
	}

	// Player check events

	void onClientCheckResponse(IPlayer& player, int actionType, int address, int results) override
	{
		gamemode_->call<void>("onClientCheckResponse", static_cast<void*>(&player), actionType, address, results);
	}

	bool onPlayerUpdate(IPlayer& player, TimePoint now) override
	{
		auto nowMs = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
		auto value = nowMs.time_since_epoch();
		long long nowMillis = value.count();

		return gamemode_->call<unsigned char>("onPlayerUpdate", static_cast<void*>(&player), nowMillis) != 0;
	}

private:
	Gamemode* gamemode_;
};
