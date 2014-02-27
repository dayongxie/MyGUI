/*!
	@file
	@author		
	@date		
*/


#ifndef __MYGUI_COCOS2D_IMEMANAGER_H__
#define __MYGUI_COCOS2D_IMEMANAGER_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_IMEManager.h"
#include <cocos2d.h>

namespace MyGUI
{

	class Cocos2dIMEManager :
		public cocos2d::CCObject,
		public cocos2d::CCIMEDelegate,
		public MyGUI::IMEManager
	{
	public:
		Cocos2dIMEManager();
		~Cocos2dIMEManager();

		void initialise();
		void shutdown();

	protected:
		virtual bool canAttachWithIME();
		virtual void didAttachWithIME();
		virtual bool canDetachWithIME();
		virtual void didDetachWithIME();
		virtual void insertText(const char * text, int len);

		virtual void deleteBackward();
		virtual void deleteForward();
		virtual const char * getContentText();
		virtual int getContentTextCursor();

		virtual void keyboardWillShow(cocos2d::CCIMEKeyboardNotificationInfo& info);
		virtual void keyboardDidShow(cocos2d::CCIMEKeyboardNotificationInfo& info);
		virtual void keyboardWillHide(cocos2d::CCIMEKeyboardNotificationInfo& info);
		virtual void keyboardDidHide(cocos2d::CCIMEKeyboardNotificationInfo& info);

		////////////////////////////////////////////////////////////////////

		virtual void attachIMEHandler(MyGUI::IMEHandler*);
		virtual void detachIMEHandler(MyGUI::IMEHandler*);

		virtual void activateIMEKeyboard();
		virtual void deactiveIMEKeyboard();

		MyGUI::IMEHandler* mIMEHandler;
		bool mActive;
	};

}

#endif // __MYGUI_COCOS2D_IMEMANAGER_H__