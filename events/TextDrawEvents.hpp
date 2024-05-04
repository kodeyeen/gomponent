#include <sdk.hpp>

#include "Singleton.hpp"
#include "Gomponent.hpp"
#include "Gamemode.hpp"

class TextDrawEvents : public TextDrawEventHandler, public Singleton<TextDrawEvents>
{
public:
	TextDrawEvents()
	{
		gamemode_ = Gomponent::Get()->getGamemode();
	}

	void onPlayerClickTextDraw(IPlayer& player, ITextDraw& td) override
	{
		gamemode_->call<unsigned char>("onPlayerClickTextDraw", static_cast<void*>(&player), static_cast<void*>(&td));
	}

	void onPlayerClickPlayerTextDraw(IPlayer& player, IPlayerTextDraw& td) override
	{
		gamemode_->call<unsigned char>("onPlayerClickPlayerTextDraw", static_cast<void*>(&player), static_cast<void*>(&td));
	}

	bool onPlayerCancelTextDrawSelection(IPlayer& player) override
	{
		return gamemode_->call<unsigned char>("onPlayerCancelTextDrawSelection", static_cast<void*>(&player)) != 0;
	}

	bool onPlayerCancelPlayerTextDrawSelection(IPlayer& player) override
	{
		return gamemode_->call<unsigned char>("onPlayerCancelPlayerTextDrawSelection", static_cast<void*>(&player)) != 0;
	}

private:
	Gamemode* gamemode_;
};
