LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MyGUIEngine

LOCAL_MODULE_FILENAME := libMyGUIEngine

LOCAL_SRC_FILES := \
src/MyGUI_Button.cpp \
src/MyGUI_Canvas.cpp \
src/MyGUI_ComboBox.cpp \
src/MyGUI_DDContainer.cpp \
src/MyGUI_EditBox.cpp \
src/MyGUI_ImageBox.cpp \
src/MyGUI_ImageSkin.cpp \
src/MyGUI_ItemBox.cpp \
src/MyGUI_ListBox.cpp \
src/MyGUI_MenuBar.cpp \
src/MyGUI_MenuControl.cpp \
src/MyGUI_MenuItem.cpp \
src/MyGUI_MultiListBox.cpp \
src/MyGUI_PopupMenu.cpp \
src/MyGUI_ProgressBar.cpp \
src/MyGUI_ScrollBar.cpp \
src/MyGUI_ScrollView.cpp \
src/MyGUI_TextBox.cpp \
src/MyGUI_TabControl.cpp \
src/MyGUI_TabItem.cpp \
src/MyGUI_MultiListItem.cpp \
src/MyGUI_Widget.cpp \
src/MyGUI_Window.cpp \
src/MyGUI_EditText.cpp \
src/MyGUI_MainSkin.cpp \
src/MyGUI_PolygonalSkin.cpp \
src/MyGUI_RotatingSkin.cpp \
src/MyGUI_SimpleText.cpp \
src/MyGUI_SubSkin.cpp \
src/MyGUI_TileRect.cpp \
src/MyGUI_LayerItem.cpp \
src/MyGUI_LayerNode.cpp \
src/MyGUI_OverlappedLayer.cpp \
src/MyGUI_RenderItem.cpp \
src/MyGUI_ScriptBridge.cpp \
src/MyGUI_SharedLayer.cpp \
src/MyGUI_SharedLayerNode.cpp \
src/MyGUI_SkinItem.cpp \
src/MyGUI_ActionController.cpp \
src/MyGUI_ControllerEdgeHide.cpp \
src/MyGUI_ControllerFadeAlpha.cpp \
src/MyGUI_ControllerPosition.cpp \
src/MyGUI_BackwardCompatibility.cpp \
src/MyGUI_Exception.cpp \
src/MyGUI_Precompiled.cpp \
src/MyGUI_BiIndexBase.cpp \
src/MyGUI_ScrollViewBase.cpp \
src/MyGUI_WidgetInput.cpp \
src/MyGUI_WidgetUserData.cpp \
src/MyGUI_ResourceImageSet.cpp \
src/MyGUI_ResourceImageSetPointer.cpp \
src/MyGUI_ResourceLayout.cpp \
src/MyGUI_ResourceManualFont.cpp \
src/MyGUI_ResourceManualPointer.cpp \
src/MyGUI_ResourceSkin.cpp \
src/MyGUI_ResourceTrueTypeFont.cpp \
src/MyGUI_ResourceNativeFont.cpp \
src/MyGUI_ChildSkinInfo.cpp \
src/MyGUI_MaskPickInfo.cpp\
src/MyGUI_SubWidgetBinding.cpp\
src/MyGUI_Any.cpp \
src/MyGUI_Colour.cpp \
src/MyGUI_ClipboardManager.cpp \
src/MyGUI_ControllerManager.cpp \
src/MyGUI_DataManager.cpp \
src/MyGUI_DynLibManager.cpp \
src/MyGUI_FactoryManager.cpp \
src/MyGUI_FontManager.cpp \
src/MyGUI_Gui.cpp \
src/MyGUI_IMEManager.cpp \
src/MyGUI_InputManager.cpp \
src/MyGUI_LanguageManager.cpp \
src/MyGUI_LayerManager.cpp \
src/MyGUI_LayoutManager.cpp \
src/MyGUI_PluginManager.cpp \
src/MyGUI_PointerManager.cpp \
src/MyGUI_RenderManager.cpp \
src/MyGUI_ResourceManager.cpp \
src/MyGUI_SkinManager.cpp \
src/MyGUI_SubWidgetManager.cpp \
src/MyGUI_ToolTipManager.cpp \
src/MyGUI_WidgetManager.cpp \
src/MyGUI_Constants.cpp \
src/MyGUI_DataFileStream.cpp \
src/MyGUI_DataStream.cpp \
src/MyGUI_DynLib.cpp \
src/MyGUI_GeometryUtility.cpp \
src/MyGUI_TextIterator.cpp \
src/MyGUI_TextureUtility.cpp \
src/MyGUI_TextView.cpp \
src/MyGUI_Timer.cpp \
src/MyGUI_UString.cpp \
src/MyGUI_XmlDocument.cpp \
src/MyGUI_ConsoleLogListener.cpp \
src/MyGUI_FileLogListener.cpp \
src/MyGUI_LevelLogFilter.cpp \
src/MyGUI_LogManager.cpp \
src/MyGUI_PathsManager.cpp \
src/MyGUI_LogSource.cpp 

LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/include

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/include

#LOCAL_LDLIBS := -lcocos2dx -lfreetype

LOCAL_WHOLE_STATIC_LIBRARIES := \
	cocos2dx_static

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

$(call import-module,cocos2dx)
$(call import-module,MyGUI/Common)
$(call import-module,MyGUI/Platforms/Cocos2d/Cocos2dPlatform)
