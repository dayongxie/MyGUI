#include "MyGUI_OgreFont.h"
#include "MyGUI_RenderManager.h"
#include "MyGUI_Gui.h"

namespace MyGUI
{

	OgreFont::OgreFont(ResourceNativeFont* _data)
		:ResourceNativeFontImp(_data),
		mTexture(nullptr),
		mSize(0),
		mResolution(96),
		mSpaceWidth(0),
		mCursorWidth(1),
		mDistance(0),
		mTabWidth(0),
		mOffsetHeight(0),
		mSubstituteCodePoint(FontCodeType::NotDefined),
		mDefaultHeight(0),
		mBold(false),
		mItalic(false)
	{
	}

	OgreFont::~OgreFont()
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
	}

	void OgreFont::deserialization(xml::ElementPtr _node, Version _version)
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
			}
		}

		initialise();
	}

	GlyphInfo* OgreFont::getGlyphInfo(Char _id)
	{
		GlyphMap::iterator _find = mGlyphInfo.find(_id);

		if (_find == mGlyphInfo.end())
		{
			return loadCharactor(_id);
		}

		return _find->second;
	}

	ITexture* OgreFont::getTextureFont()
	{
		return mTexture;
	}

	int OgreFont:: getDefaultHeight()
	{
		return mDefaultHeight;
	}

	void OgreFont::changeImage(int _Width, int _Height)
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
			mTexture = (OgreTexture*)RenderManager::getInstance().createTexture(MyGUI::utility::toString((size_t)this, "OgreFont"));
			MYGUI_ASSERT(mTexture != nullptr, "can't alloc texture for font");
		}
		mTexture->destroy();
		mTexture->createManual(_Width, _Height, TextureUsage::Static | TextureUsage::Write, PixelFormat::R8G8B8A8);

		uint8* texBuffer = static_cast<uint8*>(mTexture->lock(TextureUsage::Write));

		if (texBuffer != nullptr)
		{
			// Make the texture background transparent white.
			for (unsigned i = 0; i < _Width * _Height * 4; ++i)
			{
				texBuffer[i] = 0;
			}

			mTexture->unlock();
		}

		Gui::getInstance().correctTextView();
		MYGUI_LOG(Info, "Alloc Font Texture Buffer");
	}
}