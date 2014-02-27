LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MyGUIPlatform

LOCAL_MODULE_FILENAME := libMyGUIPlatform

LOCAL_SRC_FILES := \
src/MyGUI_Cocos2dPlatform.cpp \
src/MyGUI_Cocos2dIMEManager.cpp \
src/MyGUI_Cocos2dDataManager.cpp \
src/MyGUI_Cocos2dLogManager.cpp \
src/MyGUI_Cocos2dRenderManager.cpp \
src/MyGUI_Cocos2dRTTexture.cpp \
src/MyGUI_Cocos2dTexture.cpp \
src/MyGUI_Cocos2dVertexBuffer.cpp \
src/MyGUI_Cocos2dFont.cpp


LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/include

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/include \
	$(LOCAL_PATH)/../../../Common

#LOCAL_LDLIBS := -lcocos2dx

LOCAL_WHOLE_STATIC_LIBRARIES := \
	MyGUIEngine \
	cocos2dx_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,MyGUI/MyGUIEngine)
