#ifndef __MYGUI_COCOS2D_FONT_WIN_H__
#define __MYGUI_COCOS2D_FONT_WIN_H__

#include "MyGUI_OgreFont.h"
#include <windows.h>

namespace MyGUI
{

	class OgreFontWin :
		public OgreFont
	{
		static const int MAX_TEXTURE_SIZE = 512;
	public:
		OgreFontWin(ResourceNativeFont* _data);
		virtual ~OgreFontWin();

		virtual void initialise();
		virtual GlyphInfo* loadCharactor(Char _id);

	private:
		HDC m_MemDC;
		HFONT m_Font;
		LONG m_Ascent;
		UINT m_OffX;
		UINT m_OffY;
		std::vector<uint8> m_Buffer;
		bool m_IsFull;
		const int mTextureSize;
	};

}

#endif // __MYGUI_COCOS2D_FONT_WIN_H__