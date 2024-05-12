#pragma once

/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

// Required for most of open.mp.
#include <sdk.hpp>
#include <Server/Components/Actors/actors.hpp>
#include <Server/Components/Checkpoints/checkpoints.hpp>
#include <Server/Components/Console/console.hpp>
#include <Server/Components/Classes/classes.hpp>
#include <Server/Components/Dialogs/dialogs.hpp>
#include <Server/Components/GangZones/gangzones.hpp>
#include <Server/Components/Menus/menus.hpp>
#include <Server/Components/Objects/objects.hpp>
#include <Server/Components/Pickups/pickups.hpp>
#include <Server/Components/TextDraws/textdraws.hpp>
#include <Server/Components/TextLabels/textlabels.hpp>
#include <Server/Components/Vehicles/vehicles.hpp>
#include <Server/Components/Vehicles/vehicle_models.hpp>
#include <Server/Components/CustomModels/custommodels.hpp>

// This is the private implementation of the public interface.  We must know the interface.
#include "Singleton.hpp"
#include "interface.hpp"
#include "Gamemode.hpp"

// `final` so we don't need virtual destructors.  Also because we know it isn't inherited.
class Gomponent final
	// This class is an implementation of the publicly shared `IWeatherComponent` interface.
	: public IGomponent
	, public Singleton<Gomponent>
{
private:
	Gamemode* gamemode_ = nullptr;
public:
	ICore* core = nullptr;
	IConfig* config = nullptr;
	IPlayerPool* players = nullptr;
	IActorsComponent* actors = nullptr;
	IConsoleComponent* console = nullptr;
	ICheckpointsComponent* checkpoints = nullptr;
	IClassesComponent* classes = nullptr;
	IDialogsComponent* dialogs = nullptr;
	IGangZonesComponent* gangzones = nullptr;
	IMenusComponent* menus = nullptr;
	IObjectsComponent* objects = nullptr;
	IPickupsComponent* pickups = nullptr;
	ITextDrawsComponent* textdraws = nullptr;
	ITextLabelsComponent* textlabels = nullptr;
	IVehiclesComponent* vehicles = nullptr;
	ICustomModelsComponent* models = nullptr;

	// Required component methods.
	StringView componentName() const override;

	SemanticVersion componentVersion() const override;

	void onLoad(ICore* c) override;

	void onInit(IComponentList* components) override;

	void onReady() override;

	void onFree(IComponent* component) override;

	void free() override;

	void reset() override;

	// When this component is destroyed we need to tell any linked components this it is gone.
	~Gomponent();
};
