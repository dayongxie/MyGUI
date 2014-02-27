function(mygui_add_base_manager_source PLATFORM)
	include_directories(Base/${PLATFORM})
	
	if (MYGUI_RENDERSYSTEM EQUAL 7)
		set (HEADER_FILES ${HEADER_FILES} 
			Base/${PLATFORM}/BaseManager.h
			FileSystemInfo/${PLATFORM}/FileSystemInfo.h
			Cocos2d/RenderBox/RenderBox.h
			PARENT_SCOPE)
			
		set (SOURCE_FILES ${SOURCE_FILES}
			Base/${PLATFORM}/BaseManager.cpp
			FileSystemInfo/${PLATFORM}/FileSystemInfo_pc.cpp
			Cocos2d/RenderBox/RenderBox.cpp
			PARENT_SCOPE)
	else()
		set (HEADER_FILES ${HEADER_FILES}
			Base/${PLATFORM}/BaseManager.h
			FileSystemInfo/Default/FileSystemInfo.h
			PARENT_SCOPE)
		set (SOURCE_FILES ${SOURCE_FILES}
			Base/${PLATFORM}/BaseManager.cpp
			PARENT_SCOPE)
	endif()
	
	SOURCE_GROUP("Base" FILES
		Base/${PLATFORM}/BaseManager.h
		Base/${PLATFORM}/BaseManager.cpp
	)
	
endfunction(mygui_add_base_manager_source)

function(mygui_add_input_source PLATFORM)
	include_directories(Input/${PLATFORM})
	set (HEADER_FILES ${HEADER_FILES}
		Input/${PLATFORM}/InputManager.h
		Input/${PLATFORM}/PointerManager.h
		PARENT_SCOPE)
	set (SOURCE_FILES ${SOURCE_FILES}
		Input/${PLATFORM}/InputManager.cpp
		Input/${PLATFORM}/PointerManager.cpp
		PARENT_SCOPE)
	SOURCE_GROUP("Base" FILES
		Input/${PLATFORM}/InputManager.h
		Input/${PLATFORM}/InputManager.cpp
		Input/${PLATFORM}/PointerManager.h
		Input/${PLATFORM}/PointerManager.cpp
	)
endfunction(mygui_add_input_source)

set (PROJECTNAME Common)

include_directories(
	.
	${MYGUI_SOURCE_DIR}/Common
	${MYGUI_SOURCE_DIR}/MyGUIEngine/include
)

set (HEADER_FILES "")
set (SOURCE_FILES "")

if(MYGUI_RENDERSYSTEM EQUAL 1)
	mygui_add_base_manager_source(Dummy)
	add_definitions("-DMYGUI_DUMMY_PLATFORM")
	include_directories(
		${MYGUI_SOURCE_DIR}/Platforms/Dummy/DummyPlatform/include
	)
	link_directories(${DUMMY_LIB_DIR})
elseif(MYGUI_RENDERSYSTEM EQUAL 3)
	mygui_add_base_manager_source(Ogre)
	add_definitions("-DMYGUI_OGRE_PLATFORM")
	include_directories(
		${MYGUI_SOURCE_DIR}/Platforms/Ogre/OgrePlatform/include
		${OGRE_INCLUDE_DIR}
	)
	link_directories(${OGRE_LIB_DIR})
elseif(MYGUI_RENDERSYSTEM EQUAL 4)
	mygui_add_base_manager_source(OpenGL)
	add_definitions("-DMYGUI_OPENGL_PLATFORM")
	include_directories(
		${MYGUI_SOURCE_DIR}/Platforms/OpenGL/OpenGLPlatform/include
		${OPENGL_INCLUDE_DIR}
	)
	link_directories(${OPENGL_LIB_DIR})
elseif(MYGUI_RENDERSYSTEM EQUAL 5)
	mygui_add_base_manager_source(DirectX)
	add_definitions("-DMYGUI_DIRECTX_PLATFORM")
	include_directories(
		${MYGUI_SOURCE_DIR}/Platforms/DirectX/DirectXPlatform/include
		${DirectX_INCLUDE_DIR}
	)
	link_directories(${DIRECTX_LIB_DIR})
