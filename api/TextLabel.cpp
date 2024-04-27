#include <sdk.hpp>
#include "Server/Components/TextLabels/textlabels.hpp"

#include "api.hpp"
#include "Gomponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	GOMPONENT_EXPORT void* textLabel_create(String text, uint32_t colour, float posX, float posY, float posZ, float drawDist, int vw, unsigned char los)
	{
		auto gamemode = Gomponent::Get()->getGamemode();
		ITextLabelsComponent* textlabels = gamemode->textlabels;

		if (textlabels)
		{
			ITextLabel* textlabel = textlabels->create(StringView(text.buf, text.length), Colour::FromRGBA(colour), Vector3(posX, posY, posZ), drawDist, vw, los != 0);

			return static_cast<void*>(textlabel);
		}

		return NULL;
	}

	GOMPONENT_EXPORT void textLabel_release(void* textLabel)
	{
		auto gamemode = Gomponent::Get()->getGamemode();
		ITextLabelsComponent* textlabels = gamemode->textlabels;

		if (textlabels)
		{
			textlabels->release(static_cast<ITextLabel*>(textLabel)->getID());
		}
	}

	GOMPONENT_EXPORT void textLabel_setText(void* textLabel, String text)
	{
		return static_cast<ITextLabel*>(textLabel)->setText(StringView(text.buf, text.length));
	}

	GOMPONENT_EXPORT String textLabel_getText(void* textLabel)
	{
		StringView textView = static_cast<ITextLabel*>(textLabel)->getText();

		return { textView.data(), textView.length() };
	}

	GOMPONENT_EXPORT void textLabel_setColour(void* textLabel, uint32_t colour)
	{
		return static_cast<ITextLabel*>(textLabel)->setColour(Colour::FromRGBA(colour));
	}

	GOMPONENT_EXPORT uint32_t textLabel_getColour(void* textLabel)
	{
		return static_cast<ITextLabel*>(textLabel)->getColour().RGBA();
	}

	GOMPONENT_EXPORT void textLabel_setDrawDistance(void* textLabel, float drawDist)
	{
		return static_cast<ITextLabel*>(textLabel)->setDrawDistance(drawDist);
	}

	GOMPONENT_EXPORT float textLabel_getDrawDistance(void* textLabel)
	{
		return static_cast<ITextLabel*>(textLabel)->getDrawDistance();
	}

	GOMPONENT_EXPORT void textLabel_attachToPlayer(void* textLabel, void* player, float offsetX, float offsetY, float offsetZ)
	{
		return static_cast<ITextLabel*>(textLabel)->attachToPlayer(*static_cast<IPlayer*>(player), Vector3(offsetX, offsetY, offsetZ));
	}

	GOMPONENT_EXPORT void textLabel_attachToVehicle(void* textLabel, void* vehicle, float offsetX, float offsetY, float offsetZ)
	{
		return static_cast<ITextLabel*>(textLabel)->attachToVehicle(*static_cast<IVehicle*>(vehicle), Vector3(offsetX, offsetY, offsetZ));
	}

	GOMPONENT_EXPORT TextLabelAttachmentData textLabel_getAttachmentData(void* textLabel)
	{
		return static_cast<ITextLabel*>(textLabel)->getAttachmentData();
	}

	GOMPONENT_EXPORT void textLabel_detachFromPlayer(void* textLabel, void* player, float posX, float posY, float posZ)
	{
		return static_cast<ITextLabel*>(textLabel)->detachFromPlayer(*static_cast<IPlayer*>(player), Vector3(posX, posY, posZ));
	}

	GOMPONENT_EXPORT void textLabel_detachFromVehicle(void* textLabel, void* vehicle, float posX, float posY, float posZ)
	{
		return static_cast<ITextLabel*>(textLabel)->attachToVehicle(*static_cast<IVehicle*>(vehicle), Vector3(posX, posY, posZ));
	}

	GOMPONENT_EXPORT void textLabel_setTestLOS(void* textLabel, unsigned char status)
	{
		return static_cast<ITextLabel*>(textLabel)->setTestLOS(status != 0);
	}

	GOMPONENT_EXPORT unsigned char textLabel_getTestLOS(void* textLabel)
	{
		return static_cast<ITextLabel*>(textLabel)->getTestLOS() ? 1 : 0;
	}

	GOMPONENT_EXPORT unsigned char textLabel_isStreamedInForPlayer(void* textLabel, void* player)
	{
		return static_cast<ITextLabel*>(textLabel)->isStreamedInForPlayer() ? 1 : 0;
	}

	// entity

	GOMPONENT_EXPORT void textLabel_setPosition(void* textLabel, float posX, float posY, float posZ)
	{
		return static_cast<ITextLabel*>(textLabel)->setPosition(Vector3(posX, posY, posZ));
	}

	GOMPONENT_EXPORT Vector3 textLabel_getPosition(void* textLabel)
	{
		return static_cast<ITextLabel*>(textLabel)->getPosition();
	}

	GOMPONENT_EXPORT void textLabel_setVirtualWorld(void* textLabel, int vw)
	{
		return static_cast<ITextLabel*>(textLabel)->setVirtualWorld(vw);
	}

	GOMPONENT_EXPORT int textLabel_getVirtualWorld(void* textLabel)
	{
		return static_cast<ITextLabel*>(textLabel)->getVirtualWorld();
	}

#ifdef __cplusplus
}
#endif
