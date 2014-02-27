#include "RenderBox.h"

using namespace cocos2d;

namespace wraps
{

	RenderBox::RenderBox()
		:mCanvas(nullptr),
		mRenderTarget(nullptr),
		mColour(0, 0, 0, 1),
		mScene(nullptr)
	{
	}

	RenderBox::~RenderBox()
	{
		destroy();
	}

	cocos2d::CCScene* RenderBox::createScene()
	{
		MYGUI_ASSERT(mScene == nullptr, "mScene not null");

		mScene = cocos2d::CCScene::create();
		mScene->retain();
		
		if (mCanvas) mScene->onEnter();

		return mScene;
	}

	void RenderBox::clearScene()
	{
		MYGUI_ASSERT(mScene != nullptr, "mScene is null");
		
		mScene->onExit();
		mScene->release();
		mScene = nullptr;
	}

	void RenderBox::setCanvas(MyGUI::Canvas* _value)
	{
		MYGUI_ASSERT(mCanvas == nullptr, "mCanvas no null");

		mCanvas = _value;
		mCanvas->eventPreTextureChanges += MyGUI::newDelegate(this, &RenderBox::eventPreTextureChanges);
		mCanvas->requestUpdateCanvas = MyGUI::newDelegate(this, &RenderBox::requestUpdateCanvas);
		mCanvas->createTexture(MyGUI::Canvas::TRM_PT_VIEW_REQUESTED, MyGUI::TextureUsage::RenderTarget);

		mCanvas->updateTexture();

		if (mScene)
			mScene->onEnter();
		else
			createScene();
	}

	void RenderBox::destroy()
	{
		if (mScene)
		{
			clearScene();
		}

		frameAdvise(false);

		if (mCanvas)
		{
			mCanvas->destroyTexture();
			mCanvas->eventPreTextureChanges -= MyGUI::newDelegate(this, &RenderBox::eventPreTextureChanges);
			mCanvas->requestUpdateCanvas = nullptr;
			mCanvas = nullptr;
			mRenderTarget = nullptr;
		}
	}

	void RenderBox::setBackgroundColour(const MyGUI::Colour& _value)
	{
		mColour = _value;
	}

	void RenderBox::eventPreTextureChanges(MyGUI::Canvas* _canvas)
	{
		mRenderTarget = nullptr;
	}

	void RenderBox::requestUpdateCanvas(MyGUI::Canvas* _canvas, MyGUI::Canvas::Event _event)
	{
		if (!(_event.textureChanged || _event.requested))
			return;

		mRenderTarget = mCanvas->getTexture()->getRenderTarget();
	}

	void RenderBox::frameAdvise(bool _advise)
	{
		if (_advise)
			MyGUI::Gui::getInstance().eventFrameStart += MyGUI::newDelegate(this, &RenderBox::frameEntered);
		else
			MyGUI::Gui::getInstance().eventFrameStart -= MyGUI::newDelegate(this, &RenderBox::frameEntered);
	}

	void RenderBox::frameEntered(float _time)
	{
		if (!mRenderTarget || !mCanvas || !mCanvas->getVisible() || !mCanvas->getInheritedVisible())
			return;

		mRenderTarget->begin();
        
		/////////////////////////////////////////////////////////////////////////
		GLfloat oldColor[4];
		glGetFloatv(GL_COLOR_CLEAR_VALUE, oldColor);
		glClearColor(mColour.red, mColour.green, mColour.blue, mColour.alpha);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(oldColor[0],oldColor[1],oldColor[2],oldColor[3]);

		///////////////////////////////////////////////////////////////////////////

		//ccDrawLine(cocos2d::CCPoint(5.0f, 5.0f),
		//			cocos2d::CCPoint(float(mCanvas->getWidth() - 5) / CC_CONTENT_SCALE_FACTOR(), float(mCanvas->getHeight() - 5) / CC_CONTENT_SCALE_FACTOR()));
		//ccDrawLine(cocos2d::CCPoint(float(mCanvas->getWidth() / 2) / CC_CONTENT_SCALE_FACTOR(), 0),
		//			cocos2d::CCPoint(float(mCanvas->getWidth() / 2) / CC_CONTENT_SCALE_FACTOR(), float(mCanvas->getHeight() / 2) / CC_CONTENT_SCALE_FACTOR()));

		///////////////////////////////////////////////////////////////////////////

		mScene->visit();

		glFlush();

		mRenderTarget->end();
	}

}