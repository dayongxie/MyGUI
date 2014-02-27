// -*- coding: utf-8 -*-
#include "MyGUI_Cocos2dFont.h"
#include "MyGUI_Cocos2dRenderManager.h"
#include "MyGUI_Gui.h"

using namespace cocos2d;


const uint16_t FONT_MASK_SELECT = 0x88FF;
const uint16_t FONT_MASK_SELECT_DEACTIVE = 0xFFFF;
const uint16_t FONT_MASK_CHAR = 0x88FF;

namespace MyGUI
{
    
    ResourceNativeFontImp* Cocos2dFontBuilder::create(ResourceNativeFont* _data)
    {
        return new Cocos2dFont(_data);
    }
    
    void Cocos2dFontBuilder::destroy(ResourceNativeFontImp* imp)
    {
        delete imp;
    }
    
    void Cocos2dFontBuilder::initialise()
    {
        
    }
    
    void Cocos2dFontBuilder::shutdown()
    {
        
    }
    //////////////////////////////////////////////////////////////////////////
	Cocos2dFont::Cocos2dFont(ResourceNativeFont* _data)
		:ResourceNativeFontImp(_data),
		mTexture(nullptr),
		mSize(0),
		mResolution(96),
		mSpaceWidth(0),
		mCursorWidth(3),
		mDistance(0),
		mTabWidth(0),
		mOffsetHeight(0),
		mSubstituteCodePoint(FontCodeType::NotDefined),
		mBold(false),
        mItalic(false),
        m_OffX(0),
        m_OffY(0),
        mTextureSize(1024, 512),
        m_IsFull(false)
	{
	}

