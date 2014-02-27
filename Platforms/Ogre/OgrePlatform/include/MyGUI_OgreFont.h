// �ⲿ�ִ���ο��� ��ת������Blog���� ��MYGUI ʹ�� GDI ��������Ľ��������
// http://blog.sina.com.cn/s/blog_aa0907ae01014ipu.html


#ifndef __MYGUI_COCOS2D_FONT_H__
#define __MYGUI_COCOS2D_FONT_H__

#include "MyGUI_ResourceNativeFont.h"
#include "MyGUI_OgreTexture.h"

namespace MyGUI
{
	class OgreFontBuilder :
		public ResourceNativeFontBuilder
	{
	public:
		virtual ResourceNativeFontImp* create(ResourceNativeFont* _data);
		virtual void destroy(ResourceNativeFontImp*);

		void initialise();
		void shutdown();
	};

	class OgreFont :
		public ResourceNativeFontImp
	{
	public:
		OgreFont(ResourceNativeFont* _data);
		virtual ~OgreFont();

		virtual void deserialization(xml::ElementPtr _node, Version _version);
		virtual GlyphInfo* getGlyphInfo(Char _id);
		virtual ITexture* getTextureFont();
		virtual int getDefaultHeight();

		virtual void initialise() = 0;
		virtual GlyphInfo* loadCharactor(Char _id) = 0;

		void changeImage(int _Width, int _Height);

	protected:
		std::string mSource;
		int mSize;
		bool mBold;
		bool mItalic;
		uint mResolution; // 
		int mSpaceWidth; // �ո�
		int mTabWidth; // TAB
		uint mCursorWidth; // ���
		int mOffsetHeight; // ������
		int mDistance; // ���
		Char mSubstituteCodePoint; // ȱʡֵ
		uint mDefaultHeight; // Ĭ�ϸ߶�

		typedef std::map<Char, GlyphInfo*> GlyphMap;
		GlyphMap mGlyphInfo;
		OgreTexture* mTexture;
	};

}

#endif // __MYGUI_COCOS2D_FONT_H__