#ifndef __MYGUI_RESOURCE_NATIVE_FONT_H
#define __MYGUI_RESOURCE_NATIVE_FONT_H

#include "MyGUI_Singleton.h"
#include "MyGUI_IFont.h"

namespace MyGUI
{
	class ResourceNativeFont;
	class MYGUI_EXPORT ResourceNativeFontImp
	{
	public:
		ResourceNativeFontImp(ResourceNativeFont* _data)
		{
			pData = _data;
		}
        virtual ~ResourceNativeFontImp() {}

		virtual void deserialization(xml::ElementPtr _node, Version _version) = 0;

		virtual GlyphInfo* getGlyphInfo(Char _id) = 0;

		virtual ITexture* getTextureFont() = 0;

		virtual int getDefaultHeight() = 0;

		ResourceNativeFont* pData;
	};

	class MYGUI_EXPORT ResourceNativeFontBuilder
		: public Singleton<ResourceNativeFontBuilder>
	{
	public:
		virtual ResourceNativeFontImp* create(ResourceNativeFont* _data) = 0;
		virtual void destroy(ResourceNativeFontImp*) = 0;
	};

	class ResourceManager;
	class MYGUI_EXPORT ResourceNativeFont :
		public IFont
	{
		MYGUI_RTTI_DERIVED( ResourceNativeFont )
	public:
		ResourceNativeFont();
		~ResourceNativeFont();

		virtual void deserialization(xml::ElementPtr _node, Version _version);

		virtual GlyphInfo* getGlyphInfo(Char _id);

		virtual ITexture* getTextureFont();

		virtual int getDefaultHeight();

	private:
		ResourceNativeFontImp* mImp;
	};
};

#endif // __MYGUI_RESOURCE_NATIVE_FONT_H
