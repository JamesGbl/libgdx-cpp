
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

#include <stddef.h>
#include <memory>

#include "PixmapTextureData.hpp"
#include "gdx-cpp/Gdx.hpp"

using namespace gdx;

bool PixmapTextureData::disposePixmap () {
    return _disposePixmap;
}

Pixmap::ptr PixmapTextureData::getPixmap () {
    return pixmap;
}

int PixmapTextureData::getWidth () {
    return pixmap->getWidth();
}

int PixmapTextureData::getHeight () {
    return pixmap->getHeight();
}

const Pixmap::Format* PixmapTextureData::getFormat () {
    return &format;
}

bool PixmapTextureData::useMipMaps () {
    return _useMipMaps;
}

bool PixmapTextureData::isManaged () {
    return false;
}

const TextureData::TextureDataType& PixmapTextureData::getType () {
    return TextureDataType::Pixmap;
}

void PixmapTextureData::uploadCompressedData () {
    gdx_log_error(__FILE__, "This TextureData implementation does not upload data itself");
}

PixmapTextureData::PixmapTextureData(Pixmap::ptr _pixmap,
                                     const Pixmap::Format* format,
                                     bool useMipMaps, bool disposePixmap)
: pixmap(_pixmap),
format(format == nullptr ? _pixmap->getFormat() : *format),
_useMipMaps(useMipMaps),
_disposePixmap(disposePixmap)
{
}


