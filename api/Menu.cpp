#include <sdk.hpp>
#include "Server/Components/Menus/menus.hpp"

#include "api.hpp"
#include "Gomponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	GOMPONENT_EXPORT void* menu_create(String title, float posX, float posY, uint8_t columns, float col1Width, float col2Width)
	{
		auto gamemode = Gomponent::Get()->getGamemode();
		IMenusComponent* menus = gamemode->menus;

		if (menus)
		{
			IMenu* menu = menus->create(StringView(title.buf, title.length), Vector2(posX, posY), columns, col1Width, col2Width);
			if (menu)
			{
				return menu;
			}
		}

		return NULL;
	}

	GOMPONENT_EXPORT void menu_release(void* menu)
	{
		auto gamemode = Gomponent::Get()->getGamemode();
		IMenusComponent* menus = gamemode->menus;

		if (menus)
		{
			menus->release(static_cast<IMenu*>(menu)->getID());
		}
	}

	GOMPONENT_EXPORT void menu_setColumnHeader(void* menu, String header, uint8_t column)
	{
		static_cast<IMenu*>(menu)->setColumnHeader(StringView(header.buf, header.length), column);
	}

	GOMPONENT_EXPORT void menu_addCell(void* menu, String itemText, uint8_t column)
	{
		static_cast<IMenu*>(menu)->addCell(StringView(itemText.buf, itemText.length), column);
	}

	GOMPONENT_EXPORT void menu_disableRow(void* menu, uint8_t row)
	{
		static_cast<IMenu*>(menu)->disableRow(row);
	}

	GOMPONENT_EXPORT unsigned char menu_isRowEnabled(void* menu, uint8_t row)
	{
		return static_cast<IMenu*>(menu)->isRowEnabled(row) ? 1 : 0;
	}

	GOMPONENT_EXPORT void menu_disable(void* menu)
	{
		static_cast<IMenu*>(menu)->disable();
	}

	GOMPONENT_EXPORT unsigned char menu_isEnabled(void* menu)
	{
		return static_cast<IMenu*>(menu)->isEnabled() ? 1 : 0;
	}

	GOMPONENT_EXPORT Vector2 menu_getPosition(void* menu)
	{
		return static_cast<IMenu*>(menu)->getPosition();
	}

	GOMPONENT_EXPORT int menu_getRowCount(void* menu, uint8_t column)
	{
		return static_cast<IMenu*>(menu)->getRowCount(column);
	}

	GOMPONENT_EXPORT int menu_getColumnCount(void* menu)
	{
		return static_cast<IMenu*>(menu)->getColumnCount();
	}

	GOMPONENT_EXPORT Vector2 menu_getColumnWidths(void* menu)
	{
		return static_cast<IMenu*>(menu)->getColumnWidths();
	}

	GOMPONENT_EXPORT String menu_getColumnHeader(void* menu, uint8_t column)
	{
		StringView headerView = static_cast<IMenu*>(menu)->getColumnHeader(column);

		return { headerView.data(), headerView.length() };
	}

	GOMPONENT_EXPORT String menu_getCell(void* menu, uint8_t column, uint8_t row)
	{
		StringView cellView = static_cast<IMenu*>(menu)->getCell(column, row);

		return { cellView.data(), cellView.length() };
	}

	GOMPONENT_EXPORT void menu_showForPlayer(void* menu, void* player)
	{
		static_cast<IMenu*>(menu)->showForPlayer(*static_cast<IPlayer*>(player));
	}

	GOMPONENT_EXPORT void menu_hideForPlayer(void* menu, void* player)
	{
		static_cast<IMenu*>(menu)->hideForPlayer(*static_cast<IPlayer*>(player));
	}

#ifdef __cplusplus
}
#endif
