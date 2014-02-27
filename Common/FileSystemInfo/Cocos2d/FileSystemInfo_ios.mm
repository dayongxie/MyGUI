#include "FileSystemInfo.h"

#include <cocos2d.h>
#include <Foundation/Foundation.h>

namespace common
{

	void getSystemFileList(VectorFileInfo& _result, const std::string& _folder, const std::string& _mask)
	{
		NSString *fullpath = nil;
        NSString *file = [NSString stringWithUTF8String:_mask.c_str()];
        NSString *folder = [NSString stringWithUTF8String:_folder.c_str()];
        NSString *resDir = [folder stringByDeletingPathExtension];

        if ( [folder isAbsolutePath] ) {
            fullpath = [NSBundle pathForResource:file
                                      ofType:nil
                                 inDirectory:resDir];
        } else {
            fullpath = [[NSBundle mainBundle] pathForResource:file
                                                       ofType:nil
                                                  inDirectory:resDir];
        }
        
        if (fullpath != nil)
            _result.push_back(FileInfo([file UTF8String], false));
	}
}
