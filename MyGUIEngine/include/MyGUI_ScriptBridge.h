#ifndef MYGUI_SCRIPT_BRIDGE_H
#define MYGUI_SCRIPT_BRIDGE_H

#include "MyGUI_Prerequest.h"
#include "MyGUI_Singleton.h"
#include <typeinfo>

namespace MyGUI
{
	class IObject;
	class ControllerItem;

	class MYGUI_EXPORT LuaDelegate
	{
	public:
		~LuaDelegate();
		typedef std::vector<int> LuaDelegateList;

		int addScriptHandler(int handlerId);
		void removeScriptHandler(int handlerId);

		void clearScriptHandler();
	protected:
		void merge_handlers();

		LuaDelegateList mHandlers;
		LuaDelegateList mHandlersQueue;
	};

	class ScriptProtocol
	{
	public:
		virtual void removeScriptHandler(int handler) = 0;

		virtual void pushInt(int value) = 0;
		virtual void pushBool(bool value) = 0;
		virtual void pushFloat(float value) = 0;
		virtual void pushLongLong(long long a) = 0;
		virtual void pushString(const std::string& value) = 0;
		virtual void pushMyGUIObj(IObject* value) = 0;
		virtual void pushUserType(void* value, const char* name) = 0;
		virtual void pushRTTI(void* value, const char* name) = 0;

		virtual void prepare(int handlerId) = 0;
		virtual void exec(int handlerId,int nArgs) = 0;
	};

	class MYGUI_EXPORT ScriptBridge :
		public Singleton<ScriptBridge>
	{
	public:
		ScriptBridge();
		~ScriptBridge();

		void setScriptHandler(ScriptProtocol* handler)
		{
			mProtocol = handler;
		}

		template <typename T>
		void push(T arg)
		{
			mProtocol->pushRTTI((void*)&arg, typeid(arg).name());
		}

		void prepare(int handlerId);
		void exec(int handlerId,int nArgs);

		template <typename TP1, typename TP2, typename TP3, typename TP4, typename TP5, typename TP6>
		void invoke(int handlerId, TP1 p1, TP2 p2, TP3 p3, TP4 p4, TP5 p5, TP6 p6)
		{
			prepare(handlerId);

			push<TP1>(p1);
			push<TP2>(p2);
			push<TP3>(p3);
			push<TP4>(p4);
			push<TP5>(p5);
			push<TP6>(p6);

			exec(handlerId,6);
		}

		template <typename TP1, typename TP2, typename TP3, typename TP4, typename TP5>
		void invoke(int handlerId, TP1 p1, TP2 p2, TP3 p3, TP4 p4, TP5 p5)
		{
			prepare(handlerId);
			push<TP1>(p1);
			push<TP2>(p2);
			push<TP3>(p3);
			push<TP4>(p4);
			push<TP5>(p5);
			exec(handlerId,5);
		}

		template <typename TP1, typename TP2, typename TP3, typename TP4>
		void invoke(int handlerId, TP1 p1, TP2 p2, TP3 p3, TP4 p4)
		{
			prepare(handlerId);
			push<TP1>(p1);
			push<TP2>(p2);
			push<TP3>(p3);
			push<TP4>(p4);
			exec(handlerId,4);
		}

		template <typename TP1, typename TP2, typename TP3>
		void invoke(int handlerId, TP1 p1, TP2 p2, TP3 p3)
		{
			prepare(handlerId);
			push<TP1>(p1);
			push<TP2>(p2);
			push<TP3>(p3);
			exec(handlerId,3);
		}

		template <typename TP1, typename TP2>
		void invoke(int handlerId, TP1 p1, TP2 p2)
		{
			prepare(handlerId);
			push<TP1>(p1);
			push<TP2>(p2);
			exec(handlerId,2);
		}

		template <typename TP1>
		void invoke(int handlerId, TP1 p1)
		{
			prepare(handlerId);
			push<TP1>(p1);
			exec(handlerId,1);
		}

		void invoke(int handlerId)
		{
			prepare(handlerId);
			exec(handlerId,0);
		}

		ScriptProtocol* mProtocol;
	};



	template <>
	inline void ScriptBridge::push<int>(int arg)
	{ mProtocol->pushInt(arg); }

	template <>
	inline void ScriptBridge::push<unsigned int>(unsigned int arg)
	{ mProtocol->pushInt(arg); }

	template <>
	inline void ScriptBridge::push<bool>(bool arg)
	{ mProtocol->pushBool(arg); }

	template <>
	inline void ScriptBridge::push<float>(float arg)
	{ mProtocol->pushFloat(arg); }

	template<>
	inline void ::MyGUI::ScriptBridge::push<long long>(long long arg)
	{
		mProtocol->pushLongLong(arg);
	}

	template<>
	inline void ScriptBridge::push<const char*>(const char* arg)
	{ mProtocol->pushString(arg); }

	template<>
	inline void ScriptBridge::push<std::string>(std::string arg)
	{ mProtocol->pushString(arg); }

	template<>
	inline void ScriptBridge::push<const std::string&>(const std::string& arg)
	{ mProtocol->pushString(arg); }

#define SCRIPTBRIDGE_SPEC_MYGUIOBJ(CLASS) \
	template<>	\
	inline void ScriptBridge::push(CLASS* arg)	\
	{ mProtocol->pushMyGUIObj((IObject*)arg); }

	SCRIPTBRIDGE_SPEC_MYGUIOBJ(Widget)
	SCRIPTBRIDGE_SPEC_MYGUIOBJ(EditBox)
	SCRIPTBRIDGE_SPEC_MYGUIOBJ(Window)
	SCRIPTBRIDGE_SPEC_MYGUIOBJ(ScrollBar)
	SCRIPTBRIDGE_SPEC_MYGUIOBJ(TabControl)
	SCRIPTBRIDGE_SPEC_MYGUIOBJ(MenuItem)
	SCRIPTBRIDGE_SPEC_MYGUIOBJ(MenuControl)
	SCRIPTBRIDGE_SPEC_MYGUIOBJ(ListBox)
	SCRIPTBRIDGE_SPEC_MYGUIOBJ(MultiListBox)
	SCRIPTBRIDGE_SPEC_MYGUIOBJ(DDContainer)
	SCRIPTBRIDGE_SPEC_MYGUIOBJ(ItemBox)
	SCRIPTBRIDGE_SPEC_MYGUIOBJ(Canvas)
	SCRIPTBRIDGE_SPEC_MYGUIOBJ(ComboBox)
	SCRIPTBRIDGE_SPEC_MYGUIOBJ(ControllerItem)

#define SCRIPTBRIDGE_SPEC_CLASSPTR(CLASS) \
	template<> \
	inline void ScriptBridge::push(CLASS* arg) \
	{ \
		mProtocol->pushUserType(arg, #CLASS); \
	}

#define SCRIPTBRIDGE_SPEC_CLASSREF(CLASS) \
	template<> \
	inline void ScriptBridge::push(CLASS& arg) \
	{ \
	mProtocol->pushUserType(&arg, #CLASS); \
	}

}
#endif //MYGUI_SCRIPT_BRIDGE_H
