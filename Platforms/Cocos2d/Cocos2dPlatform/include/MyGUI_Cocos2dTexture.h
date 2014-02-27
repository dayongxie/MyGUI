/*!
	@file
	@author		Albert Semenov
	@date		04/2009
*/

#ifndef __MYGUI_COCOS2D_TEXTURE_H__
#define __MYGUI_COCOS2D_TEXTURE_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_ITexture.h"
#include "MyGUI_RenderFormat.h"

#include <cocos2d.h>

namespace MyGUI
{

	class Cocos2dTexture :
		public ITexture
	{
	public:
		Cocos2dTexture(const std::string& _name);
		virtual ~Cocos2dTexture();

		virtual const std::string& getName() const { return mName; }

		virtual void createManual(int _width, int _height, TextureUsage _usage, PixelFormat _format);
		virtual void loadFromFile(const std::string& _filename);
		virtual void saveToFile(const std::string& _filename);

		virtual void setInvalidateListener(ITextureInvalidateListener* _listener);

		virtual void destroy();

		virtual void* lock(TextureUsage _access);
		virtual void unlock();
		virtual bool isLocked();

		virtual int getWidth();
		virtual int getHeight();
		virtual int getContentWidth();
		virtual int getContentHeight();

		virtual PixelFormat getFormat()
		{
			return mPixFormat;
		}
		virtual TextureUsage getUsage()
		{
			return mUsage;
		}
		virtual size_t getNumElemBytes()
		{
			return mNumElemBytes;
		}

		virtual IRenderTarget* getRenderTarget();
		void removeRenderTarget();

		GLuint getGLTexture();

		cocos2d::CCTexture2D* getCocos2dTexture();

		void setCocos2dTexture(cocos2d::CCTexture2D *_value);

		static cocos2d::CCTexture2DPixelFormat convertFormat(PixelFormat _format);
		static PixelFormat convertFormat(cocos2d::CCTexture2DPixelFormat _format);
		GLenum getGLFormat();

		static size_t getByteForPixFormat(PixelFormat _format);
	private:
		void setUsage(TextureUsage _usage);
		void setFormat(PixelFormat _format);
		void setFormatByCocos2dTexture();

		//virtual void loadResource(Ogre::Resource* resource);

	private:
		cocos2d::CCTexture2D *mTexture;
		std::string mName;

		TextureUsage mUsage;
		TextureUsage mAccess;

		PixelFormat mPixFormat;
		size_t mNumElemBytes;

		IRenderTarget* mRenderTarget;
		ITextureInvalidateListener* mInvalidateListener;

		unsigned char *mBuffer;
		bool mLock;
	};

} // namespace MyGUI

#endif // __MYGUI_COCOS2D_TEXTURE_H__
