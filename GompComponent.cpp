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
#include "PlayerEvents.hpp"

Gamemode* GompComponent::getGamemode() {
	return gamemode_;
}

// Required component methods.
StringView GompComponent::componentName() const
{
	return "Go";
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

	// Done.
	core_->printLn("Go component loaded.");
}

void GompComponent::onInit(IComponentList* components)
{
	core_->printLn("Go component is being initialized.");

	gamemode_ = new Gamemode("./gamemodes/test.dll");
	gamemode_->init();

	if (players)
	{
		players->getPlayerConnectDispatcher().addEventHandler(PlayerEvents::Get());
	}
}

void GompComponent::onReady()
{
	core_->printLn("Go component is ready.");
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
