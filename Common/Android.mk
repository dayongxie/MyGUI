LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MyGUICommon

LOCAL_MODULE_FILENAME := libMyGUICommon

LOCAL_SRC_FILES := \
Base/Cocos2d/BaseManager.cpp \
Input/Cocos2d/InputManager.cpp \
FileSystemInfo/Cocos2d/FileSystemInfo_android.cpp \
Cocos2d/RenderBox/RenderBox.cpp

LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/ \
	$(LOCAL_PATH)/FileSystemInfo/Cocos2d \
	$(LOCAL_PATH)/Base/Cocos2d \
	$(LOCAL_PATH)/Input/Cocos2d

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/ \
	$(LOCAL_PATH)/Base/Cocos2d \
	$(LOCAL_PATH)/Input/Cocos2d

LOCAL_WHOLE_STATIC_LIBRARIES := \
	MyGUIPlatform

include $(BUILD_STATIC_LIBRARY)

$(call import-module,MyGUI/Platforms/Cocos2d/Cocos2dPlatform)
