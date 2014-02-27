/*!
	@file
	@author		Albert Semenov
	@date		09/2009
*/
/*
	This file is part of MyGUI.

	MyGUI is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	MyGUI is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with MyGUI.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "MyGUI_Precompiled.h"
#include "MyGUI_TextureUtility.h"
#include "MyGUI_RenderManager.h"
#include "MyGUI_DataManager.h"
#include "MyGUI_Bitwise.h"
#include "MyGUI_Constants.h"

namespace MyGUI
{

	namespace texture_utility
	{

		const IntSize& getTextureSize(const std::string& _texture, bool _cache)
		{
			static std::string prevTexture;
			static IntSize prevSize;

			if (prevTexture == _texture && _cache)
				return prevSize;

			prevTexture.clear();
			prevSize.clear();

			if (_texture.empty())
				return Constants::getZeroIntSize();

			RenderManager& render = RenderManager::getInstance();

			ITexture* texture = render.getTexture(_texture);
			if (texture == nullptr)
			{
				if (!DataManager::getInstance().isDataExist(_texture))
				{
					MYGUI_LOG(Error, "Texture '" + _texture + "' not found");
					return Constants::getZeroIntSize();
				}
				else
				{
					texture = render.createTexture(_texture);
					if (texture == nullptr)
					{
						MYGUI_LOG(Error, "Texture '" + _texture + "' not found");
						return Constants::getZeroIntSize();
					}
					texture->loadFromFile(_texture);
				}
			}

			prevSize = IntSize(texture->getWidth(), texture->getHeight());
			prevTexture = _texture;

	#if MYGUI_DEBUG_MODE == 1
			if (!Bitwise::isPO2(prevSize.width) || !Bitwise::isPO2(prevSize.height))
			{
				//MYGUI_LOG(Warning, "Texture '" + _texture + "' have non power of two size");
			}
	#endif

			return prevSize;
		}

		const IntSize& getTextureContentSize(const std::string& _texture, bool _cache)
		{
			// предыдущя текстура
			static std::string old_texture;
			static IntSize old_size;

			if (old_texture == _texture && _cache)
				return old_size;
			old_texture = _texture;
			old_size.clear();

			if (_texture.empty())
				return old_size;

			RenderManager& render = RenderManager::getInstance();

			if (nullptr == render.getTexture(_texture))
			{
				if (!DataManager::getInstance().isDataExist(_texture))
				{
					MYGUI_LOG(Error, "Texture '" + _texture + "' not found");
					return old_size;
				}
				else
				{
					ITexture* texture = render.createTexture(_texture);
					texture->loadFromFile(_texture);
				}
			}

			ITexture* texture = render.getTexture(_texture);
			if (texture == nullptr)
			{
				MYGUI_LOG(Error, "Texture '" + _texture + "' not found");
				return old_size;
			}

			old_size.set(texture->getContentWidth(), texture->getContentHeight());

#if MYGUI_DEBUG_MODE == 1
			if (!Bitwise::isPO2(old_size.width) || !Bitwise::isPO2(old_size.height))
			{
				MYGUI_LOG(Warning, "Texture '" + _texture + "' have non power of two size");
			}
#endif

			return old_size;
		}

		uint32 toColourARGB(const Colour& _colour)
		{
			uint32 val32 = uint8(_colour.alpha * 255);
			val32 <<= 8;
			val32 += uint8(_colour.red * 255);
			val32 <<= 8;
			val32 += uint8(_colour.green * 255);
			val32 <<= 8;
			val32 += uint8(_colour.blue * 255);
			return val32;
		}

	} // namespace texture_utility

} // namespace MyGUI
