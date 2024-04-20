/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

// Include the component's definition.
#include "Gomponent.hpp"
#include "Gamemode.hpp"
#include "ClassEvents.hpp"
#include "PlayerEvents.hpp"

Gamemode* Gomponent::getGamemode() {
	return gamemode_;
}

// Required component methods.
StringView Gomponent::componentName() const
{
	return "Gomponent";
}

SemanticVersion Gomponent::componentVersion() const
{
	return SemanticVersion(0, 0, 1, 0);
}

void Gomponent::onLoad(ICore* c)
{
	// Cache core, listen to player events.
	core_ = c;
	players = &core_->getPlayers();

	gamemode_ = new Gamemode("./gamemodes/test.dll");
	gamemode_->core = core_;
	gamemode_->config = &core_->getConfig();

	// Done.
	core_->printLn("Gomponent loaded.");
}

void Gomponent::onInit(IComponentList* components)
{
	core_->printLn("Gomponent is being initialized.");

	gamemode_->players = players;
	gamemode_->classes = components->queryComponent<IClassesComponent>();
	gamemode_->objects = components->queryComponent<IObjectsComponent>();
	gamemode_->pickups = components->queryComponent<IPickupsComponent>();
	gamemode_->textdraws = components->queryComponent<ITextDrawsComponent>();
	gamemode_->vehicles = components->queryComponent<IVehiclesComponent>();

	if (players)
	{
		players->getPlayerSpawnDispatcher().addEventHandler(PlayerEvents::Get());
		players->getPlayerConnectDispatcher().addEventHandler(PlayerEvents::Get());
		players->getPlayerTextDispatcher().addEventHandler(PlayerEvents::Get());
		players->getPlayerDamageDispatcher().addEventHandler(PlayerEvents::Get());
		players->getPlayerUpdateDispatcher().addEventHandler(PlayerEvents::Get());
	}

	if (gamemode_->classes)
	{
		gamemode_->classes->getEventDispatcher().addEventHandler(ClassEvents::Get());
	}

	gamemode_->init();
}

void Gomponent::onReady()
{
	core_->printLn("Gomponent is ready.");
}

void Gomponent::onFree(IComponent* component)
{
}

void Gomponent::free()
{
	// Deletes the component.
	delete this;
}

void Gomponent::reset()
{
	// Resets data when the mode changes.
}

// When this component is destroyed we need to tell any linked components this it is gone.
Gomponent::~Gomponent()
{
}
