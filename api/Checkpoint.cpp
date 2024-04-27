#include <sdk.hpp>
#include <iostream>
#include "Server/Components/Checkpoints/checkpoints.hpp"

#include "api.hpp"
#include "Gomponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	GOMPONENT_EXPORT void* checkpoint_setPosition(void* checkpoint, float posX, float posY, float posZ)
	{
		return static_cast<ICheckpointData*>(checkpoint)->setPosition(Vector3(posX, posY, posZ));
	}

	GOMPONENT_EXPORT Vector3 checkpoint_getPosition(void* checkpoint)
	{
		return static_cast<ICheckpointData*>(checkpoint)->getPosition();
	}

	GOMPONENT_EXPORT void checkpoint_setRadius(void* checkpoint, float radius)
	{
		return static_cast<ICheckpointData*>(checkpoint)->setRadius(radius);
	}

	GOMPONENT_EXPORT float checkpoint_getRadius(void* checkpoint)
	{
		return static_cast<ICheckpointData*>(checkpoint)->getRadius();
	}

	GOMPONENT_EXPORT unsigned char checkpoint_isPlayerInside(void* checkpoint)
	{
		return static_cast<ICheckpointData*>(checkpoint)->isPlayerInside() ? 1 : 0;
	}

	GOMPONENT_EXPORT void checkpoint_enable(void* checkpoint)
	{
		return static_cast<ICheckpointData*>(checkpoint)->enable();
	}

	GOMPONENT_EXPORT void checkpoint_disable(void* checkpoint)
	{
		return static_cast<ICheckpointData*>(checkpoint)->disable();
	}

	GOMPONENT_EXPORT unsigned char checkpoint_isEnabled(void* checkpoint)
	{
		return static_cast<ICheckpointData*>(checkpoint)->isEnabled();
	}

	// race checkpoint

	GOMPONENT_EXPORT void* raceCheckpoint_setPosition(void* checkpoint, float posX, float posY, float posZ)
	{
		return static_cast<IRaceCheckpointData*>(checkpoint)->setPosition(Vector3(posX, posY, posZ));
	}

	GOMPONENT_EXPORT Vector3 raceCheckpoint_getPosition(void* checkpoint)
	{
		return static_cast<IRaceCheckpointData*>(checkpoint)->getPosition();
	}

	GOMPONENT_EXPORT void raceCheckpoint_setRadius(void* checkpoint, float radius)
	{
		return static_cast<IRaceCheckpointData*>(checkpoint)->setRadius(radius);
	}

	GOMPONENT_EXPORT float raceCheckpoint_getRadius(void* checkpoint)
	{
		return static_cast<IRaceCheckpointData*>(checkpoint)->getRadius();
	}

	GOMPONENT_EXPORT unsigned char raceCheckpoint_isPlayerInside(void* checkpoint)
	{
		return static_cast<IRaceCheckpointData*>(checkpoint)->isPlayerInside() ? 1 : 0;
	}

	GOMPONENT_EXPORT void raceCheckpoint_enable(void* checkpoint)
	{
		return static_cast<IRaceCheckpointData*>(checkpoint)->enable();
	}

	GOMPONENT_EXPORT void raceCheckpoint_disable(void* checkpoint)
	{
		return static_cast<IRaceCheckpointData*>(checkpoint)->disable();
	}

	GOMPONENT_EXPORT unsigned char raceCheckpoint_isEnabled(void* checkpoint)
	{
		return static_cast<IRaceCheckpointData*>(checkpoint)->isEnabled();
	}

	GOMPONENT_EXPORT void raceCheckpoint_setType(void* checkpoint, int type)
	{
		return static_cast<IRaceCheckpointData*>(checkpoint)->setType(type);
	}

	GOMPONENT_EXPORT int raceCheckpoint_getType(void* checkpoint)
	{
		return static_cast<IRaceCheckpointData*>(checkpoint)->getType();
	}

	GOMPONENT_EXPORT void raceCheckpoint_setNextPosition(void* checkpoint, float posX, float posY, float posZ)
	{
		return static_cast<IRaceCheckpointData*>(checkpoint)->setNextPosition(Vector3(posX, posY, posZ));
	}

	GOMPONENT_EXPORT Vector3 raceCheckpoint_getNextPosition(void* checkpoint)
	{
		return static_cast<IRaceCheckpointData*>(checkpoint)->getNextPosition();
	}

#ifdef __cplusplus
}
#endif
