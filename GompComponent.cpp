/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

// Include the component's definition.
#include "GompComponent.hpp"
#include "Gamemode.hpp"
#include "ClassEvents.hpp"
#include "PlayerEvents.hpp"

Gamemode* GompComponent::getGamemode() {
	return gamemode_;
}

// Required component methods.
StringView GompComponent::componentName() const
{
	return "Gomp";
}

SemanticVersion GompComponent::componentVersion() const
{
	return SemanticVersion(0, 0, 1, 0);
}

void GompComponent::onLoad(ICore* c)
{
	// Cache core, listen to player events.
	core_ = c;
	players = &core_->getPlayers();

	gamemode_ = new Gamemode("./gamemodes/test.dll");
	gamemode_->core = core_;
	gamemode_->config = &core_->getConfig();

	// Done.
	core_->printLn("Gomp component loaded.");
}

void GompComponent::onInit(IComponentList* components)
{
	core_->printLn("Gomp component is being initialized.");

	gamemode_->players = players;
	gamemode_->classes = components->queryComponent<IClassesComponent>();
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

void GompComponent::onReady()
{
	core_->printLn("Gomp component is ready.");
}

void GompComponent::onFree(IComponent* component)
{
}

void GompComponent::free()
{
	// Deletes the component.
	delete this;
}

void GompComponent::reset()
{
	// Resets data when the mode changes.
}

// When this component is destroyed we need to tell any linked components this it is gone.
GompComponent::~GompComponent()
{
}
