#include "MyGUI_Precompiled.h"
#include "MyGUI_ResourceNativeFont.h"

namespace MyGUI
{

	template <> ResourceNativeFontBuilder* Singleton<ResourceNativeFontBuilder>::msInstance = nullptr;
	template <> const char* Singleton<ResourceNativeFontBuilder>::mClassTypeName("ResourceNativeFontBuilder");

	ResourceNativeFont::ResourceNativeFont()
	{
		mImp = ResourceNativeFontBuilder::getInstance().create(this);
	}

	ResourceNativeFont::~ResourceNativeFont()
	{
		ResourceNativeFontBuilder::getInstance().destroy(mImp);
	}

	void ResourceNativeFont::deserialization(xml::ElementPtr _node, Version _version)
	{
		mImp->deserialization(_node, _version);
	}

	GlyphInfo* ResourceNativeFont::getGlyphInfo(Char _id)
	{
		return mImp->getGlyphInfo(_id);
	}

	ITexture* ResourceNativeFont::getTextureFont()
	{
		return mImp->getTextureFont();
	}


	int ResourceNativeFont::getDefaultHeight()
	{
		return mImp->getDefaultHeight();
	}
}