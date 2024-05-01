#include <sdk.hpp>
#include "Server/Components/TextDraws/textdraws.hpp"

#include "api.hpp"
#include "Gomponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	GOMPONENT_EXPORT void* textDraw_create(float posX, float posY, String text)
	{
		ITextDrawsComponent* textdraws = Gomponent::Get()->textdraws;

		if (textdraws)
		{
			ITextDraw* textdraw = textdraws->create(Vector2(posX, posY), StringView(text.buf, text.length));

			if (textdraw)
			{
				return static_cast<void*>(textdraw);
			}
		}

		return NULL;
	}

	GOMPONENT_EXPORT void textDraw_release(void* textdraw)
	{
		ITextDrawsComponent* textdraws = Gomponent::Get()->textdraws;

		if (textdraws)
		{
			textdraws->release(static_cast<ITextDraw*>(textdraw)->getID());
		}
	}

	GOMPONENT_EXPORT void textDraw_setPosition(void* textdraw, float posX, float posY)
	{
		static_cast<ITextDraw*>(textdraw)->setPosition(Vector2(posX, posY));
	}

	GOMPONENT_EXPORT Vector2 textDraw_getPosition(void* textdraw)
	{
		return static_cast<ITextDraw*>(textdraw)->getPosition();
	}

	GOMPONENT_EXPORT void textDraw_setText(void* textdraw, String text)
	{
		static_cast<ITextDraw*>(textdraw)->setText(StringView(text.buf, text.length));
	}

	GOMPONENT_EXPORT String textDraw_getText(void* textdraw)
	{
		StringView textView = static_cast<ITextDraw*>(textdraw)->getText();

		return { textView.data(), textView.length() };
	}

	GOMPONENT_EXPORT void textDraw_setLetterSize(void* textdraw, float sizeX, float sizeY)
	{
		static_cast<ITextDraw*>(textdraw)->setLetterSize(Vector2(sizeX, sizeY));
	}

	GOMPONENT_EXPORT Vector2 textDraw_getLetterSize(void* textdraw)
	{
		return static_cast<ITextDraw*>(textdraw)->getLetterSize();
	}

	GOMPONENT_EXPORT void textDraw_setTextSize(void* textdraw, float sizeX, float sizeY)
	{
		static_cast<ITextDraw*>(textdraw)->setTextSize(Vector2(sizeX, sizeY));
	}

	GOMPONENT_EXPORT Vector2 textDraw_getTextSize(void* textdraw)
	{
		return static_cast<ITextDraw*>(textdraw)->getTextSize();
	}

	GOMPONENT_EXPORT void textDraw_setAlignment(void* textdraw, int alignment)
	{
		static_cast<ITextDraw*>(textdraw)->setAlignment(TextDrawAlignmentTypes(alignment));
	}

	GOMPONENT_EXPORT int textDraw_getAlignment(void* textdraw)
	{
		TextDrawAlignmentTypes alignment = static_cast<ITextDraw*>(textdraw)->getAlignment();
		return static_cast<int>(alignment);
	}

	GOMPONENT_EXPORT void textDraw_setColour(void* textdraw, uint32_t colour)
	{
		static_cast<ITextDraw*>(textdraw)->setColour(Colour::FromRGBA(colour));
	}

	GOMPONENT_EXPORT int textDraw_getLetterColour(void* textdraw)
	{
		return static_cast<ITextDraw*>(textdraw)->getLetterColour().RGBA();
	}	

	GOMPONENT_EXPORT void textDraw_useBox(void* textdraw, int use)
	{
		static_cast<ITextDraw*>(textdraw)->useBox(use != 0);
	}

	GOMPONENT_EXPORT int textDraw_hasBox(void* textdraw)
	{
		return static_cast<ITextDraw*>(textdraw)->hasBox() ? 1 : 0;
	}

	GOMPONENT_EXPORT void textDraw_setBoxColour(void* textdraw, uint32_t colour)
	{
		static_cast<ITextDraw*>(textdraw)->setBoxColour(Colour::FromRGBA(colour));
	}

	GOMPONENT_EXPORT int textDraw_getBoxColour(void* textdraw)
	{
		return static_cast<ITextDraw*>(textdraw)->getBoxColour().RGBA();
	}

	GOMPONENT_EXPORT void textDraw_setShadow(void* textdraw, int size)
	{
		static_cast<ITextDraw*>(textdraw)->setShadow(size);
	}

	GOMPONENT_EXPORT int textDraw_getShadow(void* textdraw)
	{
		return static_cast<ITextDraw*>(textdraw)->getShadow();
	}

	GOMPONENT_EXPORT void textDraw_setOutline(void* textdraw, int size)
	{
		static_cast<ITextDraw*>(textdraw)->setOutline(size);
	}

	GOMPONENT_EXPORT int textDraw_getOutline(void* textdraw)
	{
		return static_cast<ITextDraw*>(textdraw)->getOutline();
	}

	GOMPONENT_EXPORT void textDraw_setBackgroundColour(void* textdraw, uint32_t colour)
	{
		static_cast<ITextDraw*>(textdraw)->setBackgroundColour(Colour::FromRGBA(colour));
	}

	GOMPONENT_EXPORT int textDraw_getBackgroundColour(void* textdraw)
	{
		return static_cast<ITextDraw*>(textdraw)->getBackgroundColour().RGBA();
	}

	GOMPONENT_EXPORT void textDraw_setStyle(void* textdraw, int style)
	{
		static_cast<ITextDraw*>(textdraw)->setStyle(TextDrawStyle(style));
	}

	GOMPONENT_EXPORT int textDraw_getStyle(void* textdraw)
	{
		TextDrawStyle style = static_cast<ITextDraw*>(textdraw)->getStyle();
		return static_cast<int>(style);
	}

	GOMPONENT_EXPORT void textDraw_setProportional(void* textdraw, int set)
	{
		static_cast<ITextDraw*>(textdraw)->setProportional(set != 0);
	}

	GOMPONENT_EXPORT int textDraw_isProportional(void* textdraw)
	{
		return static_cast<ITextDraw*>(textdraw)->isProportional() ? 1 : 0;
	}

	GOMPONENT_EXPORT void textDraw_setSelectable(void* textdraw, int set)
	{
		static_cast<ITextDraw*>(textdraw)->setSelectable(set != 0);
	}

	GOMPONENT_EXPORT int textDraw_isSelectable(void* textdraw)
	{
		return static_cast<ITextDraw*>(textdraw)->isSelectable() ? 1 : 0;
	}

	GOMPONENT_EXPORT void textDraw_setPreviewModel(void* textdraw, int model)
	{
		static_cast<ITextDraw*>(textdraw)->setPreviewModel(model);
	}

	GOMPONENT_EXPORT int textDraw_getPreviewModel(void* textdraw)
	{
		return static_cast<ITextDraw*>(textdraw)->getPreviewModel();
	}

	GOMPONENT_EXPORT void textDraw_setPreviewRotation(void* textdraw, float rotX, float rotY, float rotZ)
	{
		static_cast<ITextDraw*>(textdraw)->setPreviewRotation(Vector3(rotX, rotY, rotZ));
	}

	GOMPONENT_EXPORT Vector3 textDraw_getPreviewRotation(void* textdraw)
	{
		return static_cast<ITextDraw*>(textdraw)->getPreviewRotation();
	}

	GOMPONENT_EXPORT void textDraw_setPreviewVehicleColour(void* textdraw, int col1, int col2)
	{
		static_cast<ITextDraw*>(textdraw)->setPreviewVehicleColour(col1, col2);
	}

	GOMPONENT_EXPORT VehicleColour textDraw_getPreviewVehicleColour(void* textdraw)
	{
		Pair<int, int> colours = static_cast<ITextDraw*>(textdraw)->getPreviewVehicleColour();

		return { colours.first, colours.second };
	}

	GOMPONENT_EXPORT void textDraw_setPreviewZoom(void* textdraw, float zoom)
	{
		static_cast<ITextDraw*>(textdraw)->setPreviewZoom(zoom);
	}

	GOMPONENT_EXPORT float textDraw_getPreviewZoom(void* textdraw)
	{
		return static_cast<ITextDraw*>(textdraw)->getPreviewZoom();
	}

	GOMPONENT_EXPORT void textDraw_showForPlayer(void* textdraw, void* player)
	{
		static_cast<ITextDraw*>(textdraw)->showForPlayer(*static_cast<IPlayer*>(player));
	}

	GOMPONENT_EXPORT void textDraw_hideForPlayer(void* textdraw, void* player)
	{
		static_cast<ITextDraw*>(textdraw)->hideForPlayer(*static_cast<IPlayer*>(player));
	}

	GOMPONENT_EXPORT int textDraw_isShownForPlayer(void* textdraw, void* player)
	{
		return static_cast<ITextDraw*>(textdraw)->isShownForPlayer(*static_cast<IPlayer*>(player)) ? 1 : 0;
	}

	GOMPONENT_EXPORT void textDraw_setTextForPlayer(void* textdraw, void* player, String text)
	{
		return static_cast<ITextDraw*>(textdraw)->setTextForPlayer(*static_cast<IPlayer*>(player), StringView(text.buf, text.length));
	}

	// PlayerTextDraw

	GOMPONENT_EXPORT void* playerTextDraw_create(void* player, float posX, float posY, String text)
	{
		IPlayerTextDrawData* playerTextDraws = queryExtension<IPlayerTextDrawData>(static_cast<IPlayer*>(player));
		if (playerTextDraws)
		{
			IPlayerTextDraw* textdraw = playerTextDraws->create(Vector2(posX, posY), StringView(text.buf, text.length));
			if (textdraw)
			{
				return textdraw;
			}
		}
		return NULL;
	}

	GOMPONENT_EXPORT void playerTextDraw_release(void* textdraw, void* player)
	{
		IPlayerTextDrawData* playerTextDraws = queryExtension<IPlayerTextDrawData>(static_cast<IPlayer*>(player));
		if (playerTextDraws)
		{
			playerTextDraws->release(static_cast<IPlayerTextDraw*>(textdraw)->getID());
		}
	}

	GOMPONENT_EXPORT void playerTextDraw_setPosition(void* textdraw, float posX, float posY)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->setPosition(Vector2(posX, posY));
	}

	GOMPONENT_EXPORT Vector2 playerTextDraw_getPosition(void* textdraw)
	{
		return static_cast<IPlayerTextDraw*>(textdraw)->getPosition();
	}

	GOMPONENT_EXPORT void playerTextDraw_setText(void* textdraw, String text)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->setText(StringView(text.buf, text.length));
	}

	GOMPONENT_EXPORT String playerTextDraw_getText(void* textdraw)
	{
		StringView textView = static_cast<IPlayerTextDraw*>(textdraw)->getText();

		return { textView.data(), textView.length() };
	}

	GOMPONENT_EXPORT void playerTextDraw_setLetterSize(void* textdraw, float sizeX, float sizeY)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->setLetterSize(Vector2(sizeX, sizeY));
	}

	GOMPONENT_EXPORT Vector2 playerTextDraw_getLetterSize(void* textdraw)
	{
		return static_cast<IPlayerTextDraw*>(textdraw)->getLetterSize();
	}

	GOMPONENT_EXPORT void playerTextDraw_setTextSize(void* textdraw, float sizeX, float sizeY)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->setTextSize(Vector2(sizeX, sizeY));
	}

	GOMPONENT_EXPORT Vector2 playerTextDraw_getTextSize(void* textdraw)
	{
		return static_cast<IPlayerTextDraw*>(textdraw)->getTextSize();
	}

	GOMPONENT_EXPORT void playerTextDraw_setAlignment(void* textdraw, int alignment)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->setAlignment(TextDrawAlignmentTypes(alignment));
	}

	GOMPONENT_EXPORT int playerTextDraw_getAlignment(void* textdraw)
	{
		TextDrawAlignmentTypes alignment = static_cast<IPlayerTextDraw*>(textdraw)->getAlignment();
		return static_cast<int>(alignment);
	}

	GOMPONENT_EXPORT void playerTextDraw_setColour(void* textdraw, uint32_t colour)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->setColour(Colour::FromRGBA(colour));
	}

	GOMPONENT_EXPORT int playerTextDraw_getLetterColour(void* textdraw)
	{
		return static_cast<IPlayerTextDraw*>(textdraw)->getLetterColour().RGBA();
	}

	GOMPONENT_EXPORT void playerTextDraw_useBox(void* textdraw, int use)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->useBox(use != 0);
	}

	GOMPONENT_EXPORT int playerTextDraw_hasBox(void* textdraw)
	{
		return static_cast<IPlayerTextDraw*>(textdraw)->hasBox() ? 1 : 0;
	}

	GOMPONENT_EXPORT void playerTextDraw_setBoxColour(void* textdraw, uint32_t colour)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->setBoxColour(Colour::FromRGBA(colour));
	}

	GOMPONENT_EXPORT int playerTextDraw_getBoxColour(void* textdraw)
	{
		return static_cast<IPlayerTextDraw*>(textdraw)->getBoxColour().RGBA();
	}

	GOMPONENT_EXPORT void playerTextDraw_setShadow(void* textdraw, int size)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->setShadow(size);
	}

	GOMPONENT_EXPORT int playerTextDraw_getShadow(void* textdraw)
	{
		return static_cast<IPlayerTextDraw*>(textdraw)->getShadow();
	}

	GOMPONENT_EXPORT void playerTextDraw_setOutline(void* textdraw, int size)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->setOutline(size);
	}

	GOMPONENT_EXPORT int playerTextDraw_getOutline(void* textdraw)
	{
		return static_cast<IPlayerTextDraw*>(textdraw)->getOutline();
	}

	GOMPONENT_EXPORT void playerTextDraw_setBackgroundColour(void* textdraw, uint32_t colour)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->setBackgroundColour(Colour::FromRGBA(colour));
	}

	GOMPONENT_EXPORT int playerTextDraw_getBackgroundColour(void* textdraw)
	{
		return static_cast<IPlayerTextDraw*>(textdraw)->getBackgroundColour().RGBA();
	}

	GOMPONENT_EXPORT void playerTextDraw_setStyle(void* textdraw, int style)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->setStyle(TextDrawStyle(style));
	}

	GOMPONENT_EXPORT int playerTextDraw_getStyle(void* textdraw)
	{
		TextDrawStyle style = static_cast<IPlayerTextDraw*>(textdraw)->getStyle();
		return static_cast<int>(style);
	}

	GOMPONENT_EXPORT void playerTextDraw_setProportional(void* textdraw, int set)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->setProportional(set != 0);
	}

	GOMPONENT_EXPORT int playerTextDraw_isProportional(void* textdraw)
	{
		return static_cast<IPlayerTextDraw*>(textdraw)->isProportional() ? 1 : 0;
	}

	GOMPONENT_EXPORT void playerTextDraw_setSelectable(void* textdraw, int set)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->setSelectable(set != 0);
	}

	GOMPONENT_EXPORT int playerTextDraw_isSelectable(void* textdraw)
	{
		return static_cast<IPlayerTextDraw*>(textdraw)->isSelectable() ? 1 : 0;
	}

	GOMPONENT_EXPORT void playerTextDraw_setPreviewModel(void* textdraw, int model)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->setPreviewModel(model);
	}

	GOMPONENT_EXPORT int playerTextDraw_getPreviewModel(void* textdraw)
	{
		return static_cast<IPlayerTextDraw*>(textdraw)->getPreviewModel();
	}

	GOMPONENT_EXPORT void playerTextDraw_setPreviewRotation(void* textdraw, float rotX, float rotY, float rotZ)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->setPreviewRotation(Vector3(rotX, rotY, rotZ));
	}

	GOMPONENT_EXPORT Vector3 playerTextDraw_getPreviewRotation(void* textdraw)
	{
		return static_cast<IPlayerTextDraw*>(textdraw)->getPreviewRotation();
	}

	GOMPONENT_EXPORT void playerTextDraw_setPreviewVehicleColour(void* textdraw, int col1, int col2)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->setPreviewVehicleColour(col1, col2);
	}

	GOMPONENT_EXPORT VehicleColour playerTextDraw_getPreviewVehicleColour(void* textdraw)
	{
		Pair<int, int> colours = static_cast<IPlayerTextDraw*>(textdraw)->getPreviewVehicleColour();

		return { colours.first, colours.second };
	}

	GOMPONENT_EXPORT void playerTextDraw_setPreviewZoom(void* textdraw, float zoom)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->setPreviewZoom(zoom);
	}

	GOMPONENT_EXPORT float playerTextDraw_getPreviewZoom(void* textdraw)
	{
		return static_cast<IPlayerTextDraw*>(textdraw)->getPreviewZoom();
	}

	GOMPONENT_EXPORT void playerTextDraw_show(void* textdraw)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->show();
	}

	GOMPONENT_EXPORT void playerTextDraw_hide(void* textdraw)
	{
		static_cast<IPlayerTextDraw*>(textdraw)->hide();
	}

	GOMPONENT_EXPORT int playerTextDraw_isShown(void* textdraw)
	{
		return static_cast<IPlayerTextDraw*>(textdraw)->isShown() ? 1 : 0;
	}
	
#ifdef __cplusplus
}
#endif
