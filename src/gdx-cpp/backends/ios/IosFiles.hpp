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
 *  @author Ozires Bortolon de Faria ozires@aevumlab.com
 *  @author aevum team
 */

#ifndef GDX_CPP_BACKENDS_IOS_IOSFILES_HPP
#define GDX_CPP_BACKENDS_IOS_IOSFILES_HPP

#include <gdx-cpp/Files.hpp>
#include <gdx-cpp/files/FileHandle.hpp>

namespace gdx {

class Files;

namespace ios {

  class IosFiles : public gdx::Files
  {
    public:
        //Override
      gdx::FileHandle::ptr getFileHandle (const std::string &fileName, gdx::Files::FileType type);

        //Override
        gdx::FileHandle::ptr internal (const std::string &path);

        //Override
        gdx::FileHandle::ptr external (const std::string &path);

        //Override
        gdx::FileHandle::ptr absolute (const std::string &path);
      
        gdx::FileHandle::ptr internal_private(const std::string &path);

        //Override
        std::string getExternalStoragePath ();

        //Override
        bool isExternalStorageAvailable ();
    private:
        std::string externalPath;
        
  };
    
}
    
}

#endif // GDX_CPP_BACKENDS_IOS_IOSFILES_HPP