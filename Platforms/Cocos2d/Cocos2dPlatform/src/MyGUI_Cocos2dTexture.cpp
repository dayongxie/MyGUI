#include "MyGUI_Cocos2dTexture.h"
#include "MyGUI_Cocos2dRenderManager.h"
#include "MyGUI_Cocos2dRTTexture.h"
#include "MyGUI_Cocos2dDiagnostic.h"
#include "MyGUI_DataManager.h"
#include "MyGUI_Timer.h"

#include <cocos2d.h>

using namespace cocos2d;

unsigned long ccNextPOT(unsigned long x)
{
	x = x - 1;
	x = x | (x >> 1);
	x = x | (x >> 2);
	x = x | (x >> 4);
	x = x | (x >> 8);
	x = x | (x >>16);
	return x + 1;
}

namespace MyGUI
{
	Cocos2dTexture::Cocos2dTexture(const std::string& _name)
		:mTexture(nullptr),
		mName(_name),
		mRenderTarget(nullptr),
		mInvalidateListener(nullptr),
		mLock(false),
		mBuffer(nullptr)
	{
	}

	Cocos2dTexture::~Cocos2dTexture()
	{
		destroy();
	}

	int Cocos2dTexture::getContentWidth()
	{
		return mTexture ? int(mTexture->getContentSizeInPixels().width) : 0;
	}

	int Cocos2dTexture::getContentHeight()
	{
		return mTexture ? int(mTexture->getContentSizeInPixels().height) : 0;
	}

	int Cocos2dTexture::getWidth()
	{
		return mTexture ? mTexture->getPixelsWide() : 0;
	}

	int Cocos2dTexture::getHeight()
	{
		return mTexture ? mTexture->getPixelsHigh() : 0;
	}

	void Cocos2dTexture::setInvalidateListener(ITextureInvalidateListener* _listener)
	{
		mInvalidateListener = _listener;
	}

	void Cocos2dTexture::createManual(int _width, int _height, TextureUsage _usage, PixelFormat _format)
	{
		if (mTexture)
			mTexture->release();
        
		unsigned long POTWide = ccNextPOT(_width);
		unsigned long POTHigh = ccNextPOT(_height);

        mTexture = new CCTexture2D();
        if (!mTexture)
				return;

		setFormat(_format);
		
		void *data = calloc(POTWide * POTHigh * getByteForPixFormat(mPixFormat), 1);
		if (!data)
		{
			CCLOG("Cocos2dTexture: createManual: not enough memory.");
			mTexture->release();
			mTexture = nullptr;
			return;
		}

		mTexture->initWithData(data, convertFormat(_format), POTWide, POTHigh, CCSize(float(_width), float(_height)));
		free(data);
	}

	void Cocos2dTexture::loadFromFile(const std::string& _filename)
	{
		if (mTexture)
			mTexture->release();
		
		const std::string& path = DataManager::getInstance().getDataPath(_filename).c_str();
		mTexture = CCTextureCache::sharedTextureCache()->addImage(path.c_str());

		if (mTexture)
		{
			mTexture->retain();

			setFormat(convertFormat(mTexture->getPixelFormat()));
		} else {
			CCLOG("Cocos2dTexture::loadFromFile: can't load image %s\n", DataManager::getInstance().getDataPath(_filename).c_str());
		}
	}

	void Cocos2dTexture::saveToFile(const std::string& _filename)
	{

	}

	void Cocos2dTexture::destroy()
	{
		if (!mTexture) return;

		if (mLock)
		{
			unlock();
		}

		mTexture->release();
		mTexture = nullptr;

		if (mBuffer)
		{
				delete[] mBuffer;
				mBuffer = nullptr;
		}

		removeRenderTarget();
	}

