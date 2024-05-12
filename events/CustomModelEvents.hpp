#include <sdk.hpp>

#include "Singleton.hpp"
#include "Gomponent.hpp"
#include "Gamemode.hpp"

class CustomModelEvents : public PlayerModelsEventHandler, public Singleton<CustomModelEvents>
{
public:
	CustomModelEvents()
	{
		gamemode_ = Gamemode::Get();
	}

	void onPlayerFinishedDownloading(IPlayer& player) override
	{
		gamemode_->call<void>("onPlayerFinishedDownloading", static_cast<void*>(&player));
	}

	bool onPlayerRequestDownload(IPlayer& player, ModelDownloadType type, uint32_t checksum) override
	{
		return gamemode_->call<unsigned char>("onPlayerRequestDownload", uint8_t(type), checksum) != 0;
	}

private:
	Gamemode* gamemode_;
};
