#include "Precompiled.h"
#include "BaseManager.h"
#include <sstream>
#include <cocos2d.h>

#include "MyGUI_Cocos2dDataManager.h"
#include "MyGUI_Cocos2dLogManager.h"
#include "MyGUI_Cocos2dPlatform.h"

using namespace cocos2d;

class CCDirectorWrapper : public CCDirector
{
public:
	void clearScene()
	{
		if (m_pobScenesStack->count() > 1)
		{
			popToRootScene();
		}
		if (m_pRunningScene)
			replaceScene(CCScene::create());
	}
};

namespace base
{
	BaseManager::BaseManager()
		:mGUI(nullptr),
		mPlatform(nullptr),
		mCocos2dLogManager(nullptr),
		mResourceFileName("MyGUI_Core.xml"),
		mShutdownNextLoop(false),
		m_hasQuited(false)
	{

		mCocos2dLogManager = new MyGUI::Cocos2dLogManager();
		mScriptBridge = new MyGUI::ScriptBridge();

		mCocos2dLogManager->initialise();
	}

	BaseManager::~BaseManager()
	{
		if (mCocos2dLogManager)
		{
			mCocos2dLogManager->shutdown();
			delete mCocos2dLogManager;
			mCocos2dLogManager = nullptr;
		}

		if (mScriptBridge)
		{
			delete mScriptBridge;
			mScriptBridge = nullptr;
		}
	}

	bool BaseManager::create()
	{
		if (!mGUI)
		{
			createGui();

			createInput(0);

			createScene();
		}

		return true;
	}

	void BaseManager::destroy()
	{
		if (!m_hasQuited)
		{
			destroyScene();
			m_hasQuited = true;
		}

		if (mGUI)
		{
			destroyInput();

			destroyGui();
		}
	}

	void BaseManager::setupResources()
	{
		MyGUI::xml::Document doc;
		unsigned long fileLen = 0;
		unsigned char *fileData = CCFileUtils::sharedFileUtils()->getFileData(CCFileUtils::sharedFileUtils()->fullPathForFilename("resources.xml").c_str(), "rb", &fileLen);
		std::stringstream stream(std::stringstream::out | std::stringstream::in|std::stringstream::binary);
		stream.write((const char*)fileData, fileLen);
		delete fileData;
		if (!doc.open(stream))
			doc.getLastError();

		MyGUI::xml::ElementPtr root = doc.getRoot();
		if (root == nullptr || root->getName() != "Paths")
			return;

		MyGUI::xml::ElementEnumerator node = root->getElementEnumerator();
		while (node.next())
		{
			if (node->getName() == "Path")
			{
				bool root = false;
				if (node->findAttribute("root") != "")
				{
					root = MyGUI::utility::parseBool(node->findAttribute("root"));
					if (root) mRootMedia = node->getContent();
				}
				addResourceLocation(node->getContent(), false);
			}
		}

		addResourceLocation(getRootMedia() + "/Common/Base");
	}

	void BaseManager::createGui()
	{
		mPlatform = new MyGUI::Cocos2dPlatform();
		mPlatform->initialise();

		setupResources();

		mGUI = new MyGUI::Gui();
		mGUI->initialise(mResourceFileName);
	}

	void BaseManager::destroyGui()
	{
		if (mGUI)
		{
			mGUI->shutdown();
			delete mGUI;
			mGUI = nullptr;
		}

		if (mPlatform)
		{
			mPlatform->shutdown();
			delete mPlatform;
			mPlatform = nullptr;
		}
	}

	void BaseManager::prepare()
	{
		do 
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			CCEGLView* eglView = CCEGLView::sharedOpenGLView();
			eglView->setFrameSize(1024, 768);
#endif
		} while (0);

		CCDirector::sharedDirector()->setOpenGLView(CCEGLView::sharedOpenGLView());
		CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
	}

	void BaseManager::addResourceLocation(const std::string& _name, bool _recursive)
	{
		mPlatform->getDataManagerPtr()->addResourceLocation(_name, _recursive);
	}

	int BaseManager::run()
	{
		CCDirector::sharedDirector()->setDelegate(this);
		return cocos2d::CCApplication::run();
	}

	void BaseManager::quit()
	{
		CCDirector::sharedDirector()->end();
	}

	const std::string& BaseManager::getRootMedia()
	{
		return mRootMedia;
	}

	void BaseManager::setResourceFilename(const std::string& _flename)
	{
		mResourceFileName = _flename;
	}

	bool BaseManager::applicationDidFinishLaunching() {
		return true;
	}

	// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
	void BaseManager::applicationDidEnterBackground() {
		CCDirector::sharedDirector()->stopAnimation();

		// if you use SimpleAudioEngine, it must be pause
		// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}

	// this function will be called when the app is active again
	void BaseManager::applicationWillEnterForeground() {
		CCDirector::sharedDirector()->startAnimation();

		// if you use SimpleAudioEngine, it must resume here
		// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}

	void BaseManager::updateProjection( void )
	{

	}

	void BaseManager::prePurge()
	{
		destroyScene();
		m_hasQuited = true;
		this->destroy();
	}

	void BaseManager::afterPurge()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	}

}
