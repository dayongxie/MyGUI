//------------------------------------------------------------------------------------
// 文件名：		MyGUI_PathsManager.cpp
// 内	容：	
// 说	明：	
// 创建日期：	2013.06.09
// 创建人：		mazp
// 版权所有：	幻星信息技术
//------------------------------------------------------------------------------------
#include "MyGUI_Precompiled.h"
#include "MyGUI_PathsManager.h"
#include "MyGUI_XmlDocument.h"
#include "MyGUI_DataManager.h"
#include "MyGUI_DataStreamHolder.h"

namespace MyGUI
{

	template <> PathsManager* Singleton<PathsManager>::msInstance = nullptr;
	template <> const char* Singleton<PathsManager>::mClassTypeName = "PathsManager";
	static std::string emptyStr = "";

	PathsManager::PathsManager() :
		mIsInitialise(false),
		mFileName("MyGUI_Paths.xml")
	{
	}

	void PathsManager::initialise()
	{
		MYGUI_ASSERT(!mIsInitialise, getClassTypeName() << " initialised twice");
		MYGUI_LOG(Info, "* Initialise: " << getClassTypeName());

		mMapPath["MyGUI_Paths.xml"] = "MyGUI_Paths.xml";
		loadPaths(mFileName);

		MYGUI_LOG(Info, getClassTypeName() << " successfully initialized");
		mIsInitialise = true;
	}

	void PathsManager::shutdown()
	{
		MYGUI_ASSERT(mIsInitialise, getClassTypeName() << " is not initialised");
		MYGUI_LOG(Info, "* Shutdown: " << getClassTypeName());

		MYGUI_LOG(Info, getClassTypeName() << " successfully shutdown");
		mIsInitialise = false;
	}

	const std::string& PathsManager::getPath(const std::string& _tag)
	{
		MapPathString::iterator iter = mMapPath.find(_tag);
		if (iter != mMapPath.end())
		{
			return iter->second;
		}

		return emptyStr;
	}

	bool PathsManager::loadPaths(const std::string& _file)
	{
		DataStreamHolder data = DataManager::getInstance().getData(_file);
		if (data.getData() == nullptr)
		{
			MYGUI_LOG(Error, "file '" << _file << "' not found");
			return false;
		}

		xml::Document doc;
		// формат xml
		if (doc.open(data.getData()))
		{
			xml::ElementPtr root = doc.getRoot();
			if (root)
			{
				xml::ElementEnumerator tag = root->getElementEnumerator();
				while (tag.next("Tag"))
				{
					mMapPath[tag->findAttribute("name")] = tag->getContent();
				}
			}
		}

		return true;
	}

} // namespace MyGUI
