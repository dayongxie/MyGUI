#include "MyGUI_Precompiled.h"
#include "MyGUI_ScriptBridge.h"
#include "MyGUI.h"

namespace MyGUI
{

	LuaDelegate::~LuaDelegate()
	{
		clearScriptHandler();
	}

	int LuaDelegate::addScriptHandler(int handlerId)
	{
		for (unsigned i = 0; i < mHandlers.size(); ++i)
		{
			if (mHandlers[i] == handlerId)
				return handlerId;
		}

		mHandlers.push_back(handlerId);
		return handlerId;
	}

	void LuaDelegate::removeScriptHandler(int handlerId)
	{
		for (unsigned i = 0; i < mHandlers.size(); ++i)
		{
			if (mHandlers[i] == handlerId)
			{
				mHandlers[i] = LUA_NIL_HANDER;
			}
		}

		ScriptBridge::getInstance().mProtocol->removeScriptHandler(handlerId);
	}

	void LuaDelegate::clearScriptHandler()
	{
		if (!ScriptBridge::getInstancePtr()) return;

		ScriptProtocol* scriptImp = ScriptBridge::getInstance().mProtocol;
		if (!scriptImp)
		{
			return;
		}

		for (unsigned i = 0; i < mHandlers.size(); ++i)
		{
			if (mHandlers[i] != LUA_NIL_HANDER)
			{
				scriptImp->removeScriptHandler(mHandlers[i]);
			}
		}

		mHandlers.clear();
	}

	void LuaDelegate::merge_handlers()
	{
		LuaDelegateList::iterator iter = mHandlers.begin();
		while (iter != mHandlers.end())
		{
			if (LUA_NIL_HANDER == (*iter))
			{
				iter = mHandlers.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	template <> ScriptBridge* Singleton<ScriptBridge>::msInstance = nullptr;
	template <> const char* Singleton<ScriptBridge>::mClassTypeName = "ScriptBridge";

	ScriptBridge::ScriptBridge()
		:mProtocol(nullptr)
	{

	}

	ScriptBridge::~ScriptBridge()
	{

	}

	void ScriptBridge::prepare(int handlerId)
	{
		if (mProtocol) mProtocol->prepare(handlerId);
	}

	void ScriptBridge::exec(int handlerId,int nArgs)
	{
		if (mProtocol) mProtocol->exec(handlerId,nArgs);
	}

} // namespace MyGUI
