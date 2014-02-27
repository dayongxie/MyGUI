#include "MyGUI_Cocos2dIMEManager.h"
#include "MyGUI_Cocos2dDiagnostic.h"

using namespace cocos2d;

namespace MyGUI
{

	Cocos2dIMEManager::Cocos2dIMEManager() :
	mIMEHandler(nullptr)
	{

	}

	Cocos2dIMEManager::~Cocos2dIMEManager()
	{

	}

	void Cocos2dIMEManager::initialise()
	{
	}

	void Cocos2dIMEManager::shutdown()
	{
	}

	bool Cocos2dIMEManager::canAttachWithIME()
	{
		if (mIMEHandler)
			return mIMEHandler->canAttachWithIME();

		return false;
	}

	void Cocos2dIMEManager::didAttachWithIME()
	{
		if (mIMEHandler)
			mIMEHandler->didAttachWithIME();
	}

	bool Cocos2dIMEManager::canDetachWithIME()
	{
		if (mIMEHandler)
			return mIMEHandler->canDetachWithIME();

		return false;
	}

	void Cocos2dIMEManager::didDetachWithIME()
	{
		if (mIMEHandler)
			mIMEHandler->didDetachWithIME();
	}

	void Cocos2dIMEManager::insertText(const char * text, int len)
	{
		if (mIMEHandler)
			mIMEHandler->insertText(text, len);
	}


	void Cocos2dIMEManager::deleteBackward()
	{
		if (mIMEHandler)
			return mIMEHandler->deleteBackward();
	}
	
	void Cocos2dIMEManager::deleteForward()
	{
		if (mIMEHandler)
			return mIMEHandler->deleteForward();
	}

	const char * Cocos2dIMEManager::getContentText()
	{
		if (mIMEHandler)
			return mIMEHandler->getContentText();

		return nullptr;
	}

	int Cocos2dIMEManager::getContentTextCursor()
	{
		if (mIMEHandler)
			return mIMEHandler->getContentTextCursor();

		return -1;
	}

	void Cocos2dIMEManager::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
	{

	}

	void Cocos2dIMEManager::keyboardDidShow(CCIMEKeyboardNotificationInfo& info)
	{

	}

	void Cocos2dIMEManager::keyboardWillHide(CCIMEKeyboardNotificationInfo& info)
	{

	}

	void Cocos2dIMEManager::keyboardDidHide(CCIMEKeyboardNotificationInfo& info)
	{

	}

	////////////////////////////////////////////////////////////////////

	void Cocos2dIMEManager::attachIMEHandler(IMEHandler* handler)
	{
		mIMEHandler = handler;
		CCIMEDelegate::attachWithIME();
	}

	void Cocos2dIMEManager::detachIMEHandler(IMEHandler* handler)
	{
		if (mIMEHandler == handler)
		{
			mIMEHandler = nullptr;
			if (mActive)
				deactiveIMEKeyboard();

			CCIMEDelegate::detachWithIME();
		}
	}

	void Cocos2dIMEManager::activateIMEKeyboard()
	{
		// open keyboard
		CCEGLView * pGlView = CCDirector::sharedDirector()->getOpenGLView();
		if (pGlView)
		{
			pGlView->setIMEKeyboardState(true);
			mActive = true;
		}
	}

	void Cocos2dIMEManager::deactiveIMEKeyboard()
	{
		// close keyboard
		CCEGLView * pGlView = CCDirector::sharedDirector()->getOpenGLView();
		if (pGlView)
		{
			pGlView->setIMEKeyboardState(false);
			mActive = false;
		}
	}
	
} // namespace MyGUI
