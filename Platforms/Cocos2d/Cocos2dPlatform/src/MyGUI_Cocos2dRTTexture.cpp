#include "MyGUI_Cocos2dRTTexture.h"
#include "MyGUI_Cocos2dDiagnostic.h"
#include "MyGUI_Cocos2dTexture.h"
#include "MyGUI_Cocos2dVertexBuffer.h"
#include "MyGUI_Cocos2dRenderManager.h"

#include <CCGL.h>

using namespace cocos2d;

namespace MyGUI
{
	Cocos2dRTTexture::Cocos2dRTTexture(Cocos2dTexture *_texture)
		:mTexture(_texture)
	{
		if (mTexture)
		{
			mRTInfo.maximumDepth = 1.0f;
			mRTInfo.hOffset = 0;
			mRTInfo.vOffset = 0;
			mRTInfo.aspectCoef = -float(mTexture->getHeight()) / float(mTexture->getWidth());
			mRTInfo.pixWidth = float(mTexture->getWidth());
			mRTInfo.pixHeight = float(mTexture->getHeight());

			glGetIntegerv(GL_FRAMEBUFFER_BINDING, &mOldFBO);
			glGenFramebuffers(1, &mFBO);

			mShaderProgram = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor);
		}
	}

	Cocos2dRTTexture::~Cocos2dRTTexture()
	{
		if (mFBO != 0)
		{
			glDeleteFramebuffers(1, &mFBO);
			mFBO = 0;
		}
	}

	void Cocos2dRTTexture::begin()
	{
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &mOldFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
		mTexture->lock(TextureUsage::RenderTarget);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture->getGLTexture(), 0);


		kmGLPushMatrix();
		kmGLLoadIdentity();
		kmMat4 orthoMatrix;
		kmMat4OrthographicProjection(&orthoMatrix, -1.0f, 1.0f, 1.0f, -1.0f, -1, 1 );
		kmGLMultMatrix(&orthoMatrix);

		//CCDirector::sharedDirector()->getOpenGLView()->setViewPortInPoints(0, 0, mTexture->getWidth(), mTexture->getHeight());
		glViewport(0, 0, mTexture->getWidth(), mTexture->getHeight());
	}

	void Cocos2dRTTexture::end()
	{
		CCDirector::sharedDirector()->getOpenGLView()->setViewPortInPoints(
			0, 0,
			(GLsizei)CCDirector::sharedDirector()->getWinSizeInPixels().width,
			(GLsizei)CCDirector::sharedDirector()->getWinSizeInPixels().height
			);

		kmGLPopMatrix();

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
		mTexture->unlock();
		glBindFramebuffer(GL_FRAMEBUFFER, mOldFBO);
	}

	void Cocos2dRTTexture::doRender(IVertexBuffer* _buffer, ITexture* _texture, size_t _count)
	{
		mShaderProgram->use();
		mShaderProgram->setUniformsForBuiltins();

		ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
		ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Cocos2dVertexBuffer* buffer = static_cast<Cocos2dVertexBuffer*>(_buffer);
		unsigned int buffer_id = buffer->getBufferID();
		MYGUI_PLATFORM_ASSERT(buffer_id, "Vertex buffer is not created");

		unsigned int texture_id = 0;
		if (_texture)
		{
			Cocos2dTexture* texture = static_cast<Cocos2dTexture*>(_texture);
			texture_id = texture->getGLTexture();
			//MYGUI_PLATFORM_ASSERT(texture_id, "Texture is not created");
		}

		ccGLBindTexture2D(texture_id);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);

		glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));
		glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));
		glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u));

		glDrawArrays(GL_TRIANGLES, 0, _count);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	const RenderTargetInfo& Cocos2dRTTexture::getInfo()
	{
		return mRTInfo;
	}
}