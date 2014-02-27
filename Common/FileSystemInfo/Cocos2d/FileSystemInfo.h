#ifndef __FILE_SYSTEM_INFO_COCOCS2D_H__
#define __FILE_SYSTEM_INFO_COCOCS2D_H__

#include <string>
#include <vector>
#include <MyGUI.h>
#include <platform/CCFileUtils.h>

#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
#include <windows.h>
#include <io.h>
#endif

using cocos2d::CCFileUtils;

namespace common
{

	struct  FileInfo
	{
		FileInfo(const std::string& _name, bool _folder) : name(_name), folder(_folder) { }
		std::string name;
		bool folder;
	};
	
	typedef std::vector<FileInfo> VectorFileInfo;

	inline bool isAbsolutePath(const char* path)
	{
	#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
		if (IsCharAlphaW(path[0]) && path[1] == ':')
			return true;
	#endif
		return path[0] == '/' || path[0] == '\\';
	}

	inline std::string concatenatePath(const std::string& _base, const std::string& _name)
	{
		if (_base.empty() || isAbsolutePath(_name.c_str()))
			return _name;
		else
#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
			return _base + '\\' + _name;
#else
			return _base + '/' + _name;
#endif
	}

	inline bool isReservedDir (const char* _fn)
	{
		// if "."
		return (_fn [0] == '.' && _fn [1] == 0);
	}

	inline bool isParentDir (const char* _fn)
	{
		// if ".."
		return (_fn [0] == '.' && _fn [1] == '.' && _fn [2] == 0);
	}

	void getSystemFileList(VectorFileInfo& _result, const std::string& _folder, const std::string& _mask);

	inline std::string getSystemCurrentFolder()
	{
		return  CCFileUtils::sharedFileUtils()->getWritablePath();
	}

	typedef std::vector<std::string> VectorString;
	inline void scanFolder(VectorString& _result, const std::string& _folder, bool _recursive, const std::string& _mask, bool _fullpath)
	{
		std::string folder = _folder;
		if (!folder.empty()) folder += "/";
		
		VectorFileInfo result;
		getSystemFileList(result, folder, _mask);

		for (VectorFileInfo::const_iterator item = result.begin(); item != result.end(); ++item)
		{
			if (item->folder) continue;

			if (_fullpath)
				_result.push_back(folder + item->name);
			else
				_result.push_back(item->name);
		}

		if (_recursive)
		{
			getSystemFileList(result, folder, "*");

			for (VectorFileInfo::const_iterator item = result.begin(); item != result.end(); ++item)
			{
				if (!item->folder
					|| item->name == ".."
					|| item->name == ".") continue;
				scanFolder(_result, folder + item->name, _recursive, _mask, _fullpath);
			}

		}
	}
	
}


#endif // __FILE_SYSTEM_INFO_COCOCS2D_H__
