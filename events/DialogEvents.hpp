#include <sdk.hpp>
#include <Server/Components/Dialogs/dialogs.hpp>

#include "Singleton.hpp"
#include "Gomponent.hpp"
#include "Gamemode.hpp"

class DialogEvents : public PlayerDialogEventHandler, public Singleton<DialogEvents>
{
public:
	DialogEvents()
	{
		gamemode_ = Gamemode::Get();
	}

	void onDialogResponse(IPlayer& player, int dialogId, DialogResponse response, int listItem, StringView inputText) override
	{
		String inputTextStr = { inputText.data(), inputText.length() };

		gamemode_->call<void>("onDialogResponse", static_cast<void*>(&player), dialogId, int(response), listItem, inputTextStr);
	}

private:
	Gamemode* gamemode_;
};
