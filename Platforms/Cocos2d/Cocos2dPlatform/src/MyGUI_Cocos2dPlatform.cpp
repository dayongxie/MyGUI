/*!
	@file
	@author		
	@date		
*/

#include "MyGUI_Cocos2dPlatform.h"
#include "MyGUI_Cocos2dRenderManager.h"
#include "MyGUI_Cocos2dDataManager.h"
#include "MyGUI_Cocos2dFont.h"
#include "MyGUI_Cocos2dIMEManager.h"

#include <assert.h>

namespace MyGUI
{

	Cocos2dPlatform::Cocos2dPlatform():
		mIsInitialise(false)
	{
		mRenderManager = new Cocos2dRenderManager();
		mDataManager = new Cocos2dDataManager();
		mFontBuilder = new Cocos2dFontBuilder();
		mIMEManager = new Cocos2dIMEManager();
		//mLogManager = new LogManager();
	}

	Cocos2dPlatform::~Cocos2dPlatform()
	{
		delete mIMEManager;
		delete mFontBuilder;
		delete mDataManager;
		CC_SAFE_RELEASE(mRenderManager);
		//delete mLogManager;
	}

	void Cocos2dPlatform::initialise(const std::string& _logName)
	{
		assert(!mIsInitialise);
		mIsInitialise = true;

		//if (!_logName.empty())
		//	LogManager::getInstance().createDefaultSource(_logName);

		mRenderManager->initialise();
		mDataManager->initialise();
		mFontBuilder->initialise();
		mIMEManager->initialise();
	}

	void Cocos2dPlatform::shutdown()
	{
		if (!mIsInitialise)
			return;

		mIsInitialise = false;

		mIMEManager->shutdown();
		mFontBuilder->shutdown();
		mDataManager->shutdown();
		mRenderManager->shutdown();
	}

	Cocos2dRenderManager* Cocos2dPlatform::getRenderManagerPtr()
	{
		assert(mIsInitialise);
		return mRenderManager;
	}

	Cocos2dDataManager* Cocos2dPlatform::getDataManagerPtr()
	{
		assert(mIsInitialise);
		return mDataManager;
	}
};