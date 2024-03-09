#include <sdk.hpp>
#include <iostream>


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define GOMP_EXPORT __declspec(dllexport)
#else
#define GOMP_EXPORT __attribute__((visibility("default")))
#endif


#ifdef __cplusplus
extern "C"
{
#endif

    GOMP_EXPORT int player_getID(void* player)
	{
		return reinterpret_cast<IPlayer*>(player)->getID();
	}

	GOMP_EXPORT EPlayerNameStatus player_setName(void* player, const char* name)
	{
		return reinterpret_cast<IPlayer*>(player)->setName(StringView(name));
	}

	GOMP_EXPORT const char* player_getName(void* player)
	{
		StringView name = reinterpret_cast<IPlayer*>(player)->getName();

		return name.data();
	}

	GOMP_EXPORT void player_sendClientMessage(void* player, int colour, const char* message)
    {
        reinterpret_cast<IPlayer*>(player)->sendClientMessage(Colour::FromRGBA(colour), message);
    }

#ifdef __cplusplus
}
#endif
