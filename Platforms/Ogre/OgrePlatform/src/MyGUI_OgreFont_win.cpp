#include "MyGUI_OgreFont_win.h"
#include "MyGUI_OgreRenderManager.h"
#include "MyGUI_DataManager.h"

namespace MyGUI
{
	const uint32 FONT_MASK_SELECT = 0xFF888888;
	//const uint32 FONT_MASK_SELECT_DEACTIVE = 0xFF606060;
	const uint32 FONT_MASK_SELECT_DEACTIVE = 0xFF888888;
	const uint32 FONT_MASK_CHAR = 0xFFFFFFFF;

	ResourceNativeFontImp* OgreFontBuilder::create(ResourceNativeFont* _data)
	{
		return new OgreFontWin(_data);
	}

	void OgreFontBuilder::destroy(ResourceNativeFontImp* _imp)
	{
		delete (OgreFontWin*)_imp;
	}

	void OgreFontBuilder::initialise()
	{
	}

	void OgreFontBuilder::shutdown()
	{

	}

	///////////////////////////////////////////////////////////////////////////////////////////


	OgreFontWin::OgreFontWin(ResourceNativeFont* _data)
		:OgreFont(_data),
		m_MemDC(NULL),
		m_Font(NULL),
		m_Ascent(0),
		m_OffX(0),
		m_OffY(0),
		mTextureSize(MAX_TEXTURE_SIZE)
	{
	}

	OgreFontWin::~OgreFontWin()
	{
		if (m_Font != NULL)
		{
			::DeleteObject(m_Font);
			m_Font = NULL;
		}

		// 清理 GDI 相关的资源
		if (m_MemDC != NULL)
		{
			::DeleteDC(m_MemDC);
			m_MemDC = NULL;
		}
	}

	void OgreFontWin::initialise()
	{
		// 这个函数 直接就返回TRUE了,需要修改
		bool rgbaMode = RenderManager::getInstance().isFormatSupported(PixelFormat::R8G8B8A8, TextureUsage::Static | TextureUsage::Write);
		if (!rgbaMode)
		{
			MYGUI_LOG(Error, "字体格式不是 R8G8B8A8");
			return;
		}

		HDC hDC = ::GetDC(NULL);
		m_MemDC = ::CreateCompatibleDC(hDC);
		if (m_MemDC == NULL)
		{
			MYGUI_LOG(Error, "字体兼容DC创建失败");
			return;
		}
		::ReleaseDC(NULL,hDC);

		// 字体模式
		::SetMapMode(m_MemDC, MM_TEXT);
		::SetTextColor(m_MemDC, RGB(255,255,255));
		::SetBkColor(m_MemDC, RGB(0,0,0));

		HFONT       hDefFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		LOGFONTA    tNewFont = {0};
		
		GetObjectA(hDefFont, sizeof(tNewFont), &tNewFont);

		if (!mSource.empty())
		{
			// create font from ttf file
			int nFindttf = mSource.find(".ttf");
			int nFindTTF = mSource.find(".TTF");

			std::string fontName = mSource;
			if (nFindttf >= 0 || nFindTTF >= 0)
			{
				std::string fontPath = DataManager::getInstance().getDataPath(fontName);
				int nFindPos = fontName.rfind("/");
				fontName = &fontName[nFindPos+1];
				nFindPos = fontName.rfind(".");
				fontName = fontName.substr(0, nFindPos);
				strcpy_s(tNewFont.lfFaceName, LF_FACESIZE, fontName.c_str());

				if(AddFontResource(fontPath.c_str()))
				{
					Ogre::RenderWindow* window = OgreRenderManager::getInstancePtr()->getRenderWindow();
					HWND hwnd = 0;
					window->getCustomAttribute("WINDOW", &hwnd);
					SendMessage(hwnd, WM_FONTCHANGE, 0, 0);
				}
			}

			tNewFont.lfCharSet = DEFAULT_CHARSET;
			strcpy_s(tNewFont.lfFaceName, LF_FACESIZE, fontName.c_str());
		}

		if (mSize)
		{
			tNewFont.lfHeight = -mSize;
		}
		tNewFont.lfQuality = ANTIALIASED_QUALITY;
		tNewFont.lfItalic = mItalic ? TRUE : FALSE;
		if (mBold) tNewFont.lfWeight *= 2;
		m_Font = CreateFontIndirectA(&tNewFont);

		if (! m_Font)
		{
			m_Font = hDefFont;
			MYGUI_LOG(Error, "字体创建失败");
			return;
		}

		::SelectObject(m_MemDC, m_Font);

		TEXTMETRIC tm;
		::GetTextMetrics(m_MemDC, &tm);
		m_Ascent = tm.tmAscent;

		mDefaultHeight = tm.tmHeight;

		m_IsFull = false;
		changeImage(mTextureSize, mTextureSize);
		loadCharactor(FontCodeType::Space);
	}

