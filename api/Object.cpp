#include <sdk.hpp>
#include <iostream>
#include <Server/Components/Objects/objects.hpp>

#include "api.hpp"
#include "Gomponent.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct
	{
		int model;
		String textureLibrary;
		String textureName;
		uint32_t colour;
	} ObjectMaterial;

	typedef struct
	{
		String text;
		uint8_t materialSize;
		String fontFace;
		uint8_t fontSize;
		unsigned char bold;
		uint32_t fontColour;
		uint32_t backgroundColour;
		uint8_t alignment;
	} ObjectMaterialText;

	GOMPONENT_EXPORT void* object_create(int modelId, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float drawDistance)
	{
		IObjectsComponent* objects = Gomponent::Get()->objects;

		if (objects)
		{
			IObject* object = objects->create(modelId, Vector3(posX, posY, posZ), Vector3(rotX, rotY, rotZ), drawDistance);
			if (object)
			{
				return static_cast<void*>(object);
			}
		}
		return NULL;
	}

	GOMPONENT_EXPORT void object_release(void* object)
	{
		IObjectsComponent* objects = Gomponent::Get()->objects;

		if (objects)
		{
			objects->release(static_cast<IObject*>(object)->getID());
		}
	}

	GOMPONENT_EXPORT void* object_getByID(int id)
	{
		IObjectsComponent* objects = Gomponent::Get()->objects;

		if (objects)
		{
			IObject* object = objects->get(id);

			if (object)
			{
				return static_cast<void*>(object);
			}
		}

		return NULL;
	}

	GOMPONENT_EXPORT void object_setDefaultCameraCollision(unsigned char set)
	{
		IObjectsComponent* objects = Gomponent::Get()->objects;

		if (objects)
		{
			return objects->setDefaultCameraCollision(set != 0);
		}
	}

	GOMPONENT_EXPORT void object_setDrawDistance(void* object, float drawDistance)
	{
		static_cast<IObject*>(object)->setDrawDistance(drawDistance);
	}

	GOMPONENT_EXPORT float object_getDrawDistance(void* object)
	{
		return static_cast<IObject*>(object)->getDrawDistance();
	}

	GOMPONENT_EXPORT void object_setModel(void* object, int model)
	{
		static_cast<IObject*>(object)->setModel(model);
	}

	GOMPONENT_EXPORT int object_getModel(void* object)
	{
		return static_cast<IObject*>(object)->getModel();
	}

	GOMPONENT_EXPORT void object_setCameraCollision(void* object, unsigned char set)
	{
		static_cast<IObject*>(object)->setCameraCollision(set);
	}

	GOMPONENT_EXPORT unsigned char object_getCameraCollision(void* object)
	{
		return static_cast<IObject*>(object)->getCameraCollision() ? 1 : 0;
	}

	GOMPONENT_EXPORT int object_move(void* object, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float speed)
	{
		ObjectMoveData data;
		data.targetPos = Vector3(posX, posY, posZ);
		data.targetRot = Vector3(rotX, rotY, rotZ);
		data.speed = speed;

		static_cast<IObject*>(object)->move(data);

		float estimatedTime = (glm::length(data.targetPos - static_cast<IObject*>(object)->getPosition()) / speed) * 1000.0f;
		return static_cast<int>(estimatedTime);
	}

	GOMPONENT_EXPORT unsigned char object_isMoving(void* object)
	{
		return static_cast<IObject*>(object)->isMoving() ? 1 : 0;
	}

	GOMPONENT_EXPORT void object_stop(void* object)
	{
		static_cast<IObject*>(object)->stop();
	}

	GOMPONENT_EXPORT ObjectMoveData object_getMovingData(void* object)
	{
		return static_cast<IObject*>(object)->getMovingData();
	}

	GOMPONENT_EXPORT void object_attachToVehicle(void* object, void* vehicle, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ)
	{
		static_cast<IObject*>(object)->attachToVehicle(*static_cast<IVehicle*>(vehicle), Vector3(offsetX, offsetY, offsetZ), Vector3(rotX, rotY, rotZ));
	}

	GOMPONENT_EXPORT void object_resetAttachment(void* object)
	{
		static_cast<IObject*>(object)->resetAttachment();
	}

	GOMPONENT_EXPORT ObjectAttachmentData object_getAttachmentData(void* object)
	{
		return static_cast<IObject*>(object)->getAttachmentData();
	}

	GOMPONENT_EXPORT unsigned char object_isMaterialSlotUsed(void* object, uint32_t materialIndex)
	{
		const ObjectMaterialData* data = nullptr;
		bool result = static_cast<IObject*>(object)->getMaterialData(materialIndex, data);
		if (result)
		{
			return data->used ? 1 : 0;
		}
		return result ? 1 : 0;
	}

	GOMPONENT_EXPORT unsigned char object_getMaterial(void* object, uint32_t materialIndex, ObjectMaterial* out)
	{
		const ObjectMaterialData* data = nullptr;
		bool result = static_cast<IObject*>(object)->getMaterialData(materialIndex, data);

		if (result)
		{
			out->model = data->model;
			out->textureLibrary = (String) { data->textOrTXD.data(), data->textOrTXD.length() };
			out->textureName = (String) { data->fontOrTexture.data(), data->fontOrTexture.length() };
			out->colour = data->materialColour.ARGB();
		}

		return result ? 1 : 0;
	}

	GOMPONENT_EXPORT unsigned char object_getMaterialText(void* object, uint32_t materialIndex, ObjectMaterialText* out)
	{
		const ObjectMaterialData* data = nullptr;
		bool result = static_cast<IObject*>(object)->getMaterialData(materialIndex, data);

		if (result)
		{
			out->text = (String) { data->textOrTXD.data(), data->textOrTXD.length() };
			out->materialSize = data->materialSize;
			out->fontFace = (String) { data->fontOrTexture.data(), data->fontOrTexture.length() };
			out->fontSize = data->fontSize;
			out->bold = data->bold ? 1 : 0;
			out->fontColour = data->fontColour.ARGB();
			out->backgroundColour = data->backgroundColour.ARGB();
			out->alignment = data->alignment;
		}

		return result ? 1 : 0;
	}

	GOMPONENT_EXPORT void object_setMaterial(void* object, uint32_t materialIndex, int model, String textureLibrary, String textureName, uint32_t colour)
	{
		static_cast<IObject*>(object)->setMaterial(materialIndex, model, StringView(textureLibrary.buf, textureLibrary.length), StringView(textureName.buf, textureName.length), Colour::FromARGB(colour));
	}

	GOMPONENT_EXPORT void object_setMaterialText(void* object, uint32_t materialIndex, String text, ObjectMaterialSize materialSize, String fontFace, int fontSize, unsigned char bold, uint32_t fontColour, uint32_t backgroundColour, ObjectMaterialTextAlign align)
	{
		static_cast<IObject*>(object)->setMaterialText(materialIndex, StringView(text.buf, text.length), materialSize, StringView(fontFace.buf, fontFace.length), fontSize, bold != 0, Colour::FromARGB(fontColour), Colour::FromARGB(backgroundColour), align);
	}

	GOMPONENT_EXPORT void object_attachToPlayer(void* object, void* player, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ)
	{
		static_cast<IObject*>(object)->attachToPlayer(*static_cast<IPlayer*>(player), Vector3(offsetX, offsetY, offsetZ), Vector3(rotX, rotY, rotZ));
	}

	GOMPONENT_EXPORT void object_attachToObject(void* object, void* other, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, unsigned char syncRotation)
	{
		static_cast<IObject*>(object)->attachToObject(*static_cast<IObject*>(other), Vector3(offsetX, offsetY, offsetZ), Vector3(rotX, rotY, rotZ), syncRotation != 0);
	}

	// entity

	GOMPONENT_EXPORT void object_setPosition(void* object, float posX, float posY, float posZ)
	{
		static_cast<IObject*>(object)->setPosition(Vector3(posX, posY, posZ));
	}

	GOMPONENT_EXPORT Vector3 object_getPosition(void* object)
	{
		return static_cast<IObject*>(object)->getPosition();
	}

	GOMPONENT_EXPORT void object_setRotation(void* object, float rotX, float rotY, float rotZ)
	{
		static_cast<IObject*>(object)->setRotation(Vector3(rotX, rotY, rotZ));
	}

	GOMPONENT_EXPORT Vector3 object_getRotation(void* object)
	{
		return static_cast<IObject*>(object)->getRotation().ToEuler();
	}

	// PlayerObject

	GOMPONENT_EXPORT void* playerObject_create(void* player, int modelId, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float drawDistance)
	{
		IPlayerObjectData* data = queryExtension<IPlayerObjectData>(static_cast<IPlayer*>(player));
		IPlayerObject* object = data->create(modelId, Vector3(posX, posY, posZ), Vector3(rotX, rotY, rotZ), drawDistance);

		if (object)
		{
			return static_cast<void*>(object);
		}

		return NULL;
	}

	GOMPONENT_EXPORT void playerObject_release(void* object, void* player)
	{
		IPlayerObjectData* data = queryExtension<IPlayerObjectData>(static_cast<IPlayer*>(player));

		data->release(static_cast<IObject*>(object)->getID());
	}

	GOMPONENT_EXPORT void* playerObject_getByID(void* player, int id)
	{
		IPlayerObjectData* data = queryExtension<IPlayerObjectData>(static_cast<IPlayer*>(player));

		if (data)
		{
			IPlayerObject* object = data->get(id)

			if (object)
			{
				return static_cast<void*>(object);
			}
		}

		return NULL;
	}

	GOMPONENT_EXPORT void playerObject_setDrawDistance(void* object, float drawDistance)
	{
		static_cast<IPlayerObject*>(object)->setDrawDistance(drawDistance);
	}

	GOMPONENT_EXPORT float playerObject_getDrawDistance(void* object)
	{
		return static_cast<IPlayerObject*>(object)->getDrawDistance();
	}

	GOMPONENT_EXPORT void playerObject_setModel(void* object, int model)
	{
		static_cast<IPlayerObject*>(object)->setModel(model);
	}

	GOMPONENT_EXPORT int playerObject_getModel(void* object)
	{
		return static_cast<IPlayerObject*>(object)->getModel();
	}

	GOMPONENT_EXPORT void playerObject_setCameraCollision(void* object, unsigned char set)
	{
		static_cast<IPlayerObject*>(object)->setCameraCollision(set);
	}

	GOMPONENT_EXPORT unsigned char playerObject_getCameraCollision(void* object)
	{
		return static_cast<IPlayerObject*>(object)->getCameraCollision() ? 1 : 0;
	}

	GOMPONENT_EXPORT int playerObject_move(void* object, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float speed)
	{
		ObjectMoveData data;
		data.targetPos = Vector3(posX, posY, posZ);
		data.targetRot = Vector3(rotX, rotY, rotZ);
		data.speed = speed;

		static_cast<IPlayerObject*>(object)->move(data);

		float estimatedTime = (glm::length(data.targetPos - static_cast<IPlayerObject*>(object)->getPosition()) / speed) * 1000.0f;
		return static_cast<int>(estimatedTime);
	}

	GOMPONENT_EXPORT unsigned char playerObject_isMoving(void* object)
	{
		return static_cast<IPlayerObject*>(object)->isMoving() ? 1 : 0;
	}

	GOMPONENT_EXPORT void playerObject_stop(void* object)
	{
		static_cast<IPlayerObject*>(object)->stop();
	}

	GOMPONENT_EXPORT ObjectMoveData playerObject_getMovingData(void* object)
	{
		return static_cast<IPlayerObject*>(object)->getMovingData();
	}

	GOMPONENT_EXPORT void playerObject_attachToVehicle(void* object, void* vehicle, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ)
	{
		static_cast<IPlayerObject*>(object)->attachToVehicle(*static_cast<IVehicle*>(vehicle), Vector3(offsetX, offsetY, offsetZ), Vector3(rotX, rotY, rotZ));
	}

	GOMPONENT_EXPORT void playerObject_resetAttachment(void* object)
	{
		static_cast<IPlayerObject*>(object)->resetAttachment();
	}

	GOMPONENT_EXPORT ObjectAttachmentData playerObject_getAttachmentData(void* object)
	{
		return static_cast<IPlayerObject*>(object)->getAttachmentData();
	}

	GOMPONENT_EXPORT unsigned char playerObject_isMaterialSlotUsed(void* object, uint32_t materialIndex)
	{
		const ObjectMaterialData* data = nullptr;
		bool result = static_cast<IPlayerObject*>(object)->getMaterialData(materialIndex, data);
		if (result)
		{
			return data->used ? 1 : 0;
		}
		return result ? 1 : 0;
	}

	GOMPONENT_EXPORT unsigned char playerObject_getMaterial(void* object, uint32_t materialIndex, ObjectMaterial* out)
	{
		const ObjectMaterialData* data = nullptr;
		bool result = static_cast<IPlayerObject*>(object)->getMaterialData(materialIndex, data);

		if (result)
		{
			out->model = data->model;
			out->textureLibrary = (String) { data->textOrTXD.data(), data->textOrTXD.length() };
			out->textureName = (String) { data->fontOrTexture.data(), data->fontOrTexture.length() };
			out->colour = data->materialColour.ARGB();
		}

		return result ? 1 : 0;
	}

	GOMPONENT_EXPORT unsigned char playerObject_getMaterialText(void* object, uint32_t materialIndex, ObjectMaterialText* out)
	{
		const ObjectMaterialData* data = nullptr;
		bool result = static_cast<IPlayerObject*>(object)->getMaterialData(materialIndex, data);

		if (result)
		{
			out->text = (String) { data->textOrTXD.data(), data->textOrTXD.length() };
			out->materialSize = data->materialSize;
			out->fontFace = (String) { data->fontOrTexture.data(), data->fontOrTexture.length() };
			out->fontSize = data->fontSize;
			out->bold = data->bold ? 1 : 0;
			out->fontColour = data->fontColour.ARGB();
			out->backgroundColour = data->backgroundColour.ARGB();
			out->alignment = data->alignment;
		}

		return result ? 1 : 0;
	}

	GOMPONENT_EXPORT void playerObject_setMaterial(void* object, uint32_t materialIndex, int model, String textureLibrary, String textureName, uint32_t colour)
	{
		static_cast<IPlayerObject*>(object)->setMaterial(materialIndex, model, StringView(textureLibrary.buf, textureLibrary.length), StringView(textureName.buf, textureName.length), Colour::FromARGB(colour));
	}

	GOMPONENT_EXPORT void playerObject_setMaterialText(void* object, uint32_t materialIndex, String text, ObjectMaterialSize materialSize, String fontFace, int fontSize, unsigned char bold, uint32_t fontColour, uint32_t backgroundColour, ObjectMaterialTextAlign align)
	{
		static_cast<IPlayerObject*>(object)->setMaterialText(materialIndex, StringView(text.buf, text.length), materialSize, StringView(fontFace.buf, fontFace.length), fontSize, bold != 0, Colour::FromARGB(fontColour), Colour::FromARGB(backgroundColour), align);
	}

	GOMPONENT_EXPORT void playerObject_attachToPlayer(void* object, void* player, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ)
	{
		static_cast<IPlayerObject*>(object)->attachToPlayer(*static_cast<IPlayer*>(player), Vector3(offsetX, offsetY, offsetZ), Vector3(rotX, rotY, rotZ));
	}

	GOMPONENT_EXPORT void playerObject_attachToObject(void* object, void* other, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ)
	{
		static_cast<IPlayerObject*>(object)->attachToObject(*static_cast<IPlayerObject*>(other), Vector3(offsetX, offsetY, offsetZ), Vector3(rotX, rotY, rotZ));
	}

	// entity

	GOMPONENT_EXPORT void playerObject_setPosition(void* object, float posX, float posY, float posZ)
	{
		static_cast<IPlayerObject*>(object)->setPosition(Vector3(posX, posY, posZ));
	}

	GOMPONENT_EXPORT Vector3 playerObject_getPosition(void* object)
	{
		return static_cast<IPlayerObject*>(object)->getPosition();
	}

	GOMPONENT_EXPORT void playerObject_setRotation(void* object, float rotX, float rotY, float rotZ)
	{
		static_cast<IPlayerObject*>(object)->setRotation(Vector3(rotX, rotY, rotZ));
	}

	GOMPONENT_EXPORT Vector3 playerObject_getRotation(void* object)
	{
		return static_cast<IPlayerObject*>(object)->getRotation().ToEuler();
	}

#ifdef __cplusplus
}
#endif
