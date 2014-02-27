/*!
	@file
	@author     Albert Semenov
	@date       08/2008
*/
#include "Precompiled.h"
#include "DemoKeeper.h"
#include "Base/Main.h"
#include "MyGUI_FontManager.h"
#include "FileSystemInfo.h"

#ifdef MYGUI_COCOS2D_PLATFORM
#include "MyGUI_Cocos2dTexture.h"
#include "MyGUI_Cocos2dVertexBuffer.h"
#include "HelloWorldScene.h"

#include "Cocos2d/RenderBox/RenderBox.h"

namespace demo
{
	std::vector<wraps::RenderBox*> mRenderBoxes;
}
USING_NS_CC;

#endif // MYGUI_COCOS2D_PLATFORM


namespace demo
{

	DemoKeeper::DemoKeeper() :
		mEditorWindow(nullptr),
		mMainPanel(nullptr),
		mInformationWindow(nullptr),
		mColourWindow(nullptr)
	{
	}

	void DemoKeeper::setupResources()
	{
		base::BaseManager::setupResources();
		addResourceLocation(getRootMedia() + "/Demos/Demo_Gui");
		addResourceLocation(getRootMedia() + "/Common/Scene");
		addResourceLocation(getRootMedia() + "/Common/Demos");
	}

	void DemoKeeper::createScene()
	{
		//MyGUI::LayoutManager::getInstance().loadLayout("Wallpaper.layout");

		//const MyGUI::VectorWidgetPtr& root = MyGUI::LayoutManager::getInstance().loadLayout("HelpPanel.layout");
		//root.at(0)->findWidget("Text")->castType<MyGUI::TextBox>()->setCaption("Demonstration of using different widgets and styles (something like Ogre Demo_Gui).");

		mMainPanel = new MainPanel();
		mMainPanel->eventAction = MyGUI::newDelegate(this, &DemoKeeper::notifyEventAction);
		mMainPanel->addObject("FrameWindow");
		mMainPanel->addObject("Horizontal Scrollbar");
		mMainPanel->addObject("Vertical Scrollbar");
		mMainPanel->addObject("TextBox");
		mMainPanel->addObject("ImageBox");
		mMainPanel->addObject("Render to Texture");

		mEditorWindow = new EditorWindow();
		
		MyGUI::FontManager& fontmanager = MyGUI::FontManager::getInstance();

		MyGUI::IFont* font = fontmanager.getByName(fontmanager.getDefaultFont());
#ifdef MYGUI_COCOS2D_PLATFORM
		CCScene* scene = HelloWorld::scene();
		cocos2d::CCDirector::sharedDirector()->runWithScene(scene);

		MyGUI::Cocos2dTexture* texture = (MyGUI::Cocos2dTexture*)font->getTextureFont();

		CCSprite* fontTexture = CCSprite::createWithTexture(texture->getCocos2dTexture());
		scene->addChild(fontTexture);
		fontTexture->setPosition(CCPoint(scene->getContentSize().width / 2, scene->getContentSize().height / 2));
#endif
	}

	void DemoKeeper::destroyScene()
	{
		removeRenderBoxes();
		destroyWindows();

		delete mEditorWindow;
		mEditorWindow = nullptr;
		delete mMainPanel;
		mMainPanel = nullptr;
	}

	void DemoKeeper::destroyWindows()
	{
		delete mInformationWindow;
		mInformationWindow = nullptr;

		delete mColourWindow;
		mColourWindow = nullptr;
	}

	void DemoKeeper::createWindows()
	{
		destroyWindows();

		mInformationWindow = new InformationWindow(mEditorWindow->getView());
		mColourWindow = new ColourWindow(mEditorWindow->getView());
	}

	int getRand(int _min, int _max)
	{
		if (_max < _min)
			std::swap(_max, _min);
		int range = _max - _min;
		if (range == 0)
			return 0;
		int result = ::rand() % range;
		if (result < 0)
			result = -result;
		return _min + result;
	}

