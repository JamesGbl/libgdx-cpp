/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 */

#include "IosFileHandle.hpp"
#import <UIKit/UIKit.h>
#include <stdexcept>

using namespace gdx_cpp::backends::ios;

IosFileHandle::IosFileHandle(const std::string& fileName, gdx_cpp::Files::FileType type)
: gdx_cpp::files::FileHandle(fileName, type)
{	
}

int IosFileHandle::readBytes(gdx_cpp::files::FileHandle::buffer_ptr& c) const {
	if (this->type == Files::Internal) {		
          
       NSString* filePath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String: file.nameWithoutExtension().c_str()] ofType:[NSString stringWithUTF8String: file.extension().c_str()]
                                                            inDirectory:[NSString stringWithUTF8String: file.getParent().c_str()]];
          
        if (filePath == nil) {            
            NSString* documentsPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
            
            filePath = [NSString stringWithFormat:@"%@/%s", 
                                  documentsPath, name().c_str()];
        }
        
		if (filePath) {
			NSData* data = [NSData dataWithContentsOfFile:filePath];
			if (data) {
				NSUInteger len = [data length];
				Byte *byteData = new Byte[len];
				memcpy(byteData, [data bytes], len);
				
				gdx_cpp::files::FileHandle::buffer_ptr new_ptr((char*) byteData, shared_ptr_array_deleter());
				c.swap(new_ptr);
				
				return len;
			}
		}
		throw std::runtime_error("Failed to load contents of file: " + this->file.getAbsolutePath());
	}
	throw std::runtime_error("Not implemented yet");
}

bool IosFileHandle::exists() const {
    NSString* documentsPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];

    return [[NSFileManager defaultManager] fileExistsAtPath:[documentsPath stringByAppendingPathComponent:[NSString stringWithUTF8String:name().c_str()]]];
}

int IosFileHandle::write(const char *data, int lenght, bool append) {
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    
    NSString *fileName = [NSString stringWithFormat:@"%@/%s", 
                          documentsDirectory, name().c_str()];
    
    NSData* nsData = [NSData dataWithBytes:(void*)data length:lenght];
    
    [nsData writeToFile:fileName atomically:YES];
    
    return lenght;
}
