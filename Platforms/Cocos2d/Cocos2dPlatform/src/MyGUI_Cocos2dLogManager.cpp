/*!
	@file
	@author		
	@date		
*/
#include "MyGUI_Cocos2dLogManager.h"
#include "MyGUI_Cocos2dDiagnostic.h"
#include "MyGUI_LevelLogFilter.h"
#include <cocos2d.h>

namespace MyGUI
{

//	template<> Cocos2dLogManager* Singleton<Cocos2dLogManager>::msInstance = nullptr;
//	template<> const char* Singleton<Cocos2dLogManager>::mClassTypeName = "Cocos2dLogManager";

	Cocos2dLogManager* Cocos2dLogManager::_instance = 0;
	const char* Cocos2dLogManager::_classTypeName = "Cocos2dLogManager";

	Cocos2dLogManager* Cocos2dLogManager::create()
	{
		_instance = new Cocos2dLogManager();

		return _instance;
	}

	void Cocos2dLogManager::destory()
	{
		delete _instance;
	}

	Cocos2dLogManager* Cocos2dLogManager::getInstancePtr()
	{
	
		return _instance;
	}

	Cocos2dLogManager& Cocos2dLogManager::getInstance()
	{
	/*	if (_instance == 0)
		{
			ASSERT(false, "");
		}*/

		return *_instance;
	}


	OutputDebugLogListener::OutputDebugLogListener()
		: mEnabled(true)
	{

	}

	OutputDebugLogListener::~OutputDebugLogListener()
	{

	}

	void OutputDebugLogListener::log(const std::string& _section, MyGUI::LogLevel _level, 
		const struct tm* _time, const std::string& _message, const char* _file, int _line)
	{
		if (mEnabled)
		{
			cocos2d::CCLog("%s", _message.c_str());
		}
	}

	bool OutputDebugLogListener::getEnabled() const
	{
		return mEnabled;
	}

	void OutputDebugLogListener::setEnabled(bool _value)
	{
		mEnabled = _value;
	}

	void OutputDebugLogListener::close()
	{

	}

	Cocos2dLogManager::Cocos2dLogManager() :
		mIsInitialise(false),
		mLogListener(NULL),
		mLogSource(NULL)
	{
		_instance = this;
		mLogManager = new LogManager();
	}

	Cocos2dLogManager::~Cocos2dLogManager()
	{
		assert(!mIsInitialise);
		delete mLogManager;
		delete mLogListener;
		delete mFilter;
		delete mLogSource;
	}

	void Cocos2dLogManager::initialise(const std::string& _logName)
	{
		mIsInitialise = true;

		std::string logfilepath = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath() + "/" + _logName;

		mLogManager->setSTDOutputEnabled(false);
		mLogManager->createDefaultSource(logfilepath);

		// 加入输出窗口日志
		mLogListener = new OutputDebugLogListener();
		mFilter = new LevelLogFilter();
		mLogSource = new LogSource();

		mLogSource->open();
		mLogSource->addLogListener(mLogListener);
		mLogSource->setLogFilter(mFilter);
		mLogManager->addLogSource(mLogSource);
	}

	void Cocos2dLogManager::shutdown()
	{
		mIsInitialise = false;
	}

	void Cocos2dLogManager::log(const std::string& _section, LogLevel _level, const std::string& _message, const char* _file, int _line)
	{
		if (mLogManager == nullptr)
		{
			return;
		}

		mLogManager->log(_section, _level, _message, _file, _line);
	}

	void Cocos2dLogManager::setSTDOutputEnabled(bool _value)
	{
		if (mLogManager == nullptr)
		{
			return;
		}

		mLogManager->setSTDOutputEnabled(_value);
	}

	bool Cocos2dLogManager::getSTDOutputEnabled() const
	{
		if (mLogManager == nullptr)
		{
			return false;
		}

		return mLogManager->getSTDOutputEnabled();
	}

	void Cocos2dLogManager::setOutputDebugEnabled(bool _value)
	{
		if (mLogListener == nullptr)
		{
			return;
		}

		mLogListener->setEnabled(_value);
	}

	bool Cocos2dLogManager::getOutputDebugEnabled() const
	{
		if (mLogListener == nullptr)
		{
			return false;
		}

		return mLogListener->getEnabled();
	}

	void Cocos2dLogManager::setLoggingLevel(LogLevel _value)
	{
		if (mLogManager == nullptr)
		{
			return ;
		}

		mLogManager->setLoggingLevel(_value);
	}

	LogLevel Cocos2dLogManager::getLoggingLevel() const
	{
		if (mLogManager == nullptr)
		{
			return LogLevel::Info;
		}

		return mLogManager->getLoggingLevel();
	}

} // namespace MyGUI
