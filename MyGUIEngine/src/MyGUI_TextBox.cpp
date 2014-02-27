/*!
	@file
	@author		Albert Semenov
	@date		12/2007
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
#include "MyGUI_TextBox.h"
#include "MyGUI_LanguageManager.h"
#include "MyGUI_Constants.h"

namespace MyGUI
{

	TextBox::TextBox()
		:m_autoAdapt(false)
	{
	}

	IntCoord TextBox::getTextRegion()
	{
		return (nullptr == getSubWidgetText()) ? IntCoord() : getSubWidgetText()->getCoord();
	}

	IntSize TextBox::getTextSize()
	{
		return (nullptr == getSubWidgetText()) ? IntSize() : getSubWidgetText()->getTextSize();
	}

	void TextBox::setTextAlign(Align _value)
	{
		if (getSubWidgetText() != nullptr)
			getSubWidgetText()->setTextAlign(_value);
	}

	Align TextBox::getTextAlign()
	{
		if (getSubWidgetText() != nullptr)
			return getSubWidgetText()->getTextAlign();
		return Align::Default;
	}

	void TextBox::setTextColour(const Colour& _value)
	{
		if (nullptr != getSubWidgetText())
			getSubWidgetText()->setTextColour(_value);
	}

	const Colour& TextBox::getTextColour()
	{
		return (nullptr == getSubWidgetText()) ? Colour::Zero : getSubWidgetText()->getTextColour();
	}

	void TextBox::setFontName(const std::string& _value)
	{
		if (nullptr != getSubWidgetText())
			getSubWidgetText()->setFontName(_value);
	}

	const std::string& TextBox::getFontName()
	{
		if (nullptr == getSubWidgetText())
			return Constants::getEmptyString();
		return getSubWidgetText()->getFontName();
	}

	void TextBox::setFontHeight(int _height)
	{
		if (nullptr != getSubWidgetText())
			getSubWidgetText()->setFontHeight(_height);
	}

	int TextBox::getFontHeight()
	{
		return (nullptr == getSubWidgetText()) ? 0 : getSubWidgetText()->getFontHeight();
	}

	void TextBox::setCaption(const UString& _caption)
	{
		if (nullptr != getSubWidgetText())
		{
			getSubWidgetText()->setCaption(_caption);
			if (m_autoAdapt)
				adaptCoord();
		}
	}

	const UString& TextBox::getCaption()
	{
		if (nullptr == getSubWidgetText())
			return Constants::getEmptyUString();
		return getSubWidgetText()->getCaption();
	}

	void TextBox::setCaptionWithReplacing(const std::string& _value)
	{
		std::string value = LanguageManager::getInstance().replaceTags(_value);

		size_t pos = value.find("\\n");
		while (pos != std::string::npos)
		{
			value[pos++] = '\n';
			value.erase(pos, 1);
			pos = value.find("\\n");
		}
		
		setCaption(value);
	}

	void TextBox::setTextShadowColour(const Colour& _value)
	{
		if (nullptr != getSubWidgetText())
			getSubWidgetText()->setShadowColour(_value);
	}

	const Colour& TextBox::getTextShadowColour()
	{
		return (nullptr == getSubWidgetText()) ? Colour::Black : getSubWidgetText()->getShadowColour();
	}

	void TextBox::setTextShadow(bool _value)
	{
		if (nullptr != getSubWidgetText())
			getSubWidgetText()->setShadow(_value);
	}

	bool TextBox::getTextShadow()
	{
		return (nullptr == getSubWidgetText()) ? false : getSubWidgetText()->getShadow();
	}

	void TextBox::setTextShadowOffset(const FloatPoint& _value)
	{
		if (nullptr != getSubWidgetText())
			getSubWidgetText()->setShadowOffset(_value);
	}

	FloatPoint TextBox::getTextShadowOffset()
	{
		return (nullptr == getSubWidgetText()) ? FloatPoint() : getSubWidgetText()->getShadowOffset();
	}

	void TextBox::setPropertyOverride(const std::string& _key, const std::string& _value)
	{
		/// @wproperty{TextBox, TextColour, Colour} Цвет текста.
		if (_key == "TextColour")
			setTextColour(utility::parseValue<Colour>(_value));

		/// @wproperty{TextBox, TextAlign, Align} Выравнивание текста.
		else if (_key == "TextAlign")
			setTextAlign(utility::parseValue<Align>(_value));

		/// @wproperty{TextBox, FontName, string} Имя шрифта.
		else if (_key == "FontName")
			setFontName(_value);

		/// @wproperty{TextBox, FontHeight, int} Высота шрифта.
		else if (_key == "FontHeight")
			setFontHeight(utility::parseValue<int>(_value));

		/// @wproperty{TextBox, Caption, string} Содержимое по? редактирован?.
		else if (_key == "Caption")
			setCaptionWithReplacing(_value);

		/// @wproperty{TextBox, TextShadowColour, Colour} Цвет тени текста.
		else if (_key == "TextShadowColour")
			setTextShadowColour(utility::parseValue<Colour>(_value));

		/// @wproperty{TextBox, TextShadow, bool} Режи?показа тени текста.
		else if (_key == "TextShadow")
			setTextShadow(utility::parseValue<bool>(_value));
		else if (_key == "AutoAdapt")
			m_autoAdapt = utility::parseValue<bool>(_value);
		else if (_key == "TextShadowOffset")
			setTextShadowOffset(FloatPoint::parse(_value));
		else
		{
			Base::setPropertyOverride(_key, _value);
			return;
		}

		eventChangeProperty(this, _key, _value);
	}

	void TextBox::adaptCoord()
	{
		if (nullptr == getSubWidgetText()) return;

		Align align = getAlign();
		const IntCoord& origCoord = getCoord();
		IntCoord textCoord = getSubWidgetText()->getCoord();
		IntSize textMargin;
		textMargin.width = origCoord.width - textCoord.width;
		textMargin.height = origCoord.height - textCoord.height;

		IntCoord coord = origCoord;
		IntSize textSize = getSubWidgetText()->getTextSize();

		if (!align.isHStretch())
			coord.width = textSize.width + textMargin.width;
		if (!align.isVStretch())
			coord.height = textSize.height + textMargin.height;

		Align textAlign = getTextAlign();
		if (textAlign.isLeft())
			coord.left = origCoord.left;
		else if (textAlign.isRight())
			coord.left = origCoord.right() - coord.width;
		else if (textAlign.isHCenter())
		{
			if (!align.isHStretch() && coord.width % 2 != 0)
			{
				coord.width += 1;
			}
			coord.left += origCoord.width / 2 - coord.width / 2;
		}
		
		if (textAlign.isTop())
			coord.top = origCoord.top;
		else if (textAlign.isBottom())
			coord.top = origCoord.bottom() - coord.height;
		else if (textAlign.isVCenter())
		{
			if (!align.isVStretch() && coord.height % 2 != 0)
			{
				coord.height += 1;
			}
			coord.top += (origCoord.height - coord.height) / 2;
		}

		setCoord(coord);
	}

	void TextBox::changeWidgetSkin( const std::string& _skinName )
	{
		UString caption = getCaption();
		Base::changeWidgetSkin(_skinName);
		setCaption(caption);
	}

} // namespace MyGUI
