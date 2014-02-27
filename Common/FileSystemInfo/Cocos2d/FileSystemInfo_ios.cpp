#include "FileSystemInfo.h"

#include <cocos2d.h>

namespace common
{

	void getSystemFileList(VectorFileInfo& _result, const std::wstring& _folder, const std::wstring& _mask)
	{
		DIR* dir = opendir(MyGUI::UString(_folder).asUTF8_c_str());
		struct dirent* dp;
		
		if (dir == NULL)
			return;

		rewinddir(dir);

		while ((dp = readdir (dir)) != NULL)
		{
			if (!isReservedDir(MyGUI::UString(dp->d_name).asWStr_c_str()))
			{
				struct stat fInfo;
				char path[NAME_MAX];

				if (strcmp(dp->d_name, MyGUI::UString(_folder).asUTF8_c_str()) == 0)
				{
					snprintf(path, sizeof(path), "%s/%s", MYGUI::UString(_folder).asUTF8_c_str(), dp->d_name);
					if (stat(path, &fInfo) == -1) continue;
					
					_result.push_back(FileInfo(MyGUI::UString(dp->d_name).asWStr(), (S_ISDIR(fInfo.st_mode))));
				}
			}
		}
	}

}