	Cocos2dFont::~Cocos2dFont()
	{
		GlyphMap::iterator it = mGlyphInfo.begin();
		while (it != mGlyphInfo.end())
		{
			delete it->second;
			it++;
		}
		mGlyphInfo.clear();

		if (mTexture != nullptr)
		{
			RenderManager::getInstance().destroyTexture(mTexture);
			mTexture = nullptr;
		}

		CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_COME_TO_FOREGROUND);
		CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_COME_TO_BACKGROUND);

		CC_SAFE_RELEASE(mCCFont);
	}

	void Cocos2dFont::deserialization(xml::ElementPtr _node, Version _version)
	{
		xml::ElementEnumerator node = _node->getElementEnumerator();
		while (node.next())
		{
			if (node->getName() == "Property")
			{
				const std::string& key = node->findAttribute("key");
				const std::string& value = node->findAttribute("value");
				// 中文处理
				if (key == "Source") mSource = value;
				else if (key == "Size") mSize = utility::parseInt(value);
				else if (key == "Resolution") mResolution = utility::parseUInt(value);
				else if (key == "SpaceWidth") mSpaceWidth = utility::parseInt(value);
				else if (key == "TabWidth") mTabWidth = utility::parseInt(value);
				else if (key == "OffsetHeight") mOffsetHeight = utility::parseInt(value);
				else if (key == "SubstituteCode") mSubstituteCodePoint = utility::parseInt(value);
				else if (key == "CursorWidth") mCursorWidth = utility::parseInt(value);
				else if (key == "Distance") mDistance = utility::parseInt(value);
				else if (key == "Bold") mBold = utility::parseBool(value);
				else if (key == "Italic") mItalic = utility::parseBool(value);
				else if (key == "TextureSize") mTextureSize = IntSize::parse(value);
			}
		}

		mCCFont = CCNativeFont::create();
		mCCFont->retain();
        mCCFont->setFont(mSource, mSize, mBold);
        
        changeImage(mTextureSize.width, mTextureSize.height);

		CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
			callfuncO_selector(Cocos2dFont::listenBackToForeground),
			EVENT_COME_TO_FOREGROUND,
			NULL);

		CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
			callfuncO_selector(Cocos2dFont::listenForeToBackground),
			EVENT_COME_TO_BACKGROUND,
			NULL);
	}

	void Cocos2dFont::listenBackToForeground(CCObject* _sender)
	{
		m_OffX = 0;
		m_OffY = 0;

		changeImage(mTextureSize.width, mTextureSize.height);
	}

	void Cocos2dFont::listenForeToBackground(CCObject* _sender)
	{
		GlyphMap::iterator it = mGlyphInfo.begin();
		while (it != mGlyphInfo.end())
		{
			delete it->second;
			it++;
		}
		mGlyphInfo.clear();

		if (mTexture) {
			mTexture->destroy();
		}

		m_OffX = 0;
		m_OffY = 0;
	}

	GlyphInfo* Cocos2dFont::loadCharactor(Char _id)
	{
		if (mTexture == nullptr)
		{
			MYGUI_LOG(Error, "invalid Texture");
			return nullptr;
		}
        
		if (m_IsFull || mTexture->getCocos2dTexture() == nullptr)
		{
			m_OffX = 0;
			m_OffY = 0;
            
			changeImage(mTextureSize.width, mTextureSize.height);
            
			m_IsFull = false;
		}
        
        CCGlyph* glyph = new CCGlyph();
        glyph->autorelease();
        
        bool loaded = false;
        
		GlyphInfo* _info = new GlyphInfo;
        
		glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
        unsigned defaultHeight = getDefaultHeight();
        glyph->height = (float)defaultHeight;
		switch(_id) {
            case FontCodeType::Selected:
            {
                glyph->width = 1;
                glyph->buffer.resize(defaultHeight * 2);
                uint16_t* lpDst = (uint16_t*)&glyph->buffer[0];
                
                // 文字高的1点竖条
                for (uint32 y = 0; y < defaultHeight; ++y)
                {
                    *lpDst = FONT_MASK_SELECT;
                    lpDst += 1;
                }
                
                loaded = true;
            }
                break;
            case FontCodeType::SelectedBack:
            {
                glyph->width = 1;
                glyph->buffer.resize(defaultHeight * 2);
                uint16_t* lpDst = (uint16_t*)&glyph->buffer[0];
                
                // 文字高的1点竖条
                for (uint32 y = 0; y < defaultHeight; ++y)
                {
                    *lpDst = FONT_MASK_SELECT_DEACTIVE;
                    lpDst += 1;
                }
                
                loaded = true;
            }
                break;
            case FontCodeType::Cursor:
            {
                glyph->width = (float)mCursorWidth;
                glyph->buffer.resize(mCursorWidth * defaultHeight * 2);
                uint16_t* lpDst = (uint16_t*)&glyph->buffer[0];
                
                for (uint32 y = 0; y < defaultHeight; ++y)
                {
                    for (uint32 x = 0; x < mCursorWidth; ++x)
                    {
                        lpDst[x] = FONT_MASK_CHAR;
                    }
                    lpDst += mCursorWidth;
                }
                
                loaded = true;
            }
                break;
            case FontCodeType::Tab:
                break;
            default:
            {
                if (_id < 0xFFFF)
                {
                    if (mCCFont->loadCharactor(_id, glyph))
                    {
                        loaded = true;
                    }
                }
            }
		}
        
        if (!loaded)
        {
            delete _info;
            return mGlyphInfo[FontCodeType::Space];
        }
        
        glBindTexture(GL_TEXTURE_2D, mTexture->getGLTexture());
        glTexSubImage2D(GL_TEXTURE_2D, 0, m_OffX, m_OffY, (GLsizei)glyph->width, (GLsizei)glyph->height, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, &glyph->buffer[0]);
        
		_info->codePoint = _id;
		_info->uvRect.left = (float)m_OffX / (float)mTextureSize.width;
		_info->uvRect.top = (float)(m_OffY + mOffsetHeight) / (float)mTextureSize.height;
		_info->uvRect.right = (float)(m_OffX + glyph->width) / (float)mTextureSize.width;
		_info->uvRect.bottom = (float)(m_OffY + mOffsetHeight + glyph->height) / (float)mTextureSize.height;
		_info->width = glyph->width;
		_info->height = glyph->height;
		_info->advance = glyph->advance - glyph->bearingX;
		_info->bearingX = glyph->bearingX;
		_info->bearingY = glyph->bearingY;
		mGlyphInfo[_id] = _info;
        
		// MYGUI 选中的兼容效果,宽度设置为0
		if (_id == FontCodeType::Selected || _id == FontCodeType::SelectedBack)
		{
			_info->width = 0.0f;
			_info->uvRect.right = _info->uvRect.left;
		}
        
		m_OffX += (unsigned)glyph->width + 1;
		if (m_OffX > mTextureSize.height - defaultHeight)
		{
			m_OffX = 0;
			m_OffY += defaultHeight + 1;
			if (m_OffY > mTextureSize.height - defaultHeight)
			{
				m_IsFull = true;
			}
		}
        
		return _info;
	}

	GlyphInfo* Cocos2dFont::getGlyphInfo(Char _id)
	{
		GlyphMap::iterator _find = mGlyphInfo.find(_id);

		if (_find == mGlyphInfo.end())
		{
			return loadCharactor(_id);
		}

		return _find->second;
	}

	ITexture* Cocos2dFont::getTextureFont()
	{
		return mTexture;
	}

	int Cocos2dFont:: getDefaultHeight()
	{
		return (int)mCCFont->getDefaultHeight();
	}

	void Cocos2dFont::changeImage(int _Width, int _Height)
	{
		// 纹理大小不够了,没办法只能重画了
		GlyphMap::iterator it = mGlyphInfo.begin();
		while (it != mGlyphInfo.end())
		{
			delete it->second;
			it++;
		}
		mGlyphInfo.clear();

		if (!mTexture) {
			mTexture = (Cocos2dTexture*)RenderManager::getInstance().createTexture(MyGUI::utility::toString((size_t)this, "Cocos2dFont"));
			CCAssert(mTexture != nullptr, "can't alloc texture for font");
		}

		mTexture->createManual(_Width, _Height, TextureUsage::Static | TextureUsage::Write, PixelFormat::L8A8);
		Gui::getInstance().correctTextView();
		MYGUI_LOG(Info, "Alloc Font Texture Buffer");
	}
}