	void DemoKeeper::notifyEventAction(MainPanel::TypeEvents _action, size_t _index)
	{
		static MyGUI::IVertexBuffer* vbo = nullptr;

		if (_action == MainPanel::EventQuit)
		{
			if (vbo)
				MyGUI::RenderManager::getInstance().destroyVertexBuffer(vbo);
			quit();
		}
		else if (_action == MainPanel::EventNew)
		{
			//cocos2d::extension::CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_COME_TO_BACKGROUND);
			//cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(EVNET_COME_TO_FOREGROUND);

			//removeRenderBoxes();
			//destroyWindows();
			//mEditorWindow->clearView();
			//MyGUI::Widget *tempWindow = mEditorWindow->getView()->findWidget("tempWindow");
			//if (tempWindow)
			//	MyGUI::Gui::getInstance().destroyWidget(tempWindow);

			if (vbo)
			{
				MyGUI::RenderManager::getInstance().destroyVertexBuffer(vbo);
				vbo = nullptr;
			}
		}
		else if (_action == MainPanel::EventLoad)
		{
			//mEditorWindow->getView()->createWidget<MyGUI::Window>(
			//	MyGUI::WidgetStyle::Overlapped, "WindowCSX",
			//	MyGUI::IntCoord(10, 10, 100, 100),
			//	MyGUI::Align::Default, "", "tempWindow");

			
			if (!vbo)
			{
				vbo = MyGUI::RenderManager::getInstance().createVertexBuffer();
			}

			for (unsigned i = 2; i < 2048; i += 4)
			{
				vbo->setVertexCount(i);
				vbo->lock();
				vbo->unlock();
			}

			//createWindows();
		}
		else if (_action == MainPanel::EventCreate)
		{
			MyGUI::Widget* view = mEditorWindow->getView();
			const MyGUI::IntCoord& coord = view->getClientCoord();

			if (_index == 0)
			{
				const MyGUI::IntSize size(80, 80);
				MyGUI::Window* window = view->createWidget<MyGUI::Window>(MyGUI::WidgetStyle::Overlapped, "WindowCS", MyGUI::IntCoord(getRand(0, coord.width - size.width), getRand(0, coord.height - size.height), size.width, size.height), MyGUI::Align::Default);
				window->setCaption("Frame");
				window->setMinSize(size);
			}
			else if (_index == 1)
			{
				const MyGUI::IntSize size(180, 15);
				MyGUI::ScrollBar* scroll = view->createWidget<MyGUI::ScrollBar>("ScrollBarH", MyGUI::IntCoord(getRand(0, coord.width - size.width), getRand(0, coord.height - size.height), size.width, size.height), MyGUI::Align::Default);
				scroll->setScrollRange(200);
				scroll->setScrollPosition(10);
				scroll->setScrollPage(1);
				scroll->setScrollViewPage(20);
			}
			else if (_index == 2)
			{
				const MyGUI::IntSize size(15, 180);
				MyGUI::ScrollBar* scroll = view->createWidget<MyGUI::ScrollBar>("ScrollBarV", MyGUI::IntCoord(getRand(0, coord.width - size.width), getRand(0, coord.height - size.height), size.width, size.height), MyGUI::Align::Default);
				scroll->setScrollRange(200);
				scroll->setScrollPosition(10);
				scroll->setScrollPage(1);
				scroll->setScrollViewPage(20);
			}
			else if (_index == 3)
			{
				const MyGUI::IntSize size(80, 26);
				MyGUI::TextBox* text = view->createWidget<MyGUI::TextBox>("TextBox", MyGUI::IntCoord(getRand(0, coord.width - size.width), getRand(0, coord.height - size.height), size.width, size.height), MyGUI::Align::Default);
				text->setCaption("TextBox");
			}
			else if (_index == 4)
			{
				const MyGUI::IntSize size(50, 50);
				MyGUI::ImageBox* image = view->createWidget<MyGUI::ImageBox>("ImageBox", MyGUI::IntCoord(getRand(0, coord.width - size.width), getRand(0, coord.height - size.height), size.width, size.height), MyGUI::Align::Default);
				image->setImageTexture("HelpIcon.png");
			}
			else if (_index == 5)
			{
				const MyGUI::IntSize size(480, 320);
				MyGUI::Window* window = view->createWidget<MyGUI::Window>(MyGUI::WidgetStyle::Overlapped, "WindowCSX", MyGUI::IntCoord(getRand(0, coord.width - size.width), getRand(0, coord.height - size.height), size.width, size.height), MyGUI::Align::Default);
				window->setCaption("Render");
				MyGUI::Canvas* canvas = window->createWidget<MyGUI::Canvas>("Canvas", MyGUI::IntCoord(0, 0, window->getClientCoord().width, window->getClientCoord().height), MyGUI::Align::Stretch);

				createRenderBox(canvas);
			}
		}
	}

	void DemoKeeper::removeRenderBoxes()
	{
#ifdef MYGUI_COCOS2D_PLATFORM
		for (std::vector<wraps::RenderBox*>::iterator item = mRenderBoxes.begin(); item != mRenderBoxes.end(); ++item)
			delete *item;
		mRenderBoxes.clear();
#endif // MYGUI_COCOS2D_PLATFORM
	}

	void DemoKeeper::createRenderBox(MyGUI::Canvas* _canvas)
	{
#ifdef MYGUI_COCOS2D_PLATFORM
		wraps::RenderBox* box = new wraps::RenderBox();
		box->setCanvas(_canvas);
		box->setBackgroundColour(MyGUI::Colour::Black);
		mRenderBoxes.push_back(box);
#endif // MYGUI_COCOS2D_PLATFORM
	}

} // namespace demo
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
MYGUI_APP(demo::DemoKeeper)
#endif