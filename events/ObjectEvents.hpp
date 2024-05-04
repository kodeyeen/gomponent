#include <sdk.hpp>

#include <api/api.hpp>
#include "Singleton.hpp"
#include "Gomponent.hpp"
#include "Gamemode.hpp"

class ObjectEvents : public ObjectEventHandler, public Singleton<ObjectEvents>
{
public:
	ObjectEvents()
	{
		gamemode_ = Gomponent::Get()->getGamemode();
	}

	void onMoved(IObject& object) override
	{
		gamemode_->call<unsigned char>("onObjectMoved", static_cast<void*>(&object));
	}

	void onPlayerObjectMoved(IPlayer& player, IPlayerObject& object) override
	{
		gamemode_->call<unsigned char>("onPlayerObjectMoved", static_cast<void*>(&player), static_cast<void*>(&object));
	}

	void onObjectSelected(IPlayer& player, IObject& object, int model, Vector3 position) override
	{
		gamemode_->call<unsigned char>("onObjectSelected", static_cast<void*>(&player), static_cast<void*>(&object), model, position);
	}

	void onPlayerObjectSelected(IPlayer& player, IPlayerObject& object, int model, Vector3 position) override
	{
		gamemode_->call<unsigned char>("onPlayerObjectSelected", static_cast<void*>(&player), static_cast<void*>(&object), model, position);
	}

	void onObjectEdited(IPlayer& player, IObject& object, ObjectEditResponse response, Vector3 offset, Vector3 rotation) override
	{
		gamemode_->call<unsigned char>("onObjectEdited", static_cast<void*>(&player), static_cast<void*>(&object), int(response), offset, rotation);
	}

	void onPlayerObjectEdited(IPlayer& player, IPlayerObject& object, ObjectEditResponse response, Vector3 offset, Vector3 rotation) override
	{
		gamemode_->call<unsigned char>("onPlayerObjectEdited", static_cast<void*>(&player), static_cast<void*>(&object), int(response), offset, rotation);
	}

	void onPlayerAttachedObjectEdited(IPlayer& player, int index, bool saved, const ObjectAttachmentSlotData& data) override
	{
		PlayerAttachedObject obj;
		obj.model = data.model;
		obj.bone = data.bone;
		obj.offset = data.offset;
		obj.rotation = data.rotation;
		obj.scale = data.scale;
		obj.colour1 = data.colour1.ARGB();
		obj.colour2 = data.colour2.ARGB();

		gamemode_->call<unsigned char>("onPlayerAttachedObjectEdited", static_cast<void*>(&player), index, (unsigned char)(saved ? 1 : 0), obj);
	}

private:
	Gamemode* gamemode_;
};
