#include <sdk.hpp>

#include "Singleton.hpp"
#include "Gomponent.hpp"
#include "Gamemode.hpp"

class ClassEvents : public ClassEventHandler, public Singleton<ClassEvents>
{
public:
	ClassEvents()
	{
		gamemode_ = Gomponent::Get()->getGamemode();
	}

	bool onPlayerRequestClass(IPlayer& player, unsigned int classId) override
	{
		IClassesComponent* classes = gamemode_->classes;
		IClass* class_ = NULL;

		if (classes)
		{
			class_ = classes->get(classId);
		}

		return gamemode_->call<unsigned char>("onPlayerRequestClass", static_cast<void*>(&player), static_cast<void*>(class_)) != 0;
	}

private:
	Gamemode* gamemode_;
};

