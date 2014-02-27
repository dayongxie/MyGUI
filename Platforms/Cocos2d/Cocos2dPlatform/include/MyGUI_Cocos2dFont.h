// -*- coding: utf-8 -*-
// 这部分代码参考了 回转工作室Blog文章 《MYGUI 使用 GDI 字体的中文解决方案》
// http://blog.sina.com.cn/s/blog_aa0907ae01014ipu.html


#ifndef __MYGUI_COCOS2D_FONT_H__
#define __MYGUI_COCOS2D_FONT_H__

#include "MyGUI_ResourceNativeFont.h"
#include "MyGUI_Cocos2dTexture.h"
#include <platform/CCNativeFont.h>

namespace MyGUI
{
	class Cocos2dFontBuilder :
		public ResourceNativeFontBuilder
	{
	public:
		virtual ResourceNativeFontImp* create(ResourceNativeFont* _data);
		virtual void destroy(ResourceNativeFontImp*);

		void initialise();
		void shutdown();
	};

	class Cocos2dFont :
		public cocos2d::CCObject,
		public ResourceNativeFontImp
	{
	public:
		Cocos2dFont(ResourceNativeFont* _data);
		virtual ~Cocos2dFont();

		virtual void deserialization(xml::ElementPtr _node, Version _version);
		virtual GlyphInfo* getGlyphInfo(Char _id);
		virtual ITexture* getTextureFont();
		virtual int getDefaultHeight();
        
        GlyphInfo* loadCharactor(Char _id);
        
		void changeImage(int _Width, int _Height);
		void listenBackToForeground(CCObject* _sender);
		void listenForeToBackground(CCObject* _sender);
	protected:
		std::string mSource;
		int mSize;
		bool mBold;
		bool mItalic;
		uint mResolution; // 
		int mSpaceWidth; // 空格
		int mTabWidth; // TAB
		uint mCursorWidth; // 光标
		int mOffsetHeight; // 上下文
		int mDistance; // 间距
		Char mSubstituteCodePoint; // 缺省值

		typedef std::map<Char, GlyphInfo*> GlyphMap;
		GlyphMap mGlyphInfo;
		Cocos2dTexture* mTexture;
        
        cocos2d::CCNativeFont* mCCFont;
        
		unsigned int m_OffX;
		unsigned int m_OffY;
		bool m_IsFull;
        IntSize mTextureSize;
	};

}

#endif // __MYGUI_COCOS2D_FONT_H__
