# set params
DEPS_ROOT="../../../../"
COCOS2DX_ROOT="${DEPS_ROOT}/cocos2d-x"
MYGUI_ROOT="${DEPS_ROOT}/MyGUI"

#export NDK_MODULE_PATH=${COCOS2D_ROOT}:${DEPS_ROOT}:${COCOS2D_ROOT}/cocos2dx/platform/third_party/android/prebuilt
# try to get global variable
if [ $NDK_ROOT"aaa" != "aaa" ]; then
echo "use global definition of NDK_ROOT: $NDK_ROOT"
NDK_ROOT_LOCAL=$NDK_ROOT
fi

if [ $COCOS2DX_ROOT"aaa" != "aaa" ]; then
echo "use global definition of COCOS2DX_ROOT: $COCOS2DX_ROOT"
COCOS2DX_ROOT_LOCAL=$COCOS2DX_ROOT
fi

if [[ $buildexternalsfromsource ]]; then
echo "Building external dependencies from source"
NDK_MODULE_PATH=${COCOS2DX_ROOT}:$DEPS_ROOT:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/source
else
echo "Using prebuilt externals"
NDK_MODULE_PATH=${COCOS2DX_ROOT}:$DEPS_ROOT:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/prebuilt
fi

export NDK_MODULE_PATH
