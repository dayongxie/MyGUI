LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := \
	helloworld/main.cpp \
	../../Classes/DemoKeeper.cpp \
	../../Classes/HelloWorldScene.cpp \
	../../Classes/ColourWindow.cpp \
	../../Classes/ColourWindowBox.cpp \
	../../Classes/ColourWindowCellView.cpp \
	../../Classes/EditorWindow.cpp \
	../../Classes/InformationWindow.cpp \
	../../Classes/MainPanel.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := \
	cocos2dx_static \
	cocosdenshion_static \
	box2d_static \
	cocos_lua_static \
	MyGUIEngine \
	MyGUIPlatform \
	MyGUICommon

include $(BUILD_SHARED_LIBRARY)

$(call import-module,MyGUI/MyGUIEngine)
$(call import-module,MyGUI/Common)
$(call import-module,MyGUI/Platforms/Cocos2d/Cocos2dPlatform)

$(call import-module,CocosDenshion/android)
$(call import-module,cocos2dx)
$(call import-module,extensions)
$(call import-module,external/Box2D)

