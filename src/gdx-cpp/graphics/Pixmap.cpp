
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

#include "Pixmap.hpp"

#include "gdx-cpp/graphics/g2d/Gdx2DPixmap.hpp"
#include "Color.hpp"
#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/files/FileHandle.hpp"

#include <cassert>

using namespace gdx_cpp::graphics;

Pixmap::Blending Pixmap::blending = SourceOver;

const Pixmap::Format Pixmap::Format::Alpha;
const Pixmap::Format Pixmap::Format::LuminanceAlpha;
const Pixmap::Format Pixmap::Format::RGB565;
const Pixmap::Format Pixmap::Format::RGBA4444;
const Pixmap::Format Pixmap::Format::RGB888;
const Pixmap::Format Pixmap::Format::RGBA8888;

void Pixmap::setBlending (const Blending& blending) {
    Pixmap::blending = blending;
    g2d::Gdx2DPixmap::setBlend(blending == Pixmap::None ? 0 : 1);
}

void Pixmap::setFilter (const Filter& filter) {
    g2d::Gdx2DPixmap::setScale(filter == NearestNeighbour ? GDX2D_SCALE_NEAREST : g2d::Gdx2DPixmap::GDX2D_SCALE_LINEAR);
}

void Pixmap::setColor (float r,float g,float b,float a) {
    color = Color::rgba8888(r, g, b, a);
}

void Pixmap::setColor (const Color& color) {
    this->color = Color::rgba8888(color.r, color.g, color.b, color.a);
}

void Pixmap::fill () {
    pixmap->clear(color);
}

void Pixmap::drawLine (int x,int y,int x2,int y2) {
    pixmap->drawLine(x, y, x2, y2, color);
}

void Pixmap::drawRectangle (int x,int y,int width,int height) {
    pixmap->drawRect(x, y, width, height, color);
}

void Pixmap::drawPixmap (const Pixmap& pixmap,int x,int y,int srcx,int srcy,int srcWidth,int srcHeight) {
    this->pixmap->drawPixmap(*pixmap.pixmap.get(), srcx, srcy, x, y, srcWidth, srcHeight);
}

void Pixmap::drawPixmap (const Pixmap& pixmap,int srcx,int srcy,int srcWidth,int srcHeight,int dstx,int dsty,int dstWidth,int dstHeight) {
    this->pixmap->drawPixmap(*pixmap.pixmap.get(), srcx, srcy, srcWidth, srcHeight, dstx, dsty, dstWidth, dstHeight);
}

void Pixmap::fillRectangle (int x,int y,int width,int height) {
    pixmap->fillRect(x, y, width, height, color);
}

void Pixmap::drawCircle (int x,int y,int radius) {
    pixmap->drawCircle(x, y, radius, color);
}

void Pixmap::fillCircle (int x,int y,int radius) {
    pixmap->fillCircle(x, y, radius, color);
}

int Pixmap::getPixel (int x, int y) const {
    return pixmap->getPixel(x, y);
}

int Pixmap::getWidth () const {
    return pixmap->getWidth();
}

int Pixmap::getHeight () {
    return pixmap->getHeight();
}

void Pixmap::dispose () {
    pixmap->dispose();
}

void Pixmap::drawPixel (int x,int y) {
    pixmap->setPixel(x, y, color);
}

int Pixmap::getGLFormat () const {
    return pixmap->getGLFormat();
}

int Pixmap::getGLInternalFormat () const {
    return pixmap->getGLInternalFormat();
}

int Pixmap::getGLType () const {
    return pixmap->getGLType();
}

const unsigned char* Pixmap::getPixels () const {
    return pixmap->getPixels();
}

const gdx_cpp::graphics::Pixmap::Format& Pixmap::getFormat () {
    return Format::fromGdx2DPixmapFormat(pixmap->getFormat());
}

Pixmap::Blending Pixmap::getBlending () {
    return blending;
}

int Pixmap::Format::toGdx2DPixmapFormat(const gdx_cpp::graphics::Pixmap::Format& format) {
    if (format == Pixmap::Format::Alpha) return GDX2D_FORMAT_ALPHA;
    if (format == Pixmap::Format::LuminanceAlpha) return GDX2D_FORMAT_LUMINANCE_ALPHA;
    if (format == Pixmap::Format::RGB565) return GDX2D_FORMAT_RGB565;
    if (format == Pixmap::Format::RGBA4444) return GDX2D_FORMAT_RGBA4444;
    if (format == Pixmap::Format::RGB888) return GDX2D_FORMAT_RGB888;
    if (format == Pixmap::Format::RGBA8888) return GDX2D_FORMAT_RGBA8888;

    gdx_cpp::Gdx::app.error("Pixmap.cpp") << "Unknown Format: " << format;
}
Pixmap::Format& Pixmap::Format::fromGdx2DPixmapFormat(int format) {
    if (format == GDX2D_FORMAT_ALPHA) return Pixmap::Format::Alpha;
    if (format == GDX2D_FORMAT_LUMINANCE_ALPHA) return Pixmap::Format::LuminanceAlpha;
    if (format == GDX2D_FORMAT_RGB565) return Pixmap::Format::RGB565;
    if (format == GDX2D_FORMAT_RGBA4444) return Pixmap::Format::RGBA4444;
    if (format == GDX2D_FORMAT_RGB888) return Pixmap::Format::RGB888;
    if (format == GDX2D_FORMAT_RGBA8888) return Pixmap::Format::RGBA8888;

    gdx_cpp::Gdx::app.error("Pixmap.cpp") << "Unknown Gdx2DPixmap Format: " << format;
}

Pixmap::Pixmap(int width, int height, gdx_cpp::graphics::Pixmap::Format::_Format format)
        : color(0)
{
    pixmap = g2d::Gdx2DPixmap::newPixmap(width, height, Format::toGdx2DPixmapFormat(format));
    assert(pixmap.get());
    setColor(0, 0, 0, 0);
    fill();
}

Pixmap::Pixmap(unsigned char* encodedData, int offset, int len) {
    pixmap = g2d::Gdx2DPixmap::ptr(new g2d::Gdx2DPixmap(encodedData, offset, len, 0));
}

Pixmap::Pixmap(gdx_cpp::files::FileHandle& file) {
    std::vector<char> bytes;
    file.readBytes(bytes);
        
    pixmap = g2d::Gdx2DPixmap::ptr(new g2d::Gdx2DPixmap((unsigned char*) &bytes[0], 0, bytes.size(), 0));
    assert(pixmap.get());
}

Pixmap::Pixmap(g2d::Gdx2DPixmap::ptr pixmap)
 : color(0)
 {
    this->pixmap = pixmap;
}
