/*!
	@file
	@author		
	@date		
*/


#ifndef __MYGUI_COCOS2D_LOGMANAGER_H__
#define __MYGUI_COCOS2D_LOGMANAGER_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_Singleton.h"
#include "MyGUI_Cocos2dDiagnostic.h"

// gnu libstdc++ have not implement wstring and wostream
#if defined(_GLIBCXX_OSTREAM) && !defined(STD_WSTRING_DEFINED)
#define STD_WSTRING_DEFINED

namespace std
{
	typedef basic_string<wchar_t> wstring;
	typedef basic_ostream<wchar_t> wostream;
}
#endif

namespace MyGUI
{

	
	class OutputDebugLogListener :
		public ILogListener
	{
	public:
		OutputDebugLogListener();
		virtual ~OutputDebugLogListener();

		/** Close log listener. (for example close file) */
		virtual void close();

		//! @copydoc ILogListener::log(const std::string& _section, LogLevel _level, const struct tm* _time, const std::string& _message, const char* _file, int _line)
		virtual void log(const std::string& _section, MyGUI::LogLevel _level, const struct tm* _time, const std::string& _message, const char* _file, int _line);

		/** Is log listener enabled. */
		bool getEnabled() const;
		/** Enable or disable log listener. */
		void setEnabled(bool _value);

	private:
		bool mEnabled;
	};

	class Cocos2dLogManager // : public Singleton<Cocos2dLogManager>
	{
	public:
		Cocos2dLogManager();
		~Cocos2dLogManager();

		void initialise(const std::string& _logName = MYGUI_PLATFORM_LOG_FILENAME);
		void shutdown();

		/** Call LogSource::log for all log sources. */
		void log(const std::string& _section, LogLevel _level, const std::string& _message, const char* _file, int _line);

		/** Enable or disable default ConsoleLogListener that writes log into std::cout.\n
			Enabled (true) by default.
		*/
		void setSTDOutputEnabled(bool _value);
		/** Is disable ConsoleLogListener enabled. */
		bool getSTDOutputEnabled() const;

		void setOutputDebugEnabled(bool _value);
		/** Is disable OutputDebugLogListener enabled. */
		bool getOutputDebugEnabled() const;

		/** Set default LevelLogFilter level. */
		void setLoggingLevel(LogLevel _value);
		/** Get default LevelLogFilter level. */
		LogLevel getLoggingLevel() const;

	public :
		static Cocos2dLogManager* create();
		static void destory();
		static Cocos2dLogManager* getInstancePtr();
		static Cocos2dLogManager& getInstance();

	private:
		static Cocos2dLogManager* _instance;
		static const char*  _classTypeName;

	private:
		LogManager* mLogManager;
		OutputDebugLogListener* mLogListener;
		LevelLogFilter* mFilter;
		LogSource* mLogSource;

		bool mIsInitialise;
	};

	 template<>  Cocos2dLogManager* Singleton<Cocos2dLogManager>::msInstance;
	//extern template<> const char* Singleton<Cocos2dLogManager>::mClassTypeName;


}



#endif // __MYGUI_COCOS2D_LOGMANAGER_H__