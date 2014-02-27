set (PROJECTNAME MyGUI.Cocos2dPlatform)

include_directories(
 include
 ${MYGUI_SOURCE_DIR}/MyGUIEngine/include
 ${COCOS2D_INCLUDE_DIR}
 ${COCOS2D_SOURCE_DIR}/kazmath/include
 ${MYGUI_SOURCE_DIR}/Common
)

include(${PROJECTNAME}.list)

add_definitions(-DGL_GLEXT_PROTOTYPES)

add_library(${PROJECTNAME} ${HEADER_FILES} ${SOURCE_FILES})

add_dependencies(${PROJECTNAME} MyGUIEngine)

target_link_libraries(${PROJECTNAME} ${COCOS2D_LIBRARIES} ${OPENGL_LIBRARIES})
link_directories(${COCOS2D_LIB_DIR})
MESSAGE(STATUS "======================${OPENGL_LIBRARIES}=====")
# installation rules
install(FILES ${HEADER_FILES}
        DESTINATION include/MYGUI
)
mygui_install_target(${PROJECTNAME} "")
