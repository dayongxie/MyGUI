#include "FileSystemInfo.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cocos2d.h>
#include "support/zip_support/unzip.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"

using namespace cocos2d;

namespace common
{
	static void getFileListFromZip(VectorFileInfo& _result, const char*_zipfile,  const std::string& _folder, const std::string& _mask);

	static void getFileListFromSys(VectorFileInfo& _result, const std::string& _folder, const std::string& _mask)
	{
		DIR* dir = opendir(_folder.c_str());
		struct dirent* dp;

		if (dir == NULL)
		{
			return;
		}

		rewinddir (dir);

		while ((dp = readdir (dir)) != NULL)
		{
			if (dp->d_name[0] != '.')
			{
				if (_mask.empty() || (_mask == dp->d_name))
					_result.push_back(FileInfo(dp->d_name, dp->d_type & DT_DIR));
			}
		}

		closedir(dir);
	}

	void getSystemFileList(VectorFileInfo& _result, const std::string& _folder, const std::string& _mask)
	{
		const std::vector<std::string>& paths = CCFileUtils::sharedFileUtils()->getSearchPaths();

		for (unsigned i = 0; i < paths.size(); ++i)
		{
			if (paths[i][0] == '/')
			{
				getFileListFromSys(_result, paths[i] + _folder, _mask);
			}
			else
			{
				getFileListFromZip(_result, getApkPath(), paths[i] + _folder, _mask);
			}
		}
	}

	void getFileListFromZip(VectorFileInfo& _result, const char*_zipfile,  const std::string& _folder, const std::string& filename)
	{
		unzFile pFile = NULL;
		std::string path = _folder + filename;
		bool isDir = false;
		
		pFile = unzOpen(_zipfile);
		if (!pFile)
			return;

		do
		{
			int nRet = unzLocateFile(pFile, path.c_str(), 1);
			CC_BREAK_IF(UNZ_OK != nRet);
			
			char szFilePathA[260];
			unz_file_info unzInfo;
			nRet = unzGetCurrentFileInfo(pFile, &unzInfo, szFilePathA, sizeof(szFilePathA), NULL, 0, NULL, 0);
			CC_BREAK_IF(UNZ_OK != nRet);
			
			if (szFilePathA[unzInfo.size_filename - 1] == '/' ||
			    szFilePathA[unzInfo.size_filename - 1] == '\\')
				isDir = true;
			else
				isDir = false;
				
			_result.push_back(FileInfo(filename, isDir));
		} while (0);
		
		unzClose(pFile);
	}

}
