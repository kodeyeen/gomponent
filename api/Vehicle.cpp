// #include <Server/Components/Vehicles/vehicles.hpp>

#include "api.hpp"
#include "GompComponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	// Vehicle

	GOMP_EXPORT void* vehicle_create(int isStatic, int modelID, float x, float y, float z, float angle, int colour1, int colour2, int respawnDelay, int addSiren)
	{
		auto gamemode = GompComponent::Get()->getGamemode();
		IVehiclesComponent* vehicles = gamemode->vehicles;

		IVehicle* vehicle = vehicles->create(bool(isStatic), modelID, Vector3(x, y, z), angle, colour1, colour2, Seconds(respawnDelay), bool(addSiren));

		return static_cast<void*>(vehicle);
	}

	GOMP_EXPORT void vehicle_release(void* vehicle)
	{
		auto gamemode = GompComponent::Get()->getGamemode();
		IVehiclesComponent* vehicles = gamemode->vehicles;

		return vehicles->release(static_cast<IVehicle*>(vehicle)->getID());
	}

	GOMP_EXPORT int vehicle_isStreamedInForPlayer(void* vehicle, void* player)
	{
		return static_cast<IVehicle*>(vehicle)->isStreamedInForPlayer(*static_cast<IPlayer*>(player)) ? 1 : 0;
	}

	GOMP_EXPORT void vehicle_setColour(void* vehicle, int col1, int col2)
	{
		return static_cast<IVehicle*>(vehicle)->setColour(col1, col2);
	}

	GOMP_EXPORT VehicleColour vehicle_getColour(void* vehicle)
	{
		Pair<int, int> colours = static_cast<IVehicle*>(vehicle)->getColour();

		return { colours.first, colours.second };
	}

	GOMP_EXPORT void vehicle_setHealth(void* vehicle, float health)
	{
		return static_cast<IVehicle*>(vehicle)->setHealth(health);
	}

	GOMP_EXPORT float vehicle_getHealth(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->getHealth();
	}

	GOMP_EXPORT void* vehicle_getDriver(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->getDriver();
	}

	GOMP_EXPORT Array* vehicle_getPassengers(void* vehicle)
	{
		const FlatHashSet<IPlayer*>& passengers = static_cast<IVehicle*>(vehicle)->getPassengers();

		Array* arr = newArray();
		arr->length = passengers.size();
		arr->buf = new void*[arr->length];

		size_t count = 0;
		for (IPlayer* passenger : passengers)
		{
			if (count < arr->length)
			{
				arr->buf[count++] = static_cast<void*>(passenger);
			}
		}

		return arr;
	}

	GOMP_EXPORT void vehicle_setPlate(void* vehicle, String plate)
	{
		return static_cast<IVehicle*>(vehicle)->setPlate(StringView(plate.buf, plate.length));
	}

	GOMP_EXPORT String vehicle_getPlate(void* vehicle)
	{
		StringView plate = static_cast<IVehicle*>(vehicle)->getPlate();

		return { plate.data(), plate.length() };
	}

	GOMP_EXPORT void vehicle_setDamageStatus(void* vehicle, int PanelStatus, int DoorStatus, uint8_t LightStatus, uint8_t TyreStatus, void* vehicleUpdater)
	{
		return static_cast<IVehicle*>(vehicle)->setDamageStatus(PanelStatus, DoorStatus, LightStatus, TyreStatus, static_cast<IPlayer*>(vehicleUpdater));
	}

	GOMP_EXPORT void vehicle_getDamageStatus(void* vehicle, int* PanelStatus, int* DoorStatus, int* LightStatus, int* TyreStatus)
	{
		return static_cast<IVehicle*>(vehicle)->getDamageStatus(*PanelStatus, *DoorStatus, *LightStatus, *TyreStatus);
	}

	GOMP_EXPORT void vehicle_setPaintjob(void* vehicle, int paintjob)
	{
		return static_cast<IVehicle*>(vehicle)->setPaintJob(paintjob);
	}

	GOMP_EXPORT int vehicle_getPaintjob(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->getPaintJob();
	}

	GOMP_EXPORT void vehicle_addComponent(void* vehicle, int component)
	{
		return static_cast<IVehicle*>(vehicle)->addComponent(component);
	}

	GOMP_EXPORT int vehicle_getComponentInSlot(void* vehicle, int slot)
	{
		return static_cast<IVehicle*>(vehicle)->getComponentInSlot(slot);
	}

	GOMP_EXPORT void vehicle_removeComponent(void* vehicle, int component)
	{
		return static_cast<IVehicle*>(vehicle)->removeComponent(component);
	}

	GOMP_EXPORT void vehicle_putPlayer(void* vehicle, void* player, int seatID)
	{
		return static_cast<IVehicle*>(vehicle)->putPlayer(*static_cast<IPlayer*>(player), seatID);
	}

	GOMP_EXPORT void vehicle_setZAngle(void* vehicle, float angle)
	{
		return static_cast<IVehicle*>(vehicle)->setZAngle(angle);
	}

	GOMP_EXPORT float vehicle_getZAngle(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->getZAngle();
	}

	GOMP_EXPORT void vehicle_setParams(void* vehicle, VehicleParams* params)
	{
		return static_cast<IVehicle*>(vehicle)->setParams(*params);
	}

	GOMP_EXPORT void vehicle_setParamsForPlayer(void* vehicle, void* player, VehicleParams* params)
	{
		return static_cast<IVehicle*>(vehicle)->setParamsForPlayer(*static_cast<IPlayer*>(player), *params);
	}

	GOMP_EXPORT VehicleParams vehicle_getParams(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->getParams();
	}

	GOMP_EXPORT int vehicle_isDead(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->isDead() ? 1 : 0;
	}

	GOMP_EXPORT void vehicle_respawn(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->respawn();
	}

	GOMP_EXPORT void vehicle_setRespawnDelay(void* vehicle, int delay)
	{
		return static_cast<IVehicle*>(vehicle)->setRespawnDelay(Seconds(delay));
	}

	GOMP_EXPORT long long vehicle_getRespawnDelay(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->getRespawnDelay().count();
	}

	GOMP_EXPORT int vehicle_isRespawning(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->isRespawning() ? 1 : 0;
	}

	GOMP_EXPORT void vehicle_setInterior(void* vehicle, int interiorID)
	{
		return static_cast<IVehicle*>(vehicle)->setInterior(interiorID);
	}

	GOMP_EXPORT int vehicle_getInterior(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->getInterior();
	}

	GOMP_EXPORT void vehicle_attachTrailer(void* vehicle, void* trailer)
	{
		return static_cast<IVehicle*>(vehicle)->attachTrailer(*static_cast<IVehicle*>(trailer));
	}

	GOMP_EXPORT void vehicle_detachTrailer(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->detachTrailer();
	}

	GOMP_EXPORT int vehicle_isTrailer(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->isTrailer() ? 1 : 0;
	}

	GOMP_EXPORT void* vehicle_getTrailer(void* vehicle)
	{
		IVehicle* trailer = static_cast<IVehicle*>(vehicle)->getTrailer();

		if (trailer)
		{
			return trailer;
		}

		return NULL;
	}

	GOMP_EXPORT void* vehicle_getCab(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->getCab();
	}

	GOMP_EXPORT void vehicle_repair(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->repair();
	}

	GOMP_EXPORT void vehicle_setVelocity(void* vehicle, float x, float y, float z)
	{
		return static_cast<IVehicle*>(vehicle)->setVelocity(Vector3(x, y, z));
	}

	GOMP_EXPORT Vector3 vehicle_getVelocity(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->getVelocity();
	}

	GOMP_EXPORT void vehicle_setAngularVelocity(void* vehicle, float x, float y, float z)
	{
		return static_cast<IVehicle*>(vehicle)->setAngularVelocity(Vector3(x, y, z));
	}

	GOMP_EXPORT Vector3 vehicle_getAngularVelocity(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->getAngularVelocity();
	}

	GOMP_EXPORT int vehicle_getModel(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->getModel();
	}

	GOMP_EXPORT uint8_t vehicle_getLandingGearState(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->getLandingGearState();
	}

	GOMP_EXPORT int vehicle_hasBeenOccupied(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->hasBeenOccupied() ? 1 : 0;
	}

	long vehicle_getLastOccupiedTime(void* vehicle)
	{
		TimePoint spawnTime = static_cast<IVehicle*>(vehicle)->getLastOccupiedTime();
		auto spawnTimeMs = std::chrono::time_point_cast<std::chrono::milliseconds>(spawnTime);
		auto value = spawnTimeMs.time_since_epoch();
		long duration = value.count();

		return duration;
	}

	long vehicle_getLastSpawnTime(void* vehicle)
	{
		TimePoint spawnTime = static_cast<IVehicle*>(vehicle)->getLastSpawnTime();
		auto spawnTimeMs = std::chrono::time_point_cast<std::chrono::milliseconds>(spawnTime);
		auto value = spawnTimeMs.time_since_epoch();
		long duration = value.count();

		return duration;
	}

	GOMP_EXPORT int vehicle_isOccupied(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->isOccupied() ? 1 : 0;
	}

	GOMP_EXPORT void vehicle_setSiren(void* vehicle, int status)
	{
		return static_cast<IVehicle*>(vehicle)->setSiren(status != 0);
	}

	GOMP_EXPORT uint8_t vehicle_getSirenState(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->getSirenState();
	}

	GOMP_EXPORT uint32_t vehicle_getHydraThrustAngle(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->getHydraThrustAngle();
	}

	GOMP_EXPORT float vehicle_getTrainSpeed(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->getTrainSpeed();
	}

	GOMP_EXPORT int vehicle_getLastDriverPoolID(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->getLastDriverPoolID();
	}

	// entity

	GOMP_EXPORT Vector3 vehicle_getPosition(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->getPosition();
	}

	GOMP_EXPORT void vehicle_setPosition(void* vehicle, float x, float y, float z)
	{
		return static_cast<IVehicle*>(vehicle)->setPosition(Vector3(x, y, z));
	}

	GOMP_EXPORT Vector4 vehicle_getRotation(void* vehicle)
	{
		glm::quat rotQuat = static_cast<IVehicle*>(vehicle)->getRotation().q;

		return Vector4(rotQuat.x, rotQuat.y, rotQuat.z, rotQuat.w);
	}

	GOMP_EXPORT void vehicle_setVirtualWorld(void* vehicle, int vw)
	{
		return static_cast<IVehicle*>(vehicle)->setVirtualWorld(vw);
	}

	GOMP_EXPORT int vehicle_getVirtualWorld(void* vehicle)
	{
		return static_cast<IVehicle*>(vehicle)->getVirtualWorld();
	}

	// misc

	GOMP_EXPORT float vehicle_getDistanceFromPoint(void* vehicle, float pX, float pY, float pZ)
	{
		Vector3 vehicleCoords = static_cast<IVehicle*>(vehicle)->getPosition();
		return glm::distance(vehicleCoords, Vector3(pX, pY, pZ));
	}

	GOMP_EXPORT int vehicle_isInRangeOfPoint(void* vehicle, float range, float pX, float pY, float pZ)
	{
		return range >= glm::distance(static_cast<IVehicle*>(vehicle)->getPosition(), Vector3(pX, pY, pZ)) ? 1 : 0;
	}

#ifdef __cplusplus
}
#endif