elseif(MYGUI_RENDERSYSTEM EQUAL 6)
	mygui_add_base_manager_source(DirectX11)
	add_definitions("-DMYGUI_DIRECTX11_PLATFORM")
	include_directories(
		${MYGUI_SOURCE_DIR}/Platforms/DirectX11/DirectX11Platform/include
		${DirectX_INCLUDE_DIR}
	)
	link_directories(${DIRECTX_LIB_DIR})
elseif(MYGUI_RENDERSYSTEM EQUAL 7)
	mygui_add_base_manager_source(Cocos2d)
	add_definitions("-DMYGUI_COCOS2D_PLATFORM -DUNICODE -D_UNICODE")
	include_directories(
		${MYGUI_SOURCE_DIR}/Platforms/Cocos2d/Cocos2dPlatform/include
		${COCOS2D_INCLUDE_DIR}
		${COCOS2D_SOURCE_DIR}/kazmath/include
	)
endif()

if(MYGUI_SAMPLES_INPUT EQUAL 1)
	include_directories(${OIS_INCLUDE_DIRS})
	mygui_add_input_source(OIS)
elseif(MYGUI_SAMPLES_INPUT EQUAL 2)
	mygui_add_input_source(Win32)
elseif(MYGUI_SAMPLES_INPUT EQUAL 3)
	include_directories(${OIS_INCLUDE_DIRS})
	mygui_add_input_source(Win32_OIS)
elseif(MYGUI_SAMPLES_INPUT EQUAL 4)
	mygui_add_input_source(Cocos2d)
endif()

add_library(${PROJECTNAME} ${HEADER_FILES} ${SOURCE_FILES})

if(MYGUI_RENDERSYSTEM EQUAL 1)
	add_dependencies(${PROJECTNAME} MyGUI.DummyPlatform)
	target_link_libraries(${PROJECTNAME} MyGUI.DummyPlatform)
elseif(MYGUI_RENDERSYSTEM EQUAL 3)
	add_dependencies(${PROJECTNAME} MyGUI.OgrePlatform)
	target_link_libraries(${PROJECTNAME} MyGUI.OgrePlatform)
elseif(MYGUI_RENDERSYSTEM EQUAL 4)
	add_dependencies(${PROJECTNAME} MyGUI.OpenGLPlatform)
	target_link_libraries(${PROJECTNAME} MyGUI.OpenGLPlatform)
elseif(MYGUI_RENDERSYSTEM EQUAL 5)
	add_dependencies(${PROJECTNAME} MyGUI.DirectXPlatform)
	target_link_libraries(${PROJECTNAME} MyGUI.DirectXPlatform)
elseif(MYGUI_RENDERSYSTEM EQUAL 6)
	add_dependencies(${PROJECTNAME} MyGUI.DirectX11Platform)
	target_link_libraries(${PROJECTNAME} MyGUI.DirectX11Platform)
elseif(MYGUI_RENDERSYSTEM EQUAL 7)
	add_dependencies(${PROJECTNAME} MyGUI.Cocos2dPlatform)
	target_link_libraries(${PROJECTNAME} MyGUI.Cocos2dPlatform)
endif()

add_dependencies(${PROJECTNAME} MyGUIEngine)

if(MYGUI_SAMPLES_INPUT EQUAL 1)
	add_definitions("-DMYGUI_SAMPLES_INPUT_OIS")
	link_directories(${OIS_LIB_DIR})
	target_link_libraries(${PROJECTNAME} ${OIS_LIBRARIES})
elseif(MYGUI_SAMPLES_INPUT EQUAL 2)
	add_definitions("-DMYGUI_SAMPLES_INPUT_WIN32")
elseif(MYGUI_SAMPLES_INPUT EQUAL 3)
	add_definitions("-DMYGUI_SAMPLES_INPUT_WIN32_OIS")
	link_directories(${OIS_LIB_DIR})
	target_link_libraries(${PROJECTNAME} ${OIS_LIBRARIES})
elseif(MYGUI_SAMPLES_INPUT EQUAL 4)
	add_definitions("-DMYGUI_SAMPLES_INPUT_COCOS2D")
endif()