	GlyphInfo* OgreFontWin::loadCharactor(Char _id)
	{
		if (mTexture == nullptr)
		{
			MYGUI_LOG(Error, "无效的纹理对象");
			return nullptr;
		}

		if (m_IsFull)
		{
			m_OffX = 0;
			m_OffY = 0;

			changeImage(mTextureSize, mTextureSize);

			m_IsFull = false;
		}

		// 清理数据
		GLYPHMETRICS _GM;
		memset(&_GM, 0, sizeof(GLYPHMETRICS));

		switch(_id)
		{
		case FontCodeType::Selected:
			{
				m_Buffer.resize(mDefaultHeight * 4);
				uint32* lpDst = (uint32*)&m_Buffer[0];

				// 文字高的1点竖条
				for (uint32 y = 0; y < mDefaultHeight; ++y)
				{
					*lpDst = FONT_MASK_SELECT;
					lpDst += 1;
				}

				Ogre::PixelBox pixbox(1, mDefaultHeight, 1, Ogre::PF_BYTE_RGBA, &m_Buffer[0]);
				mTexture->getOgreTexture()->getBuffer()->blitFromMemory(pixbox, Ogre::Image::Box(m_OffX, m_OffY, m_OffX + 1, m_OffY + mDefaultHeight));

				// 宽度;高度
				_GM.gmBlackBoxX = 1;
				_GM.gmBlackBoxY = mDefaultHeight;
				_GM.gmCellIncX = 1;
			}
			break;
		case FontCodeType::SelectedBack:
			{
				m_Buffer.resize(mDefaultHeight * 4);
				uint32* lpDst = (uint32*)&m_Buffer[0];

				// 文字高的1点竖条
				for (uint32 y = 0; y < mDefaultHeight; ++y)
				{
					*lpDst = FONT_MASK_SELECT_DEACTIVE;
					lpDst += 1;
				}
				
				Ogre::PixelBox pixbox(1, mDefaultHeight, 1, Ogre::PF_BYTE_RGBA, &m_Buffer[0]);
				mTexture->getOgreTexture()->getBuffer()->blitFromMemory(pixbox, Ogre::Image::Box(m_OffX, m_OffY, m_OffX + 1, m_OffY + mDefaultHeight));

				// 宽度;高度
				_GM.gmBlackBoxX = 1;
				_GM.gmBlackBoxY = mDefaultHeight;
				_GM.gmCellIncX = 1;
			}
			break;
		case FontCodeType::Cursor:
			{
				m_Buffer.resize(mCursorWidth * mDefaultHeight * 4);
				uint32* lpDst = (uint32*)&m_Buffer[0];

				for (uint32 y = 0; y < mDefaultHeight; ++y)
				{
					for (uint32 x = 0; x < mCursorWidth; ++x)
					{
						lpDst[x] = FONT_MASK_CHAR;
					}
					lpDst += mCursorWidth;
				}
				
				Ogre::PixelBox pixbox(mCursorWidth, mDefaultHeight, 1, Ogre::PF_BYTE_RGBA, &m_Buffer[0]);
				mTexture->getOgreTexture()->getBuffer()->blitFromMemory(pixbox, Ogre::Image::Box(m_OffX, m_OffY, m_OffX + mCursorWidth, m_OffY + mDefaultHeight));

				// 宽度;高度
				_GM.gmBlackBoxX = mCursorWidth;
				_GM.gmBlackBoxY = mDefaultHeight;
				_GM.gmCellIncX = mCursorWidth;
			}
			break;
		case FontCodeType::Tab:
			break;
		default:
			{
				// 有效数据
				if (_id < 0xFFFF && !mGlyphInfo[_id])
				{
					// 字模格式
					MAT2 mat2 = {{0,1},{0,0},{0,0},{0,1}};
					uint32 nLen = ::GetGlyphOutlineW(m_MemDC, _id, GGO_GRAY8_BITMAP, &_GM, 0, NULL, &mat2);

					// 有效字符
					if((signed)nLen > 0)
					{
						m_Buffer.resize(nLen);
						std::fill(m_Buffer.begin(), m_Buffer.end(), 0);
						// 字符轮廓
						if (nLen == ::GetGlyphOutlineW(m_MemDC, _id, GGO_GRAY8_BITMAP, &_GM, nLen, &m_Buffer[0], &mat2))
						{
							std::vector<uint32> pixels;
							pixels.resize(_GM.gmBlackBoxX * _GM.gmBlackBoxY, 0);


							// 获取数据
							uint8* lpSrc = &m_Buffer[0];
							uint32* lpDst = &pixels[0];

							// 位图调整
							LONG nSrcPitch = ((_GM.gmBlackBoxX + 3) >> 2) << 2;
							LONG nDstPitch = _GM.gmBlackBoxX;

							// 拷贝数据
							for (uint32 y = 0; y < _GM.gmBlackBoxY; ++y)
							{
								for (uint32 x = 0; x < _GM.gmBlackBoxX; ++x)
								{
									// 按字节计算
									uint32 gray = lpSrc[x] << 2;
									if (gray != 0) {
										if (gray > 255) gray = 255;
										lpDst[x] = (gray << 24) | 0x00FFFFFF;
									}
								}
								lpSrc += nSrcPitch;
								lpDst += nDstPitch;
							}

							Ogre::PixelBox pixbox(_GM.gmBlackBoxX, _GM.gmBlackBoxY, 1, Ogre::PF_BYTE_RGBA, &pixels[0]);
							mTexture->getOgreTexture()->getBuffer()->blitFromMemory(pixbox, 
												Ogre::Image::Box(m_OffX + _GM.gmptGlyphOrigin.x, m_OffY + (m_Ascent -_GM.gmptGlyphOrigin.y),
													m_OffX + _GM.gmptGlyphOrigin.x + _GM.gmBlackBoxX, m_OffY + m_Ascent - _GM.gmptGlyphOrigin.y + _GM.gmBlackBoxY));
						}
					}
				}
				break;
			}
		}

		// 无效字符
		if (_GM.gmBlackBoxX == 0)
		{
			return mGlyphInfo[FontCodeType::Space];
		}

		// 生成信息
		GlyphInfo* _info = new GlyphInfo;
		_info->codePoint = _id;
		_info->uvRect.left = (float)m_OffX / (float)mTextureSize;
		_info->uvRect.top = (float)(m_OffY + mOffsetHeight) / (float)mTextureSize;
		_info->uvRect.right = (float)(m_OffX + _GM.gmCellIncX) / (float)mTextureSize;
		_info->uvRect.bottom = (float)(m_OffY + mOffsetHeight + mDefaultHeight) / (float)mTextureSize;
		_info->width = _GM.gmCellIncX;
		_info->height = mDefaultHeight;
		_info->advance = _GM.gmCellIncX;
		mGlyphInfo[_id] = _info;
		// MYGUI 选中的兼容效果,宽度设置为0
		if (_id == FontCodeType::Selected || _id == FontCodeType::SelectedBack)
		{
			_info->width = 0.0f;
			_info->uvRect.right = _info->uvRect.left;
		}

		m_OffX += _GM.gmCellIncX + 1;

		if (m_OffX > mTextureSize - mDefaultHeight)
		{
			m_OffX = 0;
			m_OffY += mDefaultHeight + 1;
			if (m_OffY > mTextureSize - mDefaultHeight)
			{
				m_IsFull = true;
			}
		}

		return _info;
	}
}