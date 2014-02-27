# set params
RESOURCE_SRC=../Resources
RESOURCE_ROOT=.

DEPS_ROOT="../../../.."
COCOS2D_ROOT="${DEPS_ROOT}/cocos2d-x"
MYGUI_ROOT="${DEPS_ROOT}/MyGUI"

# make sure assets is exist
if [ -d $RESOURCE_ROOT/assets ]; then
    rm -rf $RESOURCE_ROOT/assets
fi

mkdir $RESOURCE_ROOT/assets
cp -af $RESOURCE_SRC/* $RESOURCE_ROOT/assets

#find . -name "*.ttf" -exec mv {} {}.png \;

# build
export NDK_MODULE_PATH=${COCOS2D_ROOT}:${DEPS_ROOT}:${COCOS2D_ROOT}/cocos2dx/platform/third_party/android/prebuilt



if [ `basename $0` == "build_native.sh" ]; then
	$NDK_ROOT/ndk-build -C $RESOURCE_ROOT $*
fi

