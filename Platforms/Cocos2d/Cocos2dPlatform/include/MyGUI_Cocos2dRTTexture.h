#ifndef __MYGUI_COCOS2D_RTTEXTURE_H__
#define __MYGUI_COCOS2D_RTTEXTURE_H__

#include "MyGUI_IRenderTarget.h"
#include <cocos2d.h>

namespace MyGUI
{
	class Cocos2dTexture;
	class Cocos2dRTTexture :
		public IRenderTarget
	{
	public:
		Cocos2dRTTexture(Cocos2dTexture *_texture);
		virtual ~Cocos2dRTTexture();

		virtual void begin();
		virtual void end();

		virtual void doRender(IVertexBuffer* _buffer, ITexture* _texture, size_t _count);
		virtual const RenderTargetInfo& getInfo();

	private:
		Cocos2dTexture *mTexture;

		GLuint				mFBO;
		GLint				mOldFBO;
		RenderTargetInfo	mRTInfo;
		cocos2d::CCGLProgram *mShaderProgram;
	};
}

#endif // __MYGUI_COCOS2D_RTTEXTURE_H__