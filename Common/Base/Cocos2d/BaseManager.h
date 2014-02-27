#ifndef __BASE_MANAGER_H__
#define __BASE_MANAGER_H__

#include <MyGUI.h>
#include "Base/StatisticInfo.h"
#include "Base/InputFocusInfo.h"

#include "InputManager.h"
#include "PointerManager.h"
#include <cocoa/CCObject.h>
#include <CCApplication.h>
#include <CCProtocols.h>

namespace MyGUI
{
	class Cocos2dPlatform;
	class Cocos2dLogManager;
}

namespace base
{
	class BaseManager :
		public cocos2d::CCObject,
		public input::InputManager,
		public cocos2d::CCApplication,
		public cocos2d::CCDirectorDelegate
	{
	public:
		BaseManager();
		virtual ~BaseManager();

		virtual void prepare();

		bool create();
		void destroy();

		int run();
		void quit();

		const std::string& getRootMedia();
		void setResourceFilename(const std::string& _flename);
		void addResourceLocation(const std::string& _name, bool _recursive = false);

		typedef std::map<std::string, std::string> MapString;
		MapString getStatistic() { return MapString(); }

		/**
		@brief    Implement CCDirector and CCScene init code here.
		@return true    Initialize success, app continue.
		@return false   Initialize failed, app terminate.
		*/
		virtual bool applicationDidFinishLaunching();

		/**
		@brief  The function be called when the application enter background
		@param  the pointer of the application
		*/
		virtual void applicationDidEnterBackground();

		/**
		@brief  The function be called when the application enter foreground
		@param  the pointer of the application
		*/
		virtual void applicationWillEnterForeground();


		virtual void updateProjection(void);
		virtual void prePurge();
		virtual void afterPurge();

		virtual void setupResources();

		virtual void createScene() {}
		virtual void destroyScene() {}

		void createGui();
		void destroyGui();

	private:
		MyGUI::Gui *mGUI;
		MyGUI::Cocos2dPlatform* mPlatform;
		MyGUI::Cocos2dLogManager* mCocos2dLogManager;
		MyGUI::ScriptBridge* mScriptBridge;

		bool m_hasQuited;

		std::string mPluginCfgName;
		std::string mResourceXMLName;
		std::string mResourceFileName;
		std::string mRootMedia;

		bool mShutdownNextLoop;
	};
} //namespace base

#endif // __BASE_MANAGER_H__
