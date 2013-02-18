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

#ifndef GDX_CPP_BACKENDS_IOS_IOSGLU_HPP
#define GDX_CPP_BACKENDS_IOS_IOSGLU_HPP

#include <gdx-cpp/graphics/GL10.hpp>
#include <gdx-cpp/graphics/GLU.hpp>

namespace gdx {

namespace ios {

class IosGLU : public gdx::GLU
{
public:

    inline void gluLookAt (const GL10& gl,float eyeX,float eyeY,float eyeZ,float centerX,float centerY,float centerZ,float upX,float upY,float upZ) const {
        
    }
    inline void gluOrtho2D (const GL10& gl,float left,float right,float bottom,float top) const {
    }
    inline void gluPerspective (const GL10& gl,float fovy,float aspect,float zNear,float zFar) const {
    }
    inline bool gluProject (float objX,float objY,float objZ, float* model, float* projection, int* view, float* winX, float* winY, float* winZ) const {
    }
    inline bool gluUnProject (float winX,float winY,float winZ,float* model,float* proj, int* view,float* objX,float* objY,float* objZ) const {
    }
};

}

}

#endif // GDX_CPP_BACKENDS_NIX_LINUXGLU_HPP
