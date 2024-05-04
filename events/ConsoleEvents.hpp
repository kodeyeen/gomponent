#include <sdk.hpp>
#include <Server/Components/Console/console.hpp>

#include <api/api.hpp>
#include "Singleton.hpp"
#include "Gomponent.hpp"
#include "Gamemode.hpp"

class ConsoleEvents : public ConsoleEventHandler, public Singleton<ConsoleEvents>
{
public:
	ConsoleEvents()
	{
		gamemode_ = Gomponent::Get()->getGamemode();
	}

	bool onConsoleText(StringView command, StringView parameters, const ConsoleCommandSenderData& sender) override
	{
		String commandStr = { command.data(), command.length() };
		String parametersStr = { parameters.data(), parameters.length() };

		return gamemode_->call<unsigned char>("onConsoleText", commandStr, parametersStr) != 0;
	}

	void onRconLoginAttempt(IPlayer& player, StringView password, bool success) override
	{
		String passwordStr = { password.data(), password.length() };

		gamemode_->call<unsigned char>("onRconLoginAttempt", static_cast<void*>(&player), passwordStr, (unsigned char)(success ? 1 : 0));
	}

	// void onConsoleCommandListRequest(FlatHashSet<StringView>& commands) { }

private:
	Gamemode* gamemode_;
};
