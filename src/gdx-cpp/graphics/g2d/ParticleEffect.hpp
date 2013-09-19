
/*
    Copyright 2011 Aevum Software aevum @ aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
    @author Ozires Bortolon de Faria ozires@aevumlab.com
*/

#ifndef GDX_CPP_GRAPHICS_G2D_PARTICLEEFFECT_HPP_
#define GDX_CPP_GRAPHICS_G2D_PARTICLEEFFECT_HPP_
#include <string>
#include <vector>

#include "gdx-cpp/files/File.hpp"
#include "gdx-cpp/files/FileHandle.hpp"
#include "gdx-cpp/graphics/Texture.hpp"
#include "gdx-cpp/internal/memory"
#include "gdx-cpp/utils/Disposable.hpp"

namespace gdx {
class File;
class FileHandle;
class ParticleEmitter;
class SpriteBatch;
class TextureAtlas;

class ParticleEffect: public Disposable {
public:

    ParticleEffect ();
    ParticleEffect (ParticleEffect& effect);
    ~ParticleEffect();
    void start ();
    void update (float delta);
    void draw (SpriteBatch& spriteBatch);
    void draw (SpriteBatch& spriteBatch,float delta);
    void allowCompletion ();
    bool isComplete ();
    void setDuration (int duration);
    void setPosition (float x,float y);
    void setFlip (bool flipX,bool flipY);
    std::vector< ParticleEmitter* >& getEmitters ();
    ParticleEmitter* findEmitter (const std::string& name);
    void save (const File& file);
    void load (std::string file);
    void load (const FileHandle& effectFile,const FileHandle& imagesDir);
    void load (const FileHandle& effectFile,const TextureAtlas& atlas);
    void loadEmitters (const FileHandle& effectFile);
    void loadEmittersTest (std::string file);
    void loadEmitterImages (const TextureAtlas& atlas);
    void loadEmitterImages (const FileHandle& imagesDir);
    void loadEmitterImagesTest ();
    void dispose () override;

protected:
    Texture::ptr loadTexture (const FileHandle::ptr file);

private:
    std::vector<ParticleEmitter *> emitters;
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_G2D_PARTICLEEFFECT_HPP_
