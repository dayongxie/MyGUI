//------------------------------------------------------------------------------------
// 文件名：		MyGUI_PathsManager.h
// 内	容：	
// 说	明：	
// 创建日期：	2013.06.09
// 创建人：		mazp
// 版权所有：	幻星信息技术
//------------------------------------------------------------------------------------
#ifndef __MYGUI_PATHS_MANAGER_H__
#define __MYGUI_PATHS_MANAGER_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_Singleton.h"
#include "MyGUI_XmlDocument.h"
#include "MyGUI_Delegate.h"
#include "MyGUI_Types.h"
#include "MyGUI_BackwardCompatibility.h"

namespace MyGUI
{

	class MYGUI_EXPORT PathsManager :
		public Singleton<PathsManager>,
		public MemberObsolete<PathsManager>
	{
	public:
		PathsManager();

		void initialise();
		void shutdown();

		/** Get path value */
		const std::string& getPath(const std::string& _tag);

	private:
		bool loadPaths(const std::string& _file);

	private:
		typedef std::map<std::string, std::string> MapPathString;

		MapPathString mMapPath;
		bool mIsInitialise;
		std::string mFileName;
	};

} // namespace MyGUI

#endif // __MYGUI_PATHS_MANAGER_H__
