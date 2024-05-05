#include <sdk.hpp>

#include "Singleton.hpp"
#include "Gomponent.hpp"
#include "Gamemode.hpp"

class MenuEvents : public MenuEventHandler, public Singleton<MenuEvents>
{
public:
	MenuEvents()
	{
		gamemode_ = Gomponent::Get()->getGamemode();
	}

	void onPlayerSelectedMenuRow(IPlayer& player, MenuRow row) override
	{
		gamemode_->call<void>("onPlayerSelectedMenuRow", static_cast<void*>(&player), uint8_t(row));
	}
	
	void onPlayerExitedMenu(IPlayer& player) override
	{
		gamemode_->call<void>("onPlayerExitedMenu", static_cast<void*>(&player));
	}

private:
	Gamemode* gamemode_;
};
