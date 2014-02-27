//------------------------------------------------------------------------------------
// �ļ�����		MyGUI_PathsManager.h
// ��	�ݣ�	
// ˵	����	
// �������ڣ�	2013.06.09
// �����ˣ�		mazp
// ��Ȩ���У�	������Ϣ����
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
