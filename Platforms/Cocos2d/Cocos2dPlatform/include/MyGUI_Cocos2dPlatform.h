/*!
	@file
	@author		
	@date		
*/

#ifndef __MYGUI_COCOS2D_PLATFORM_H__
#define __MYGUI_COCOS2D_PLATFORM_H__

#include "MyGUI_Cocos2dDiagnostic.h"

#include <string>

namespace MyGUI
{
	class Cocos2dRenderManager;
	class Cocos2dDataManager;
	class Cocos2dFontBuilder;
	class Cocos2dIMEManager;

	class Cocos2dPlatform
	{
	public:
		Cocos2dPlatform();
		~Cocos2dPlatform();

		void initialise(const std::string& _logName = MYGUI_PLATFORM_LOG_FILENAME);
		void shutdown();

		Cocos2dRenderManager* getRenderManagerPtr();
		Cocos2dDataManager* getDataManagerPtr();
	private:
		bool mIsInitialise;
		Cocos2dRenderManager* mRenderManager;
		Cocos2dDataManager* mDataManager;
		Cocos2dFontBuilder* mFontBuilder;
		Cocos2dIMEManager* mIMEManager;
		//LogManager* mLogManager;
	};
}

#endif /* __MYGUI_COCOS2D_PLATFORM_H__ */
