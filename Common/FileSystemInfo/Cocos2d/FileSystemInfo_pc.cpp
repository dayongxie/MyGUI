#include "FileSystemInfo.h"

#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
#include <windows.h>
#include <io.h>
#else
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

using namespace cocos2d;

namespace common
{
	void getSystemFileList(VectorFileInfo& _result, const std::string& _folder, const std::string& _mask)
	{
#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
		//FIXME add optional parameter?
		bool ms_IgnoreHidden = true;

		long lHandle, res;
		struct _finddata_t tagData;

		// pattern can contain a directory name, separate it from mask
		size_t pos = _mask.find_last_of("/\\");
		std::string directory;
		if (pos != _mask.npos)
			directory = _mask.substr (0, pos);

		std::string folder = CCFileUtils::sharedFileUtils()->fullPathForFilename(_folder.c_str());
		std::string full_mask = concatenatePath(folder, _mask);
		
		lHandle = _findfirst(full_mask.c_str(), &tagData);
		res = 0;
		while (lHandle != -1 && res != -1)
		{
			if (( !ms_IgnoreHidden || (tagData.attrib & _A_HIDDEN) == 0 ) &&
				!isReservedDir(tagData.name))
			{
				_result.push_back(FileInfo(concatenatePath(directory, tagData.name), (tagData.attrib & _A_SUBDIR) != 0));
			}
			res = _findnext( lHandle, &tagData );
		}
		// Close if we found any files
		if (lHandle != -1)
			_findclose(lHandle);
#else
		DIR* dir = opendir(_folder.c_str());
		struct dirent* dp;

		if (dir == NULL)
		{
			/* opendir() failed */
		}

		rewinddir (dir);

		while ((dp = readdir (dir)) != NULL)
		{
			if (!isReservedDir(dp->d_name))
			{
				struct stat fInfo;
				char path[NAME_MAX];
				//snprintf(path, NAME_MAX, "%s/%s", MyGUI::UString(_folder).asUTF8_c_str(), dp->d_name);
				if(stat(path, &fInfo) == -1)perror("stat");
				_result.push_back(FileInfo(dp->d_name, (S_ISDIR(fInfo.st_mode))));
			}
		}

		closedir(dir);
#endif
	}

}
