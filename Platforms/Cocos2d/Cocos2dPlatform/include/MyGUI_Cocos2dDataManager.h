/*!
	@file
	@author		
	@date		
*/


#ifndef __MYGUI_COCOS2D_DATAMANAGER_H__
#define __MYGUI_COCOS2D_DATAMANAGER_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_DataManager.h"

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
	class Cocos2dDataManager:
		public DataManager
	{
	public:
		Cocos2dDataManager();

		void initialise();
		void shutdown();

		static Cocos2dDataManager& getInstance()
		{
			return *getInstancePtr();
		}
		static Cocos2dDataManager* getInstancePtr()
		{
			return static_cast<Cocos2dDataManager*>(DataManager::getInstancePtr());
		}

		/** @see DataManager::getData(const std::string& _name) */
		virtual IDataStream* getData(const std::string& _name);
	
		/** Free data stream.
			@param _data Data stream.
		*/
		virtual void freeData(IDataStream* _data);

		/** @see DataManager::isDataExist(const std::string& _name) */
		virtual bool isDataExist(const std::string& _name);

		/** @see DataManager::getDataListNames(const std::string& _pattern) */
		virtual const VectorString& getDataListNames(const std::string& _pattern);

		/** @see DataManager::getDataPath(const std::string& _name) */
		virtual const std::string& getDataPath(const std::string& _name);

		/*internal:*/
		void addResourceLocation(const std::string& _name, bool _recursive);

	private:
		struct ArhivInfo
		{
			std::string name;
			bool recursive;
		};
		typedef std::vector<ArhivInfo> VectorArhivInfo;
		VectorArhivInfo mPaths;

		bool mIsInitialise;
	};
}

#endif // __MYGUI_COCOS2D_DATAMANAGER_H__