	void* Cocos2dTexture::lock(TextureUsage _access)
	{
		if (!mTexture)
		{
			MYGUI_PLATFORM_LOG(Info, "Cocos2dTexture::lock mTexture is NULL");
			return nullptr;
		}

		if (isLocked())
		{
			return nullptr;
		}

		mLock = true;
		mAccess = _access;

		if (mAccess == TextureUsage::RenderTarget)
			return mRenderTarget;

		mBuffer = new unsigned char[getWidth() * getHeight() * mNumElemBytes];
		{
			//TODO unfinished
			GLuint fbo;
			GLint oldFBO;
			glGenFramebuffers(1, &fbo);
			glGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldFBO);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, getGLTexture(), 0);
			glReadPixels(0, 0, getWidth(), getHeight(), getGLFormat(), GL_UNSIGNED_BYTE, mBuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, oldFBO);
			glDeleteFramebuffers(1, &fbo);
		}

		return mBuffer;
	}

	void Cocos2dTexture::unlock()
	{
		if (!isLocked())
			return;

		if (mAccess.isValue(TextureUsage::Write))
		{
			GLint oldTexture;
			glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldTexture);
			glBindTexture(GL_TEXTURE_2D, getGLTexture());
			GLenum format = getGLFormat();
			glTexImage2D(GL_TEXTURE_2D, 0, format, getWidth(), getHeight(), 0, format, GL_UNSIGNED_BYTE, mBuffer);
			glBindTexture(GL_TEXTURE_2D, oldTexture);
		}

		if (mBuffer) {
			delete[] mBuffer;
			mBuffer = nullptr;
		}

		mLock = false;
		mAccess = TextureUsage::Default;
	}

	bool Cocos2dTexture::isLocked()
	{
		return mLock;
	}

	IRenderTarget* Cocos2dTexture::getRenderTarget()
	{
		if (mRenderTarget == nullptr)
			mRenderTarget = new Cocos2dRTTexture(this);

		return mRenderTarget;
	}

	void Cocos2dTexture::removeRenderTarget()
	{
		if (mRenderTarget)
		{
			delete mRenderTarget;
			mRenderTarget = nullptr;
		}
	}

	void Cocos2dTexture::setFormat(PixelFormat _format)
	{
		mPixFormat = _format;

		mNumElemBytes = getByteForPixFormat(mPixFormat);
	}

	size_t Cocos2dTexture::getByteForPixFormat(PixelFormat _format)
	{
		size_t iRet = 0;

		if (_format == PixelFormat::L8)
			iRet = 1;
		else if (_format == PixelFormat::L8A8)
			iRet = 2;
		else if (_format == PixelFormat::R8G8B8)
			iRet = 3;
		else if (_format == PixelFormat::R8G8B8A8)
			iRet = 4;

		return iRet;
	}


	CCTexture2DPixelFormat Cocos2dTexture::convertFormat(PixelFormat _format)
	{
		CCTexture2DPixelFormat format = kCCTexture2DPixelFormat_Default;

		if (_format == PixelFormat::L8)
			format = kCCTexture2DPixelFormat_I8;
		else if (_format == PixelFormat::L8A8)
			format = kCCTexture2DPixelFormat_AI88 ;
		else if (_format == PixelFormat::R8G8B8)
			format = kCCTexture2DPixelFormat_RGB888 ;
		else if (_format == PixelFormat::R8G8B8A8)
			format = kCCTexture2DPixelFormat_RGBA8888 ;

		return format;
	}

	PixelFormat Cocos2dTexture::convertFormat(CCTexture2DPixelFormat _format)
	{
		PixelFormat format = PixelFormat::Unknow;
		switch (_format)
		{
		case kCCTexture2DPixelFormat_I8:
			format = PixelFormat::L8;
			break;
		case kCCTexture2DPixelFormat_AI88:
			format = PixelFormat::L8A8;
			break;
		case kCCTexture2DPixelFormat_RGB888:
			format = PixelFormat::R8G8B8;
			break;
		case kCCTexture2DPixelFormat_RGBA8888:
			format = PixelFormat::R8G8B8A8;
			break;
        default:
                break;
		}

		return format;
	}

	GLenum Cocos2dTexture::getGLFormat()
	{
		GLenum format = GL_RGBA;
		if (mPixFormat == PixelFormat::L8)
			format = GL_LUMINANCE;
		else if (mPixFormat == PixelFormat::L8A8)
			format = GL_LUMINANCE_ALPHA ;
		else if (mPixFormat == PixelFormat::R8G8B8)
			format = GL_RGB;
		else if (mPixFormat == PixelFormat::R8G8B8A8)
			format = GL_RGBA;

		return format;
	}

	GLuint Cocos2dTexture::getGLTexture()
	{
		if (!mTexture) return 0;

		return mTexture->getName();
	}

	cocos2d::CCTexture2D* Cocos2dTexture::getCocos2dTexture()
	{
		return mTexture;
	}

	void Cocos2dTexture::setCocos2dTexture(cocos2d::CCTexture2D *_value)
	{
		mTexture = _value;
	}
}
