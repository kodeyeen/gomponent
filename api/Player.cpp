#include <iostream>

#include "api.hpp"
#include "Gomponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct
	{
		int hours;
		int minutes;
	} PlayerTime;

	typedef struct
	{
		unsigned char spectating;
		int spectateID;
		int type;
	} CPlayerSpectateData;

	typedef struct
	{
		Vector3 position;
		float radius;
		unsigned char isEnabled;
	} Checkpoint;

	// Player

	GOMPONENT_EXPORT void* player_getByID(int id)
	{
		IPlayerPool* players = Gomponent::Get()->players;

		if (players)
		{
			IPlayer* player = players->get(id);

			if (player)
			{
				return static_cast<void*>(player);
			}

		}

		return NULL;
	}

	GOMPONENT_EXPORT Array player_getAll()
	{
		IPlayerPool* pool = Gomponent::Get()->players;
		const FlatPtrHashSet<IPlayer>& players = pool->entries();

		Array arr;
		arr.length = players.size();
		arr.buf = new void*[arr.length];

		size_t i = 0;
		for (IPlayer* player : players)
		{
			if (i < arr.length)
			{
				arr.buf[i++] = static_cast<void*>(player);
			}
		}

		return arr;
	}

	GOMPONENT_EXPORT void player_sendDeathMessageToAll(void* killer, void* killee, int weapon)
	{
		IPlayerPool* players = Gomponent::Get()->players;
		players->sendDeathMessageToAll(static_cast<IPlayer*>(killer), *static_cast<IPlayer*>(killee), weapon);
	}

	GOMPONENT_EXPORT void player_sendEmptyDeathMessageToAll()
	{
		IPlayerPool* players = Gomponent::Get()->players;
		players->sendEmptyDeathMessageToAll();
	}

	GOMPONENT_EXPORT int player_getID(void* player)
	{
		return static_cast<IPlayer*>(player)->getID();
	}

	GOMPONENT_EXPORT void player_kick(void* player)
	{
		return static_cast<IPlayer*>(player)->kick();
	}

	GOMPONENT_EXPORT void player_ban(void* player, String reason)
	{
		return static_cast<IPlayer*>(player)->ban(StringView(reason.buf, reason.length));
	}

	GOMPONENT_EXPORT int player_isBot(void* player)
	{
		return static_cast<IPlayer*>(player)->isBot() ? 1 : 0;
	}

	// virtual const PeerNetworkData& getNetworkData() const = 0;

	GOMPONENT_EXPORT unsigned player_getPing(void* player)
	{
		return static_cast<IPlayer*>(player)->getPing();
	}

	GOMPONENT_EXPORT void player_spawn(void* player)
	{
		return static_cast<IPlayer*>(player)->spawn();
	}

	GOMPONENT_EXPORT int player_isSpawned(void* player)
	{
		PlayerState state = static_cast<IPlayer*>(player)->getState();

		switch (state)
		{
		case PlayerState_OnFoot:
		case PlayerState_Driver:
		case PlayerState_Passenger:
		case PlayerState_Spawned:
		{
			return 1;
		}
		default:
			return 0;
		}
	}

	GOMPONENT_EXPORT uint8_t player_getClientVersion(void* player)
	{
		return (uint8_t) static_cast<IPlayer*>(player)->getClientVersion();
	}

	GOMPONENT_EXPORT String player_getClientVersionName(void* player)
	{
		StringView nameView = static_cast<IPlayer*>(player)->getClientVersionName();

		return { nameView.data(), nameView.length() };
	}

	GOMPONENT_EXPORT void player_setPositionFindZ(void* player, float x, float y, float z)
	{
		return static_cast<IPlayer*>(player)->setPositionFindZ(Vector3(x, y, z));
	}

	GOMPONENT_EXPORT void player_setCameraPosition(void* player, float x, float y, float z)
	{
		return static_cast<IPlayer*>(player)->setCameraPosition(Vector3(x, y, z));
	}

	GOMPONENT_EXPORT Vector3 player_getCameraPosition(void* player)
	{
		return static_cast<IPlayer*>(player)->getCameraPosition();
	}

	GOMPONENT_EXPORT void player_setCameraLookAt(void* player, float x, float y, float z, int cutType)
	{
		return static_cast<IPlayer*>(player)->setCameraLookAt(Vector3(x, y, z), cutType);
	}

	GOMPONENT_EXPORT Vector3 player_getCameraLookAt(void* player)
	{
		return static_cast<IPlayer*>(player)->getCameraLookAt();
	}

	GOMPONENT_EXPORT void player_setCameraBehind(void* player)
	{
		return static_cast<IPlayer*>(player)->setCameraBehind();
	}

	GOMPONENT_EXPORT void player_interpolateCameraPosition(void* player, float fromX, float fromY, float fromZ, float toX, float toY, float toZ, int time, int cutType)
	{
		return static_cast<IPlayer*>(player)->interpolateCameraPosition(Vector3(fromX, fromY, fromZ), Vector3(toX, toY, toZ), time, PlayerCameraCutType(cutType));
	}

	GOMPONENT_EXPORT void player_interpolateCameraLookAt(void* player, float fromX, float fromY, float fromZ, float toX, float toY, float toZ, int time, int cutType)
	{
		return static_cast<IPlayer*>(player)->interpolateCameraLookAt(Vector3(fromX, fromY, fromZ), Vector3(toX, toY, toZ), time, PlayerCameraCutType(cutType));
	}

	GOMPONENT_EXPORT void player_attachCameraToObject(void* player, void* object)
	{
		return static_cast<IPlayer*>(player)->attachCameraToObject(*static_cast<IObject*>(player));
	}

	// virtual void attachCameraToObject(IPlayerObject& object) = 0;

	GOMPONENT_EXPORT int player_setName(void* player, String name)
	{
		return (int)static_cast<IPlayer*>(player)->setName(StringView(name.buf, name.length));
	}

	GOMPONENT_EXPORT String player_getName(void* player)
	{
		StringView nameView = static_cast<IPlayer*>(player)->getName();

		return { nameView.data(), nameView.length() };
	}

	GOMPONENT_EXPORT String player_getSerial(void* player)
	{
		StringView serialView = static_cast<IPlayer*>(player)->getSerial();

		return { serialView.data(), serialView.length() };
	}

	GOMPONENT_EXPORT void player_giveWeapon(void* player, uint8_t id, uint32_t ammo)
	{
		return static_cast<IPlayer*>(player)->giveWeapon(WeaponSlotData(id, ammo));
	}

	GOMPONENT_EXPORT void player_removeWeapon(void* player, uint8_t weapon)
	{
		return static_cast<IPlayer*>(player)->removeWeapon(weapon);
	}

	GOMPONENT_EXPORT void player_setWeaponAmmo(void* player, uint8_t id, uint32_t ammo)
	{
		return static_cast<IPlayer*>(player)->setWeaponAmmo(WeaponSlotData(id, ammo));
	}

	GOMPONENT_EXPORT Array player_getWeapons(void* player)
	{
		const WeaponSlots& weapons = static_cast<IPlayer*>(player)->getWeapons();

		Array arr = newArray(weapons.size());

		size_t i = 0;
		for (const WeaponSlotData& weapon : weapons)
		{
			if (i < arr.length)
			{
				arr.buf[i++] = static_cast<void*>(const_cast<WeaponSlotData*>(&weapon));
			}
		}

		return arr;
	}

	GOMPONENT_EXPORT WeaponSlotData player_getWeaponSlot(void* player, int slot)
	{
		return static_cast<IPlayer*>(player)->getWeaponSlot(slot);
	}

	GOMPONENT_EXPORT void player_resetWeapons(void* player)
	{
		return static_cast<IPlayer*>(player)->resetWeapons();
	}

	GOMPONENT_EXPORT void player_setArmedWeapon(void* player, uint32_t weapon)
	{
		return static_cast<IPlayer*>(player)->setArmedWeapon(weapon);
	}

	GOMPONENT_EXPORT uint32_t player_getArmedWeapon(void* player)
	{
		return static_cast<IPlayer*>(player)->getArmedWeapon();
	}

	GOMPONENT_EXPORT uint32_t player_getArmedWeaponAmmo(void* player)
	{
		return static_cast<IPlayer*>(player)->getArmedWeaponAmmo();
	}

	GOMPONENT_EXPORT void player_setShopName(void* player, String name)
	{
		return static_cast<IPlayer*>(player)->setShopName(StringView(name.buf, name.length));
	}

	GOMPONENT_EXPORT String player_getShopName(void* player)
	{
		StringView nameView = static_cast<IPlayer*>(player)->getShopName();

		return { nameView.data(), nameView.size() };
	}

	GOMPONENT_EXPORT void player_setDrunkLevel(void* player, int level)
	{
		return static_cast<IPlayer*>(player)->setDrunkLevel(level);
	}

	GOMPONENT_EXPORT int player_getDrunkLevel(void* player)
	{
		return static_cast<IPlayer*>(player)->getDrunkLevel();
	}

	GOMPONENT_EXPORT void player_setColour(void* player, uint32_t colour)
	{
		return static_cast<IPlayer*>(player)->setColour(Colour::FromRGBA(colour));
	}

	GOMPONENT_EXPORT uint32_t player_getColour(void* player)
	{
		return static_cast<IPlayer*>(player)->getColour().RGBA();
	}

	GOMPONENT_EXPORT void player_setOtherColour(void* player, void* other, uint32_t colour)
	{
		return static_cast<IPlayer*>(player)->setOtherColour(*static_cast<IPlayer*>(other), Colour::FromRGBA(colour));
	}

	GOMPONENT_EXPORT int player_getOtherColour(void* player, void* other, uint32_t* colour)
	{
		Colour col;
		bool hasPlayerSpecificColour = static_cast<IPlayer*>(player)->getOtherColour(*static_cast<IPlayer*>(other), col);

		*colour = col.RGBA();

		return hasPlayerSpecificColour ? 1 : 0;
	}

	GOMPONENT_EXPORT void player_setControllable(void* player, int controllable)
	{
		return static_cast<IPlayer*>(player)->setControllable(controllable != 0);
	}

	GOMPONENT_EXPORT int player_getControllable(void* player)
	{
		return static_cast<IPlayer*>(player)->getControllable() ? 1 : 0;
	}

	GOMPONENT_EXPORT void player_setSpectating(void* player, int spectating)
	{
		return static_cast<IPlayer*>(player)->setSpectating(spectating != 0);
	}

	GOMPONENT_EXPORT void player_setWantedLevel(void* player, unsigned level)
	{
		return static_cast<IPlayer*>(player)->setWantedLevel(level);
	}

	GOMPONENT_EXPORT unsigned player_getWantedLevel(void* player)
	{
		return static_cast<IPlayer*>(player)->getWantedLevel();
	}

	GOMPONENT_EXPORT void player_playSound(void* player, uint32_t sound, float posX, float posY, float posZ)
	{
		return static_cast<IPlayer*>(player)->playSound(sound, Vector3(posX, posY, posZ));
	}

	GOMPONENT_EXPORT uint32_t player_lastPlayedSound(void* player)
	{
		return static_cast<IPlayer*>(player)->lastPlayedSound();
	}

	GOMPONENT_EXPORT void player_playAudio(void* player, String url, unsigned char usePos, float posX, float posY, float posZ, float distance)
	{
		return static_cast<IPlayer*>(player)->playAudio(StringView(url.buf, url.length), usePos != 0, Vector3(posX, posY, posZ), distance);
	}

	GOMPONENT_EXPORT int player_playerCrimeReport(void* player, void* suspect, int crime)
	{
		return static_cast<IPlayer*>(player)->playerCrimeReport(*static_cast<IPlayer*>(suspect), crime) ? 1 : 0;
	}

	GOMPONENT_EXPORT void player_stopAudio(void* player)
	{
		return static_cast<IPlayer*>(player)->stopAudio();
	}

	GOMPONENT_EXPORT String player_lastPlayedAudio(void* player)
	{
		StringView audioView = static_cast<IPlayer*>(player)->lastPlayedAudio();

		return { audioView.data(), audioView.size() };
	}

	GOMPONENT_EXPORT void player_createExplosion(void* player, float vecX, float vecY, float vecZ, int type, float radius)
	{
		return static_cast<IPlayer*>(player)->createExplosion(Vector3(vecX, vecY, vecZ), type, radius);
	}

	GOMPONENT_EXPORT void player_sendDeathMessage(void* player, void* killee, void* killer, int weapon)
	{
		return static_cast<IPlayer*>(player)->sendDeathMessage(*static_cast<IPlayer*>(killee), static_cast<IPlayer*>(killer), weapon);
	}

	GOMPONENT_EXPORT void player_sendEmptyDeathMessage(void* player)
	{
		return static_cast<IPlayer*>(player)->sendEmptyDeathMessage();
	}

	GOMPONENT_EXPORT void player_removeDefaultObjects(void* player, unsigned model, float posX, float posY, float posZ, float radius)
	{
		return static_cast<IPlayer*>(player)->removeDefaultObjects(model, Vector3(posX, posY, posZ), radius);
	}

	GOMPONENT_EXPORT void player_forceClassSelection(void* player)
	{
		return static_cast<IPlayer*>(player)->forceClassSelection();
	}

	GOMPONENT_EXPORT void player_setMoney(void* player, int money)
	{
		return static_cast<IPlayer*>(player)->setMoney(money);
	}

	GOMPONENT_EXPORT void player_giveMoney(void* player, int money)
	{
		return static_cast<IPlayer*>(player)->giveMoney(money);
	}

	GOMPONENT_EXPORT void player_resetMoney(void* player)
	{
		return static_cast<IPlayer*>(player)->resetMoney();
	}

	GOMPONENT_EXPORT int player_getMoney(void* player)
	{
		return static_cast<IPlayer*>(player)->getMoney();
	}

	GOMPONENT_EXPORT void player_setMapIcon(void* player, int id, float posX, float posY, float posZ, int type, uint32_t colour, int style)
	{
		return static_cast<IPlayer*>(player)->setMapIcon(id, Vector3(posX, posY, posZ), type, Colour::FromRGBA(colour), MapIconStyle(style));
	}

	GOMPONENT_EXPORT void player_unsetMapIcon(void* player, int id)
	{
		return static_cast<IPlayer*>(player)->unsetMapIcon(id);
	}

	GOMPONENT_EXPORT void player_useStuntBonuses(void* player, int enable)
	{
		return static_cast<IPlayer*>(player)->useStuntBonuses(enable != 0);
	}

	GOMPONENT_EXPORT void player_toggleOtherNameTag(void* player, void* other, int toggle)
	{
		return static_cast<IPlayer*>(player)->toggleOtherNameTag(*static_cast<IPlayer*>(other), toggle != 0);
	}

	GOMPONENT_EXPORT void player_setTime(void* player, int hr, int min)
	{
		return static_cast<IPlayer*>(player)->setTime(std::chrono::hours(hr), std::chrono::minutes(min));
	}

	GOMPONENT_EXPORT PlayerTime player_getTime(void* player)
	{
		std::pair<std::chrono::hours, std::chrono::minutes> data = static_cast<IPlayer*>(player)->getTime();

		return { data.first.count(), data.second.count() };
	}

	GOMPONENT_EXPORT void player_useClock(void* player, int enable)
	{
		return static_cast<IPlayer*>(player)->useClock(enable != 0);
	}

	GOMPONENT_EXPORT int player_hasClock(void* player)
	{
		return static_cast<IPlayer*>(player)->hasClock() ? 1 : 0;
	}

	GOMPONENT_EXPORT void player_useWidescreen(void* player, int enable)
	{
		return static_cast<IPlayer*>(player)->useWidescreen(enable != 0);
	}

	GOMPONENT_EXPORT int player_hasWidescreen(void* player)
	{
		return static_cast<IPlayer*>(player)->hasWidescreen() ? 1 : 0;
	}

	// TODO
	// virtual void setTransform(GTAQuat tm) = 0;

	GOMPONENT_EXPORT void player_setHealth(void* player, float health)
	{
		return static_cast<IPlayer*>(player)->setHealth(health);
	}

	GOMPONENT_EXPORT float player_getHealth(void* player)
	{
		return static_cast<IPlayer*>(player)->getHealth();
	}

	GOMPONENT_EXPORT void player_setScore(void* player, int score)
	{
		return static_cast<IPlayer*>(player)->setScore(score);
	}

	GOMPONENT_EXPORT int player_getScore(void* player)
	{
		return static_cast<IPlayer*>(player)->getScore();
	}

	GOMPONENT_EXPORT void player_setArmour(void* player, float armour)
	{
		return static_cast<IPlayer*>(player)->setArmour(armour);
	}

	GOMPONENT_EXPORT float player_getArmour(void* player)
	{
		return static_cast<IPlayer*>(player)->getArmour();
	}

	GOMPONENT_EXPORT void player_setGravity(void* player, float gravity)
	{
		return static_cast<IPlayer*>(player)->setGravity(gravity);
	}

	GOMPONENT_EXPORT float player_getGravity(void* player)
	{
		return static_cast<IPlayer*>(player)->getGravity();
	}

	GOMPONENT_EXPORT void player_setWorldTime(void* player, int time)
	{
		return static_cast<IPlayer*>(player)->setWorldTime(std::chrono::hours(time));
	}

	GOMPONENT_EXPORT void player_applyAnimation(void* player, float delta, unsigned char loop, unsigned char lockX, unsigned char lockY, unsigned char freeze, uint32_t time, String lib, String name, int syncType)
	{
		const AnimationData animationData(delta, loop, lockX, lockY, freeze, time, StringView(lib.buf, lib.length), StringView(name.buf, name.length));
		return static_cast<IPlayer*>(player)->applyAnimation(animationData, PlayerAnimationSyncType(syncType));
	}

	GOMPONENT_EXPORT void player_clearAnimations(void* player, int syncType)
	{
		return static_cast<IPlayer*>(player)->clearAnimations(PlayerAnimationSyncType(syncType));
	}

	GOMPONENT_EXPORT PlayerAnimationData player_getAnimationData(void* player)
	{
		return static_cast<IPlayer*>(player)->getAnimationData();
	}

	// TODO
	// virtual PlayerSurfingData getSurfingData() const = 0;

	GOMPONENT_EXPORT int player_isStreamedInForPlayer(void* player, void* other)
	{
		return static_cast<IPlayer*>(player)->isStreamedInForPlayer(*static_cast<IPlayer*>(other)) ? 1 : 0;
	}

	GOMPONENT_EXPORT int player_getState(void* player)
	{
		return static_cast<IPlayer*>(player)->getState();
	}

	GOMPONENT_EXPORT void player_setTeam(void* player, int team)
	{
		return static_cast<IPlayer*>(player)->setTeam(team);
	}

	GOMPONENT_EXPORT int player_getTeam(void* player)
	{
		return static_cast<IPlayer*>(player)->getTeam();
	}

	GOMPONENT_EXPORT void player_setSkin(void* player, int skin, int send)
	{
		return static_cast<IPlayer*>(player)->setSkin(skin, send != 0);
	}

	GOMPONENT_EXPORT int player_getSkin(void* player)
	{
		return static_cast<IPlayer*>(player)->getSkin();
	}

	GOMPONENT_EXPORT void player_setChatBubble(void* player, String text, uint32_t colour, float drawDist, int expire)
	{
		return static_cast<IPlayer*>(player)->setChatBubble(StringView(text.buf, text.length), Colour::FromRGBA(colour), drawDist, std::chrono::milliseconds(expire));
	}

	GOMPONENT_EXPORT void player_sendClientMessage(void* player, uint32_t colour, String message)
	{
		return static_cast<IPlayer*>(player)->sendClientMessage(Colour::FromRGBA(colour), StringView(message.buf, message.length));
	}

	GOMPONENT_EXPORT void player_sendChatMessage(void* player, void* sender, String message)
	{
		return static_cast<IPlayer*>(player)->sendChatMessage(*static_cast<IPlayer*>(sender), StringView(message.buf, message.length));
	}

	GOMPONENT_EXPORT void player_sendCommand(void* player, String message)
	{
		return static_cast<IPlayer*>(player)->sendCommand(StringView(message.buf, message.length));
	}

	GOMPONENT_EXPORT void player_sendGameText(void* player, String message, int time, int style)
	{
		return static_cast<IPlayer*>(player)->sendGameText(StringView(message.buf, message.length), std::chrono::milliseconds(time), style);
	}

	GOMPONENT_EXPORT void player_hideGameText(void* player, int style)
	{
		return static_cast<IPlayer*>(player)->hideGameText(style);
	}

	GOMPONENT_EXPORT int player_hasGameText(void* player, int style)
	{
		return static_cast<IPlayer*>(player)->hasGameText(style) ? 1 : 0;
	}

	GOMPONENT_EXPORT int player_getGameText(void* player, int style, String* message, int* time, int* remaining)
	{
		Milliseconds mt;
		Milliseconds mr;
		StringView ms;

		if (static_cast<IPlayer*>(player)->getGameText(style, ms, mt, mr))
		{
			*message = { ms.data(), ms.size() };
			*time = (int)mt.count();
			*remaining = (int)mr.count();
			return true;
		}

		return false;
	}

	GOMPONENT_EXPORT void player_setWeather(void* player, int weatherID)
	{
		return static_cast<IPlayer*>(player)->setWeather(weatherID);
	}

	GOMPONENT_EXPORT int player_getWeather(void* player)
	{
		return static_cast<IPlayer*>(player)->getWeather();
	}

	GOMPONENT_EXPORT void player_setWorldBounds(void* player, float x, float y, float z, float w)
	{
		return static_cast<IPlayer*>(player)->setWorldBounds(Vector4(x, y, z, w));
	}

	GOMPONENT_EXPORT void player_setFightingStyle(void* player, int style)
	{
		return static_cast<IPlayer*>(player)->setFightingStyle(PlayerFightingStyle(style));
	}

	GOMPONENT_EXPORT int player_getFightingStyle(void* player)
	{
		return (int)static_cast<IPlayer*>(player)->getFightingStyle();
	}

	GOMPONENT_EXPORT void player_setSkillLevel(void* player, int skill, int level)
	{
		return static_cast<IPlayer*>(player)->setSkillLevel(PlayerWeaponSkill(skill), level);
	}

	GOMPONENT_EXPORT void player_setAction(void* player, int action)
	{
		return static_cast<IPlayer*>(player)->setAction(PlayerSpecialAction(action));
	}

	GOMPONENT_EXPORT int player_getAction(void* player)
	{
		return static_cast<IPlayer*>(player)->getAction();
	}

	GOMPONENT_EXPORT void player_setVelocity(void* player, float velX, float velY, float velZ)
	{
		return static_cast<IPlayer*>(player)->setVelocity(Vector3(velX, velY, velZ));
	}

	GOMPONENT_EXPORT Vector3 player_getVelocity(void* player)
	{
		return static_cast<IPlayer*>(player)->getVelocity();
	}

	GOMPONENT_EXPORT void player_setInterior(void* player, unsigned interior)
	{
		return static_cast<IPlayer*>(player)->setInterior(interior);
	}

	GOMPONENT_EXPORT unsigned player_getInterior(void* player)
	{
		return static_cast<IPlayer*>(player)->getInterior();
	}

	GOMPONENT_EXPORT PlayerKeyData player_getKeyData(void* player)
	{
		return static_cast<IPlayer*>(player)->getKeyData();
	}

	// TODO
	// virtual const StaticArray<uint16_t, NUM_SKILL_LEVELS>& getSkillLevels() const = 0;

	GOMPONENT_EXPORT const PlayerAimData* player_getAimData(void* player)
	{
		return &static_cast<IPlayer*>(player)->getAimData();
	}

	GOMPONENT_EXPORT const PlayerBulletData* player_getBulletData(void* player)
	{
		return &static_cast<IPlayer*>(player)->getBulletData();
	}

	GOMPONENT_EXPORT void player_useCameraTargeting(void* player, int enable)
	{
		return static_cast<IPlayer*>(player)->useCameraTargeting(enable != 0);
	}

	GOMPONENT_EXPORT unsigned char player_hasCameraTargetting(void* player)
	{
		return static_cast<IPlayer*>(player)->hasCameraTargeting() ? 1 : 0;
	}

	GOMPONENT_EXPORT void player_removeFromVehicle(void* player, unsigned char force)
	{
		return static_cast<IPlayer*>(player)->removeFromVehicle(force != 0);
	}

	GOMPONENT_EXPORT void* player_getCameraTargetPlayer(void* player)
	{
		IPlayer* targetPlayer = static_cast<IPlayer*>(player)->getCameraTargetPlayer();
		return static_cast<void*>(targetPlayer);
	}

	GOMPONENT_EXPORT void* player_getCameraTargetVehicle(void* player)
	{
		IVehicle* targetVehicle = static_cast<IPlayer*>(player)->getCameraTargetVehicle();
		return static_cast<void*>(targetVehicle);
	}

	GOMPONENT_EXPORT void* player_getCameraTargetObject(void* player)
	{
		IObject* targetObject = static_cast<IPlayer*>(player)->getCameraTargetObject();
		return static_cast<void*>(targetObject);
	}

	GOMPONENT_EXPORT void* player_getCameraTargetActor(void* player)
	{
		IActor* targetActor = static_cast<IPlayer*>(player)->getCameraTargetActor();
		return static_cast<void*>(targetActor);
	}

	GOMPONENT_EXPORT void* player_getTargetPlayer(void* player)
	{
		IPlayer* targetPlayer = static_cast<IPlayer*>(player)->getTargetPlayer();
		return static_cast<void*>(targetPlayer);
	}

	GOMPONENT_EXPORT void* player_getTargetActor(void* player)
	{
		IActor* targetActor = static_cast<IPlayer*>(player)->getTargetActor();
		return static_cast<void*>(targetActor);
	}

	GOMPONENT_EXPORT void player_setRemoteVehicleCollisions(void* player, int collide)
	{
		return static_cast<IPlayer*>(player)->setRemoteVehicleCollisions(collide != 0);
	}

	GOMPONENT_EXPORT void player_spectatePlayer(void* player, void* target, int mode)
	{
		return static_cast<IPlayer*>(player)->spectatePlayer(*static_cast<IPlayer*>(target), PlayerSpectateMode(mode));
	}

	GOMPONENT_EXPORT void player_spectateVehicle(void* player, void* target, int mode)
	{
		return static_cast<IPlayer*>(player)->spectateVehicle(*static_cast<IVehicle*>(target), PlayerSpectateMode(mode));
	}

	GOMPONENT_EXPORT CPlayerSpectateData player_getSpectateData(void* player)
	{
		auto data = &static_cast<IPlayer*>(player)->getSpectateData();
		return {
			(unsigned char)(data->spectating ? 1 : 0),
			data->spectateID,
			static_cast<int>(data->type)
		};
	}

	GOMPONENT_EXPORT void player_sendClientCheck(void* player, int actionType, int address, int offset, int count)
	{
		return static_cast<IPlayer*>(player)->sendClientCheck(actionType, address, offset, count);
	}

	GOMPONENT_EXPORT void player_toggleGhostMode(void* player, int toggle)
	{
		return static_cast<IPlayer*>(player)->toggleGhostMode(toggle != 0);
	}

	GOMPONENT_EXPORT int player_isGhostModeEnabled(void* player)
	{
		return static_cast<IPlayer*>(player)->isGhostModeEnabled() ? 1 : 0;
	}

	GOMPONENT_EXPORT int player_getDefaultObjectsRemoved(void* player)
	{
		return static_cast<IPlayer*>(player)->getDefaultObjectsRemoved();
	}

	GOMPONENT_EXPORT int player_getKickStatus(void* player)
	{
		return static_cast<IPlayer*>(player)->getKickStatus() ? 1 : 0;
	}

	GOMPONENT_EXPORT void player_clearTasks(void* player, PlayerAnimationSyncType syncType)
	{
		return static_cast<IPlayer*>(player)->clearTasks(syncType);
	}

	GOMPONENT_EXPORT void player_allowWeapons(void* player, int allow)
	{
		return static_cast<IPlayer*>(player)->allowWeapons(allow != 0);
	}

	GOMPONENT_EXPORT int player_areWeaponsAllowed(void* player)
	{
		return static_cast<IPlayer*>(player)->areWeaponsAllowed() ? 1 : 0;
	}

	GOMPONENT_EXPORT void player_allowTeleport(void* player, int allow)
	{
		return static_cast<IPlayer*>(player)->allowTeleport(allow != 0);
	}

	GOMPONENT_EXPORT int player_isTeleportAllowed(void* player)
	{
		return static_cast<IPlayer*>(player)->isTeleportAllowed() ? 1 : 0;
	}

	GOMPONENT_EXPORT int player_isUsingOfficialClient(void* player)
	{
		return static_cast<IPlayer*>(player)->isUsingOfficialClient() ? 1 : 0;
	}

	// entity

	GOMPONENT_EXPORT void player_setPosition(void* player, float posX, float posY, float posZ)
	{
		return static_cast<IPlayer*>(player)->setPosition(Vector3(posX, posY, posZ));
	}

	GOMPONENT_EXPORT Vector3 player_getPosition(void* player)
	{
		return static_cast<IPlayer*>(player)->getPosition();
	}

	GOMPONENT_EXPORT Vector4 player_getRotation(void* player)
	{
		glm::quat rotQuat = static_cast<IPlayer*>(player)->getRotation().q;

		return Vector4(rotQuat.x, rotQuat.y, rotQuat.z, rotQuat.w);
	}

	GOMPONENT_EXPORT void player_setVirtualWorld(void* player, int vw)
	{
		return static_cast<IPlayer*>(player)->setVirtualWorld(vw);
	}

	GOMPONENT_EXPORT int player_getVirtualWorld(void* player)
	{
		return static_cast<IPlayer*>(player)->getVirtualWorld();
	}

	// checkpoint data

	GOMPONENT_EXPORT void* player_getCheckpoint(void* player)
	{
		IPlayerCheckpointData* data = queryExtension<IPlayerCheckpointData>(static_cast<IPlayer*>(player));
		ICheckpointData& cp = data->getCheckpoint();

		return &cp;
	}

	GOMPONENT_EXPORT void* player_getRaceCheckpoint(void* player)
	{
		IPlayerCheckpointData* data = queryExtension<IPlayerCheckpointData>(static_cast<IPlayer*>(player));
		IRaceCheckpointData& cp = data->getRaceCheckpoint();

		return &cp;
	}

	// console data

	GOMPONENT_EXPORT void player_setConsoleAccessibility(void* player, int set)
	{
		IPlayerConsoleData* data = queryExtension<IPlayerConsoleData>(static_cast<IPlayer*>(player));

		if (!data)
		{
			return;
		}

		return data->setConsoleAccessibility(set != 0);
	}

	GOMPONENT_EXPORT int player_hasConsoleAccess(void* player)
	{
		IPlayerConsoleData* data = queryExtension<IPlayerConsoleData>(static_cast<IPlayer*>(player));

		if (!data)
		{
			return 0;
		}

		return data->hasConsoleAccess() ? 1 : 0;
	}

	// custom models data

	GOMPONENT_EXPORT int player_getCustomSkin(void* player)
	{
		IPlayerCustomModelsData* data = queryExtension<IPlayerCustomModelsData>(static_cast<IPlayer*>(player));

		if (!data)
		{
			return 0;
		}

		return data->getCustomSkin();
	}

	// network data

	GOMPONENT_EXPORT String player_getIp(void* player)
	{
		PeerNetworkData data = static_cast<IPlayer*>(player)->getNetworkData();

		if (!data.networkID.address.ipv6)
		{
			PeerAddress::AddressString addressString;
			if (PeerAddress::ToString(data.networkID.address, addressString))
			{
				auto ip = StringView(addressString);
				return { ip.data(), ip.length() };
			}
		}

		return { "", 0 };
	}

	GOMPONENT_EXPORT uint32_t player_getRawIp(void* player)
	{
		PeerNetworkData data = static_cast<IPlayer*>(player)->getNetworkData();

		return data.networkID.address.v4;
	}

	// vehicle data

	GOMPONENT_EXPORT void* player_getVehicle(void* player)
	{
		IPlayerVehicleData* data = queryExtension<IPlayerVehicleData>(static_cast<IPlayer*>(player));

		if (!data)
		{
			return NULL;
		}

		IVehicle* vehicle = data->getVehicle();

		return vehicle ? static_cast<void*>(vehicle) : NULL;
	}

	GOMPONENT_EXPORT int player_getSeat(void* player)
	{
		IPlayerVehicleData* data = queryExtension<IPlayerVehicleData>(static_cast<IPlayer*>(player));

		if (data)
		{
			return data->getSeat();
		}

		return -1;
	}

	GOMPONENT_EXPORT int player_isInModShop(void* player)
	{
		IPlayerVehicleData* data = queryExtension<IPlayerVehicleData>(static_cast<IPlayer*>(player));

		if (data)
		{
			return data->isInModShop() ? 1 : 0;
		}

		return 0;
	}

	// object data

	GOMPONENT_EXPORT void player_beginObjectEditing(void* player, void* object)
	{
		IPlayerObjectData* data = queryExtension<IPlayerObjectData>(static_cast<IPlayer*>(player));
		return data->beginEditing(*static_cast<IObject*>(object));
	}

	GOMPONENT_EXPORT void player_endObjectEditing(void* player)
	{
		IPlayerObjectData* data = queryExtension<IPlayerObjectData>(static_cast<IPlayer*>(player));
		return data->endEditing();
	}

	GOMPONENT_EXPORT unsigned char player_isEditingObject(void* player)
	{
		IPlayerObjectData* data = queryExtension<IPlayerObjectData>(static_cast<IPlayer*>(player));
		return data->editingObject() ? 1 : 0;
	}

	GOMPONENT_EXPORT void player_beginObjectSelecting(void* player)
	{
		IPlayerObjectData* data = queryExtension<IPlayerObjectData>(static_cast<IPlayer*>(player));
		return data->beginSelecting();
	}

	GOMPONENT_EXPORT unsigned char player_isSelectingObject(void* player)
	{
		IPlayerObjectData* data = queryExtension<IPlayerObjectData>(static_cast<IPlayer*>(player));
		return data->selectingObject() ? 1 : 0;
	}

	GOMPONENT_EXPORT void player_setAttachedObject(void* player, int index, int modelId, int bone, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, uint32_t colour1, uint32_t colour2)
	{
		ObjectAttachmentSlotData attachment;
		attachment.model = modelId;
		attachment.bone = bone;
		attachment.offset = Vector3(offsetX, offsetY, offsetZ);
		attachment.rotation = Vector3(rotX, rotY, rotZ);
		attachment.scale = Vector3(scaleX, scaleY, scaleZ);
		attachment.colour1 = Colour::FromARGB(colour1);
		attachment.colour2 = Colour::FromARGB(colour2);

		IPlayerObjectData* data = queryExtension<IPlayerObjectData>(static_cast<IPlayer*>(player));
		return data->setAttachedObject(index, attachment);
	}

	GOMPONENT_EXPORT PlayerAttachedObject player_getAttachedObject(void* player, int index)
	{
		IPlayerObjectData* data = queryExtension<IPlayerObjectData>(static_cast<IPlayer*>(player));

		ObjectAttachmentSlotData attachment = data->getAttachedObject(index);

		PlayerAttachedObject obj;
		obj.model = attachment.model;
		obj.bone = attachment.bone;
		obj.offset = attachment.offset;
		obj.rotation = attachment.rotation;
		obj.scale = attachment.scale;
		obj.colour1 = attachment.colour1.ARGB();
		obj.colour2 = attachment.colour2.ARGB();

		return obj;
	}

	GOMPONENT_EXPORT void player_removeAttachedObject(void* player, int index)
	{
		IPlayerObjectData* data = queryExtension<IPlayerObjectData>(static_cast<IPlayer*>(player));
		return data->removeAttachedObject(index);
	}

	GOMPONENT_EXPORT void player_editAttachedObject(void* player, int index)
	{
		IPlayerObjectData* data = queryExtension<IPlayerObjectData>(static_cast<IPlayer*>(player));
		return data->editAttachedObject(index);
	}

	GOMPONENT_EXPORT unsigned char player_hasAttachedObject(void* player, int index)
	{
		IPlayerObjectData* data = queryExtension<IPlayerObjectData>(static_cast<IPlayer*>(player));
		return data->hasAttachedObject(index) ? 1 : 0;
	}
	

	// misc

	GOMPONENT_EXPORT float player_getDistanceFromPoint(void* player, float pX, float pY, float pZ)
	{
		Vector3 playerCoords = static_cast<IPlayer*>(player)->getPosition();
		return glm::distance(playerCoords, Vector3(pX, pY, pZ));
	}

	GOMPONENT_EXPORT int player_isInRangeOfPoint(void* player, float range, float pX, float pY, float pZ)
	{
		return range >= glm::distance(static_cast<IPlayer*>(player)->getPosition(), Vector3(pX, pY, pZ)) ? 1 : 0;
	}

	GOMPONENT_EXPORT void player_setFacingAngle(void* player, float angle)
	{
		Vector3 rotation = static_cast<IPlayer*>(player)->getRotation().ToEuler();
		rotation.z = angle;
		static_cast<IPlayer*>(player)->setRotation(rotation);
	}

	GOMPONENT_EXPORT float player_getFacingAngle(void* player)
	{
		GTAQuat quat = static_cast<IPlayer*>(player)->getRotation();
		float angle = quat.ToEuler().z;

		return angle;
	}

#ifdef __cplusplus
}
#endif
