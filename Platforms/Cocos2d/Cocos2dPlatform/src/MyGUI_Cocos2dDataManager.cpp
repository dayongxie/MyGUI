/*!
	@file
	@author		
	@date		
*/
#include "MyGUI_Cocos2dDataManager.h"
#include "MyGUI_Cocos2dDiagnostic.h"
#include "MyGUI_DataFileStream.h"
#include "FileSystemInfo/Cocos2d/FileSystemInfo.h"
#include "MyGUI_PathsManager.h"
#include <sstream>

namespace MyGUI
{
	Cocos2dDataManager::Cocos2dDataManager() :
		mIsInitialise(false)
	{
	}

	void Cocos2dDataManager::initialise()
	{
		MYGUI_PLATFORM_ASSERT(!mIsInitialise, getClassTypeName() << " initialised twice");
		MYGUI_PLATFORM_LOG(Info, "* Initialise: " << getClassTypeName());

		MYGUI_PLATFORM_LOG(Info, getClassTypeName() << " successfully initialized");
		mIsInitialise = true;
	}

	void Cocos2dDataManager::shutdown()
	{
		MYGUI_PLATFORM_ASSERT(mIsInitialise, getClassTypeName() << " is not initialised");
		MYGUI_PLATFORM_LOG(Info, "* Shutdown: " << getClassTypeName());

		MYGUI_PLATFORM_LOG(Info, getClassTypeName() << " successfully shutdown");
		mPaths.clear();
		mIsInitialise = false;
	}

	IDataStream* Cocos2dDataManager::getData(const std::string& _name)
	{
		unsigned long fileLen = -1;
		unsigned char *fileData = NULL;
		std::string filepath = getDataPath(_name);
		if (filepath.empty())
			return nullptr;

		filepath = CCFileUtils::sharedFileUtils()->fullPathForFilename(filepath.c_str());

		fileData = CCFileUtils::sharedFileUtils()->getFileData(filepath.c_str(), "rb", &fileLen);
		std::stringstream* stream = new std::stringstream(std::stringstream::out | std::stringstream::in|std::stringstream::binary);
		stream->write((const char*)fileData, fileLen);
		delete fileData;
		CommonDataStream<std::stringstream>* data = new CommonDataStream<std::stringstream>(stream);

		return data;
	}

	void Cocos2dDataManager::freeData(IDataStream* _data)
	{
		delete _data;
	}

	bool Cocos2dDataManager::isDataExist(const std::string& _name)
	{
		const VectorString& files = getDataListNames(_name);
		return files.size() >= 1;
	}

	const VectorString& Cocos2dDataManager::getDataListNames(const std::string& _pattern)
	{
// 		static VectorString result;
// 		result.clear();
// 
// 		for (VectorArhivInfo::const_iterator item = mPaths.begin(); item != mPaths.end(); ++item)
// 		{
// 			common::scanFolder(result, (*item).name, (*item).recursive, _pattern, false);
// 		}
// 
// 		return result;

		static VectorString result;
		result.clear();

		const std::string& path = PathsManager::getInstance().getPath(_pattern);

		if (!path.empty())
		{
			result.push_back(path);
		}

		return result;
	}

	const std::string& Cocos2dDataManager::getDataPath(const std::string& _name)
	{
// 		static std::string path;
// 		VectorString result;
// 
// 		for (VectorArhivInfo::const_iterator item = mPaths.begin(); item != mPaths.end(); ++item)
// 		{
// 			common::scanFolder(result, (*item).name, (*item).recursive, _name, true);
// 		}
// 
// 		path = result.empty() ? "" : result[0];
// 		return path;

		return PathsManager::getInstance().getPath(_name);
	}

	void Cocos2dDataManager::addResourceLocation(const std::string& _name, bool _recursive)
	{
		ArhivInfo info;
		info.name = _name;
		info.recursive = _recursive;
		mPaths.push_back(info);
	}

} // namespace MyGUI
