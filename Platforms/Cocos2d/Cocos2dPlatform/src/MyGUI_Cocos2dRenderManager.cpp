/*!
	@file
	@author		
	@date		
*/

#include "MyGUI_Cocos2dRenderManager.h"
#include "MyGUI_Cocos2dDiagnostic.h"
#include "MyGUI_Cocos2dTexture.h"
#include "MyGUI_Cocos2dVertexBuffer.h"
#include "MyGUI_LayerManager.h"
#include "MyGUI_ILayerNode.h"

#include "MyGUI_Gui.h"

#include <CCGL.h>

using namespace cocos2d;

static int vbo_count = 0;
static int vertex_count = 0;

namespace MyGUI
{
	Cocos2dRenderManager::Cocos2dRenderManager() :
		mUpdate(false),
		mIsInitialise(false),
		vertex_pf(0),
		vbo_pf(0)
	{
	}

	Cocos2dRenderManager::~Cocos2dRenderManager()
	{
	}

	void Cocos2dRenderManager::initialise()
	{
		CCDirector *pDirector = CCDirector::sharedDirector();
		MYGUI_PLATFORM_ASSERT(!mIsInitialise, getClassTypeName() << " initialised twice");
		MYGUI_PLATFORM_LOG(Info, "* Initialise: " << getClassTypeName());

		CCSize s = pDirector->getWinSizeInPixels();

		this->setPosition(0, 0);
		this->setContentSize(s);
		setViewSize(int(s.width), int(s.height));

		// 绑定到cocos2d节点
		pDirector->setNotificationNode(this);

		mInfo.pixWidth = s.width;
		mInfo.pixHeight = s.height;

		mVertexFormat = VertexColourType::ColourABGR;

		mUpdate = true;

		kmMat4 tmp;
		kmGLGetMatrix(KM_GL_PROJECTION, &tmp);
		kmMat4Inverse(&mMatrix, &tmp);

		MYGUI_PLATFORM_LOG(Info, getClassTypeName() << " successfully initialized");
		mIsInitialise = true;

		CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
			callfuncO_selector(Cocos2dRenderManager::listenForeToBackground),
			EVENT_COME_TO_BACKGROUND,
			NULL);
		pDirector->getScheduler()->scheduleUpdateForTarget(this, kCCPriorityNonSystemMin, false);
	}

	void Cocos2dRenderManager::shutdown()
	{
		MYGUI_PLATFORM_ASSERT(mIsInitialise, getClassTypeName() << " is not initialised");
		MYGUI_PLATFORM_LOG(Info, "* Shutdown: " << getClassTypeName());

		CCDirector *pDirector = CCDirector::sharedDirector();
		pDirector->getScheduler()->unscheduleUpdateForTarget(this);

		// 注意  (maybe）CCNotificationCenter的生命周期在mainloop结束之前就结束了
		CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_COME_TO_BACKGROUND);


		// 解除与cocos2d节点的绑定
		pDirector->setNotificationNode(NULL);

		destroyAllResources();

		MYGUI_PLATFORM_LOG(Info, getClassTypeName() << " successfully shutdown");
		mIsInitialise = false;
	}

	IVertexBuffer* Cocos2dRenderManager::createVertexBuffer()
	{
		return new Cocos2dVertexBuffer();
	}

	/** Destroy vertex buffer */
	void Cocos2dRenderManager::destroyVertexBuffer(IVertexBuffer* _buffer)
	{
		delete _buffer;
	}

	void Cocos2dRenderManager::begin()
	{
		kmGLMatrixMode(KM_GL_PROJECTION);
		kmGLPushMatrix();

		//kmGLLoadIdentity();

		//kmMat4 mat;
		//kmGLGetMatrix(KM_GL_PROJECTION, &mat);
		//mat.mat[0] = 600;
		//mat.mat[5] = 600;
		//kmGLLoadMatrix(&mat);

		kmGLMatrixMode(KM_GL_MODELVIEW);
		kmGLPushMatrix();

		//kmGLLoadIdentity();

		//kmGLGetMatrix(KM_GL_MODELVIEW, &mat);
		//mat.mat[12] = 0;
		//mat.mat[13] = 0;
		//mat.mat[15] = 0;
		//kmGLLoadMatrix(&mat);
	}

	void Cocos2dRenderManager::end()
	{
		kmGLMatrixMode(KM_GL_PROJECTION);
		kmGLPopMatrix();

		kmGLMatrixMode(KM_GL_MODELVIEW);
		kmGLPopMatrix();
	}

	void Cocos2dRenderManager::visit()
	{
		CCNode::visit();
	}

	void Cocos2dRenderManager::draw()
	{
		vbo_count = 0;
		vertex_count = 0;

		begin();
		if (mUpdate)
		{
			mUpdate = false;
			onRenderToTarget(this, true);
		}
		else
			onRenderToTarget(this, false);
		end();

		if (vbo_count > 0)
		{
			vbo_pf = vbo_count;
			vertex_pf = vertex_count;
		}
		//CCGLProgram *program = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_Position_uColor);
		//program->use();
		//program->setUniformsForBuiltins();
		//static ccColor4F s_tColor = {1.0f,1.0f,1.0f,1.0f};
		//program->setUniformLocationWith4fv(1, (GLfloat*) &s_tColor.r, 1);

		//ccVertex3F vertices[2] = {
		//	{0, 0, -1024},
		//	{1024, 768, 1024}
		//};

		//ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
		//glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, 0, vertices);
		//glDrawArrays(GL_LINES, 0, 2);
	}

	void Cocos2dRenderManager::doRender(IVertexBuffer* _buffer, ITexture* _texture, size_t _count)
	{
		Cocos2dVertexBuffer* buffer = static_cast<Cocos2dVertexBuffer*>(_buffer);
		unsigned int buffer_id = buffer->getBufferID();

		unsigned int texture_id = 0;
		Cocos2dTexture* texture = static_cast<Cocos2dTexture*>(_texture);
		texture_id = texture->getGLTexture();

		//MYGUI_PLATFORM_ASSERT(buffer_id, "Texture is not created");
		//MYGUI_PLATFORM_ASSERT(texture_id, "Texture is not created");
		if (!buffer_id) return;
		if (!texture_id) return;

		ccGLEnable(m_eGLServerState);

		CCGLProgram* shaderProgram = NULL;
		cocos2d::ccBlendFunc blendFunc;

		shaderProgram = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor_MyGUI);
		// 对于
		if (texture->getCocos2dTexture()->hasPremultipliedAlpha())
		{
			blendFunc.src = CC_BLEND_SRC;
			blendFunc.dst = CC_BLEND_DST;
		}
		else
		{
			blendFunc.src = GL_SRC_ALPHA;
			blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
		}

		shaderProgram->use();
		shaderProgram->setUniformsForBuiltins();
		ccGLBlendFunc(blendFunc.src, blendFunc.dst);

		ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );

		ccGLBindTexture2D(texture_id);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);

		glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));
		glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));
		glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u));

		glDrawArrays(GL_TRIANGLES, 0, _count);

		vbo_count++;
		vertex_count += _count;

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	const RenderTargetInfo& Cocos2dRenderManager::getInfo()
	{
		return mInfo;
	}

	const IntSize& Cocos2dRenderManager::getViewSize() const
	{
		return mViewSize;
	}

	VertexColourType Cocos2dRenderManager::getVertexFormat()
	{
		return mVertexFormat;
	}

	void Cocos2dRenderManager::update(float delayTime)
	{
		if (!mIsInitialise)
			return;

		onFrameEvent(delayTime);
	}

	void Cocos2dRenderManager::setViewSize(int _width, int _height)
	{
		if (_height == 0)
			_height = 1;
		if (_width == 0)
			_width = 1;

		mViewSize.set(_width, _height);

		onResizeView(mViewSize);
		mUpdate = true;
	}
	
	ITexture* Cocos2dRenderManager::createTexture(const std::string& _name)
	{
		MapTexture::const_iterator item = mTextures.find(_name);
		MYGUI_PLATFORM_ASSERT(item == mTextures.end(), "Texture '" << _name << "' already exist");

		Cocos2dTexture* texture = new Cocos2dTexture(_name);
		mTextures[_name] = texture;
		return texture;
	}

	void Cocos2dRenderManager::destroyTexture(ITexture* _texture)
	{
		if (_texture == nullptr)
			return;

		MapTexture::iterator item = mTextures.find(_texture->getName());
		MYGUI_PLATFORM_ASSERT(item != mTextures.end(), "Texture '" << _texture->getName() << "' not found");

		mTextures.erase(item);
		delete _texture;
	}

	ITexture* Cocos2dRenderManager::getTexture(const std::string& _name)
	{
		MapTexture::const_iterator item = mTextures.find(_name);
		if (item == mTextures.end())
			return nullptr;
		return item->second;
	}

	void Cocos2dRenderManager::destroyAllResources()
	{
		for (MapTexture::const_iterator item = mTextures.begin(); item != mTextures.end(); ++item)
		{
			delete item->second;
		}
		mTextures.clear();
	}

	void Cocos2dRenderManager::listenForeToBackground(CCObject *obj)
	{
		releaseAllVertexBuffer();
		invalidateRender();
	}

	void Cocos2dRenderManager::invalidateRender()
	{
		mUpdate = true;
	}

	void Cocos2dRenderManager::releaseAllVertexBuffer()
	{
		LayerManager* layers = LayerManager::getInstancePtr();
		if (layers != nullptr)
		{
			LayerManager::EnumeratorLayer layer = layers->getEnumerator();
			while (layer.next())
			{
				EnumeratorILayerNode layerNode = layer->getEnumerator();
				while (layerNode.next())
				{
					layerNode->releaseVertexBuffer();
				}
			}
		}
	}

	MapString Cocos2dRenderManager::getStatistic()
	{
		MapString info;

		info["vbo"] = utility::toString(vbo_pf);
		info["trangle"] = utility::toString(vertex_pf / 3);

		return info;
	}
}