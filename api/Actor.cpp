#include <sdk.hpp>
#include "Server/Components/Actors/actors.hpp"

#include "api.hpp"
#include "Gomponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	struct CAnimationData
	{
		float delta;
		unsigned char loop;
		unsigned char lockX;
		unsigned char lockY;
		unsigned char freeze;
		uint32_t time;
		String lib;
		String name;
	};

	GOMPONENT_EXPORT void* actor_create(int skin, float posX, float posY, float posZ, float angle)
	{
		auto gamemode = Gomponent::Get()->getGamemode();
		IActorsComponent* actors = gamemode->actors;

		if (actors)
		{
			IActor* actor = actors->create(skin, Vector3(posX, posY, posZ), angle);
			if (actor)
			{
				return static_cast<void*>(actor);
			}
		}

		return NULL;
	}

	GOMPONENT_EXPORT void actor_release(void* actor)
	{
		auto gamemode = Gomponent::Get()->getGamemode();
		IActorsComponent* actors = gamemode->actors;

		if (actors)
		{
			return actors->release(static_cast<IActor*>(actor)->getID());
		}
	}

	GOMPONENT_EXPORT void actor_setSkin(void* actor, int skin)
	{
		return static_cast<IActor*>(actor)->setSkin(skin);
	}

	GOMPONENT_EXPORT int actor_getSkin(void* actor)
	{
		return static_cast<IActor*>(actor)->getSkin();
	}

	GOMPONENT_EXPORT void actor_applyAnimation(void* actor, float delta, unsigned char loop, unsigned char lockX, unsigned char lockY, unsigned char freeze, uint32_t time, String lib, String name)
	{
		return static_cast<IActor*>(actor)->applyAnimation(AnimationData(
			delta,
			loop != 0,
			lockX != 0,
			lockY != 0,
			freeze != 0,
			time,
			StringView(lib.buf, lib.length),
			StringView(name.buf, name.length)
		));
	}

	GOMPONENT_EXPORT CAnimationData actor_getAnimation(void* actor)
	{
		AnimationData anim = static_cast<IActor*>(actor)->getAnimation();
		String animLib = { anim.lib.data(), anim.lib.length() };
		String animName = { anim.name.data(), anim.name.length() };

		return {
			anim.delta,
			(unsigned char)(anim.loop ? 1 : 0),
			(unsigned char)(anim.lockX ? 1 : 0),
			(unsigned char)(anim.lockY ? 1 : 0),
			(unsigned char)(anim.freeze ? 1 : 0),
			anim.time,
			animLib,
			animName
		};
	}

	GOMPONENT_EXPORT void actor_clearAnimations(void* actor)
	{
		return static_cast<IActor*>(actor)->clearAnimations();
	}

	GOMPONENT_EXPORT void actor_setHealth(void* actor, float health)
	{
		return static_cast<IActor*>(actor)->setHealth(health);
	}

	GOMPONENT_EXPORT float actor_getHealth(void* actor)
	{
		return static_cast<IActor*>(actor)->getHealth();
	}

	GOMPONENT_EXPORT void actor_setInvulnerable(void* actor, unsigned char invuln)
	{
		return static_cast<IActor*>(actor)->setInvulnerable(invuln != 0);
	}

	GOMPONENT_EXPORT unsigned char actor_isInvulnerable(void* actor)
	{
		return static_cast<IActor*>(actor)->isInvulnerable() ? 1 : 0;
	}

	GOMPONENT_EXPORT unsigned char actor_isStreamedInForPlayer(void* actor, void* player)
	{
		return static_cast<IActor*>(actor)->isStreamedInForPlayer(*static_cast<IPlayer*>(player)) ? 1 : 0;
	}

	GOMPONENT_EXPORT ActorSpawnData actor_getSpawnData(void* actor)
	{
		return static_cast<IActor*>(actor)->getSpawnData();
	}

	GOMPONENT_EXPORT void actor_setPosition(void* actor, float posX, float posY, float posZ)
	{
		return static_cast<IActor*>(actor)->setPosition(Vector3(posX, posY, posZ));
	}

	GOMPONENT_EXPORT Vector3 actor_getPosition(void* actor)
	{
		return static_cast<IActor*>(actor)->getPosition();
	}

	GOMPONENT_EXPORT void actor_setVirtualWorld(void* actor, int vw)
	{
		return static_cast<IActor*>(actor)->setVirtualWorld(vw);
	}

	GOMPONENT_EXPORT int actor_getVirtualWorld(void* actor)
	{
		return static_cast<IActor*>(actor)->getVirtualWorld();
	}

	GOMPONENT_EXPORT void actor_setFacingAngle(void* actor, float angle)
	{
		return static_cast<IActor*>(actor)->setRotation(Vector3(0.0f, 0.0f, angle));
	}

	GOMPONENT_EXPORT float actor_getFacingAngle(void* actor)
	{
		return static_cast<IActor*>(actor)->getRotation().ToEuler().z;
	}

#ifdef __cplusplus
}
#endif
