/*!
	@file
	@author		Albert Semenov
	@date		08/2008
*/
#include "Precompiled.h"
#include "DemoKeeper.h"
#include "Base/Main.h"

USING_NS_CC;

namespace demo
{

	void notifyMouseSetFocus(MyGUI::Widget* _sender, MyGUI::Widget* _old)
	{
		MyGUI::ImageBox* image = _sender->castType<MyGUI::ImageBox>();
		image->setItemName("Active");
	}

	void notifyMouseLostFocus(MyGUI::Widget* _sender, MyGUI::Widget* _new)
	{
		MyGUI::ImageBox* image = _sender->castType<MyGUI::ImageBox>();
		image->setItemName("Normal");
	}

	void DemoKeeper::setupResources()
	{
		base::BaseManager::setupResources();
		addResourceLocation(getRootMedia() + "/Demos/Demo_Picking");
		addResourceLocation(getRootMedia() + "/Common/Demos");
	}

	void DemoKeeper::createScene()
	{
		base::BaseDemoManager::createScene();
		MyGUI::LayoutManager::getInstance().loadLayout("Wallpaper.layout");
		const MyGUI::VectorWidgetPtr& root = MyGUI::LayoutManager::getInstance().loadLayout("HelpPanel.layout");
		if (root.size() == 1)
			root.at(0)->findWidget("Text")->castType<MyGUI::TextBox>()->setCaption("Sample of picking mask for widget.");

		MyGUI::ResourceManager::getInstance().load("Resources.xml");

		const MyGUI::IntSize& view = MyGUI::RenderManager::getInstance().getViewSize();
		const MyGUI::IntSize size(128, 128);

		MyGUI::ImageBox* image = MyGUI::Gui::getInstance().createWidget<MyGUI::ImageBox>("ImageBox", MyGUI::IntCoord((view.width - size.width) / 2, (view.height - size.height) / 2, size.width, size.height), MyGUI::Align::Default, "Main");
		image->setItemResource("pic_Crystal_Clear_Butterfly");
		image->setItemGroup("States");
		image->setItemName("Normal");

		image->eventMouseSetFocus += MyGUI::newDelegate(notifyMouseSetFocus);
		image->eventMouseLostFocus += MyGUI::newDelegate(notifyMouseLostFocus);

		image->setMaskPick("Crystal_Clear_Butterfly_Pick.png");
	}

	void DemoKeeper::destroyScene()
	{
	}

	bool DemoKeeper::applicationDidFinishLaunching() {
		// initialize director
		CCDirector *pDirector = CCDirector::sharedDirector();

		pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

		// enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
		//    pDirector->enableRetinaDisplay(true);

		// turn on display FPS
		pDirector->setDisplayStats(true);

		// set FPS. the default value is 1.0/60 if you don't call this
		pDirector->setAnimationInterval(1.0 / 60);

		// create a scene. it's an autorelease object
		//CCScene *pScene = HelloWorld::scene();

		// run
		//pDirector->runWithScene(pScene);

		return true;
	}

	// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
	void DemoKeeper::applicationDidEnterBackground() {
		CCDirector::sharedDirector()->stopAnimation();

		// if you use SimpleAudioEngine, it must be pause
		// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}

	// this function will be called when the app is active again
	void DemoKeeper::applicationWillEnterForeground() {
		CCDirector::sharedDirector()->startAnimation();

		// if you use SimpleAudioEngine, it must resume here
		// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}

} // namespace demo

MYGUI_APP(demo::DemoKeeper)
