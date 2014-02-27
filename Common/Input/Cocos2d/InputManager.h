#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "MyGUI_InputManager.h"
#include <touch_dispatcher/CCTouchDelegateProtocol.h>

namespace input
{
	class InputManager :
		public cocos2d::CCTouchDelegate
	{
	public:
		InputManager();
		virtual ~InputManager();

		void createInput(size_t handle);
		void destroyInput();
		void captureInput();
		void setInputViewSize(int _width, int _height);

		virtual void injectKeyPress(MyGUI::KeyCode _key, MyGUI::Char _text);
	private:
 		virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
 		virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
 		virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
 		virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	};
}

#endif // __INPUT_MANAGER_H__