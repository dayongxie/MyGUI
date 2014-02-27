#ifndef __MYGUI_IME_MANAGER_H__
#define __MYGUI_IME_MANAGER_H__

#include "MyGUI_Singleton.h"

namespace MyGUI
{
	class MYGUI_EXPORT IMEHandler
	{
	public:
		virtual bool canAttachWithIME() = 0;
		virtual void didAttachWithIME() = 0;
		virtual bool canDetachWithIME() = 0;
		virtual void didDetachWithIME() = 0;
		virtual void insertText(const char * text, int len) = 0;
		virtual void deleteBackward() = 0;
		virtual void deleteForward() = 0;
		virtual const char * getContentText() = 0;
		virtual int getContentTextCursor() = 0;
	};

	class MYGUI_EXPORT IMEManager :
		public Singleton<IMEManager>
	{
	public:
		virtual void attachIMEHandler(IMEHandler*) = 0;
		virtual void detachIMEHandler(IMEHandler*) = 0;

		virtual void activateIMEKeyboard() = 0;
		virtual void deactiveIMEKeyboard() = 0;
	};
}

#endif