/*!
	@file
	@author		
	@date		
*/

#ifndef __MYGUI_COCOS2D_RENDERMANAGER_H__
#define __MYGUI_COCOS2D_RENDERMANAGER_H__

#include "MyGUI_RenderManager.h"
#include "MyGUI_IRenderTarget.h"
#include <base_nodes/CCNode.h>

namespace MyGUI
{
	class Cocos2dRenderManager :
		public cocos2d::CCNode,
		public RenderManager,
		public IRenderTarget
	{
	public:
		Cocos2dRenderManager();
		virtual ~Cocos2dRenderManager();

		void initialise();
		void shutdown();

		/** @see OpenGLRenderManager::getViewSize */
		virtual const IntSize& getViewSize() const;

		/** @see OpenGLRenderManager::getVertexFormat */
		virtual VertexColourType getVertexFormat();

		/** @see OpenGLRenderManager::createVertexBuffer */
		virtual IVertexBuffer* createVertexBuffer();
		/** @see OpenGLRenderManager::destroyVertexBuffer */
		virtual void destroyVertexBuffer(IVertexBuffer* _buffer);

		/** @see OpenGLRenderManager::createTexture */
		virtual ITexture* createTexture(const std::string& _name);
		/** @see OpenGLRenderManager::destroyTexture */
		virtual void destroyTexture(ITexture* _texture);
		/** @see OpenGLRenderManager::getTexture */
		virtual ITexture* getTexture(const std::string& _name);


		/** @see IRenderTarget::begin */
		virtual void begin();
		/** @see IRenderTarget::end */
		virtual void end();
		/** @see IRenderTarget::doRender */
		virtual void doRender(IVertexBuffer* _buffer, ITexture* _texture, size_t _count);
		/** @see IRenderTarget::getInfo */
		virtual const RenderTargetInfo& getInfo();

	/*internal:*/
		virtual void visit();
		virtual void draw();
		virtual void update(float delayTime);
		void setViewSize(int _width, int _height);

		void releaseAllVertexBuffer();

		MapString getStatistic();

		void listenForeToBackground(CCObject *obj);
		void invalidateRender();
	private:
		void destroyAllResources();
		
	private:
		IntSize mViewSize;
		bool mUpdate;
		VertexColourType mVertexFormat;
		RenderTargetInfo mInfo;

		typedef std::map<std::string, ITexture*> MapTexture;
		MapTexture mTextures;

		kmMat4 mMatrix;

		bool mIsInitialise;

		int vbo_pf;
		int vertex_pf;
	};
}
#endif //__MYGUI_COCOS2D_RENDERMANAGER_H__