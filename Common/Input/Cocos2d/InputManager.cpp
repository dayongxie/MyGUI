#include "InputManager.h"

#include <cocos2d.h>

using namespace cocos2d;

namespace input
{
	InputManager::InputManager()
	{

	}

	InputManager::~InputManager()
	{

	}

	void InputManager::createInput(size_t handle)
	{
		CCTouchDispatcher *dispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
		dispatcher->addTargetedDelegate(this, -129, true);
	}

	void InputManager::destroyInput()
	{
		CCTouchDispatcher *dispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
		dispatcher->removeDelegate(this);
	}

	bool InputManager::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
	{
		CCPoint pt = pTouch->getLocationInView();
        pt.x *= CC_CONTENT_SCALE_FACTOR();
        pt.y *= CC_CONTENT_SCALE_FACTOR();
		//MyGUI::InputManager::getInstance().injectMouseMove(int(pt.x), int(pt.y), MyGUI::MouseButton::Left);
		return MyGUI::InputManager::getInstance().injectMousePress(int(pt.x), int(pt.y), MyGUI::MouseButton::Left);
	}

	void InputManager::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
	{
		CCPoint pt = pTouch->getLocationInView();
        pt.x *= CC_CONTENT_SCALE_FACTOR();
        pt.y *= CC_CONTENT_SCALE_FACTOR();
		MyGUI::InputManager::getInstance().injectMouseRelease(int(pt.x), int(pt.y), MyGUI::MouseButton::Left);
	}

	void InputManager::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
	{
		CCPoint pt = pTouch->getLocationInView();
        pt.x *= CC_CONTENT_SCALE_FACTOR();
        pt.y *= CC_CONTENT_SCALE_FACTOR();
		MyGUI::InputManager::getInstance().injectMouseRelease(int(pt.x), int(pt.y), MyGUI::MouseButton::Left);
	}

	void InputManager::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
	{
		CCPoint pt = pTouch->getLocationInView();
        pt.x *= CC_CONTENT_SCALE_FACTOR();
        pt.y *= CC_CONTENT_SCALE_FACTOR();
		MyGUI::InputManager::getInstance().injectMouseMove(int(pt.x), int(pt.y), MyGUI::MouseButton::Left);
	}

	void InputManager::injectKeyPress( MyGUI::KeyCode _key, MyGUI::Char _text )
	{

	}

}