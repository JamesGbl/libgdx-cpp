
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

#include "VertexBufferObjectSubData.hpp"

using namespace gdx_cpp::graphics::glutils;

int VertexBufferObjectSubData::createBufferObject () {
    if (Gdx.gl20 != null) {
        Gdx.gl20.glGenBuffers(1, tmpHandle);
        Gdx.gl20.glBindBuffer(GL20.GL_ARRAY_BUFFER, tmpHandle.get(0));
        Gdx.gl20.glBufferData(GL20.GL_ARRAY_BUFFER, byteBuffer.capacity(), null, usage);
        Gdx.gl20.glBindBuffer(GL20.GL_ARRAY_BUFFER, 0);
    } else {
        Gdx.gl11.glGenBuffers(1, tmpHandle);
        Gdx.gl11.glBindBuffer(GL11.GL_ARRAY_BUFFER, tmpHandle.get(0));
        Gdx.gl11.glBufferData(GL11.GL_ARRAY_BUFFER, byteBuffer.capacity(), null, usage);
        Gdx.gl11.glBindBuffer(GL11.GL_ARRAY_BUFFER, 0);
    }
    return tmpHandle.get(0);
}

gdx_cpp::graphics::VertexAttributes& VertexBufferObjectSubData::getAttributes () {
    return attributes;
}

int VertexBufferObjectSubData::getNumVertices () {
    return buffer.limit() * 4 / attributes.vertexSize;
}

int VertexBufferObjectSubData::getNumMaxVertices () {
    return byteBuffer.capacity() / attributes.vertexSize;
}

FloatBuffer& VertexBufferObjectSubData::getBuffer () {
    isDirty = true;
    return buffer;
}

void VertexBufferObjectSubData::setVertices (int offset,int count) {
    isDirty = true;
    if (isDirect) {
        BufferUtils.copy(vertices, byteBuffer, count, offset);
        buffer.position(0);
        buffer.limit(count);
    } else {
        buffer.clear();
        buffer.put(vertices, offset, count);
        buffer.flip();
        byteBuffer.position(0);
        byteBuffer.limit(buffer.limit() << 2);
    }

    if (isBound) {
        if (Gdx.gl20 != null) {
            GL20 gl = Gdx.gl20;
            gl.glBufferSubData(GL20.GL_ARRAY_BUFFER, 0, byteBuffer.limit(), byteBuffer);
        } else {
            GL11 gl = Gdx.gl11;
            gl.glBufferSubData(GL11.GL_ARRAY_BUFFER, 0, byteBuffer.limit(), byteBuffer);
        }
        isDirty = false;
    }
}

void VertexBufferObjectSubData::bind () {
    GL11 gl = Gdx.gl11;

    gl.glBindBuffer(GL11.GL_ARRAY_BUFFER, bufferHandle);
    if (isDirty) {
        byteBuffer.limit(buffer.limit() * 4);
        gl.glBufferSubData(GL11.GL_ARRAY_BUFFER, 0, byteBuffer.limit(), byteBuffer);
// gl.glBufferData(GL11.GL_ARRAY_BUFFER, byteBuffer.limit(),
// byteBuffer, usage);
        isDirty = false;
    }

    int textureUnit = 0;
    int numAttributes = attributes.size();

    for (int i = 0; i < numAttributes; i++) {
        VertexAttribute attribute = attributes.get(i);

        switch (attribute.usage) {
        case Usage.Position:
            gl.glEnableClientState(GL11.GL_VERTEX_ARRAY);
            gl.glVertexPointer(attribute.numComponents, GL10.GL_FLOAT, attributes.vertexSize, attribute.offset);
            break;

        case Usage.Color:
        case Usage.ColorPacked:
            int colorType = GL10.GL_FLOAT;
            if (attribute.usage == Usage.ColorPacked) colorType = GL11.GL_UNSIGNED_BYTE;

            gl.glEnableClientState(GL10.GL_COLOR_ARRAY);
            gl.glColorPointer(attribute.numComponents, colorType, attributes.vertexSize, attribute.offset);
            break;

        case Usage.Normal:
            gl.glEnableClientState(GL10.GL_NORMAL_ARRAY);
            gl.glNormalPointer(GL10.GL_FLOAT, attributes.vertexSize, attribute.offset);
            break;

        case Usage.TextureCoordinates:
            gl.glClientActiveTexture(GL10.GL_TEXTURE0 + textureUnit);
            gl.glEnableClientState(GL10.GL_TEXTURE_COORD_ARRAY);
            gl.glTexCoordPointer(attribute.numComponents, GL10.GL_FLOAT, attributes.vertexSize, attribute.offset);
            textureUnit++;
            break;

        default:
            throw new GdxRuntimeException("unkown vertex attribute type: " + attribute.usage);
        }
    }

    isBound = true;
}

void VertexBufferObjectSubData::bind (const ShaderProgram& shader) {
    GL20 gl = Gdx.gl20;

    gl.glBindBuffer(GL20.GL_ARRAY_BUFFER, bufferHandle);
    if (isDirty) {
        byteBuffer.limit(buffer.limit() * 4);
        gl.glBufferSubData(GL11.GL_ARRAY_BUFFER, 0, byteBuffer.limit(), byteBuffer);
// gl.glBufferData(GL20.GL_ARRAY_BUFFER, byteBuffer.limit(),
// byteBuffer, usage);
        isDirty = false;
    }

    int numAttributes = attributes.size();
    for (int i = 0; i < numAttributes; i++) {
        VertexAttribute attribute = attributes.get(i);
        shader.enableVertexAttribute(attribute.alias);
        int colorType = GL20.GL_FLOAT;
        boolean normalize = false;
        if (attribute.usage == Usage.ColorPacked) {
            colorType = GL20.GL_UNSIGNED_BYTE;
            normalize = true;
        }
        shader.setVertexAttribute(attribute.alias, attribute.numComponents, colorType, normalize, attributes.vertexSize,
                                  attribute.offset);
    }
    isBound = true;
}

void VertexBufferObjectSubData::unbind () {
    GL11 gl = Gdx.gl11;
    int textureUnit = 0;
    int numAttributes = attributes.size();

    for (int i = 0; i < numAttributes; i++) {

        VertexAttribute attribute = attributes.get(i);
        switch (attribute.usage) {
        case Usage.Position:
            break; // no-op, we also need a position bound in gles
        case Usage.Color:
        case Usage.ColorPacked:
            gl.glDisableClientState(GL11.GL_COLOR_ARRAY);
            break;
        case Usage.Normal:
            gl.glDisableClientState(GL11.GL_NORMAL_ARRAY);
            break;
        case Usage.TextureCoordinates:
            gl.glClientActiveTexture(GL11.GL_TEXTURE0 + textureUnit);
            gl.glDisableClientState(GL11.GL_TEXTURE_COORD_ARRAY);
            textureUnit++;
            break;
        default:
            throw new GdxRuntimeException("unkown vertex attribute type: " + attribute.usage);
        }
    }

    gl.glBindBuffer(GL11.GL_ARRAY_BUFFER, 0);
    isBound = false;
}

void VertexBufferObjectSubData::unbind (const ShaderProgram& shader) {
    GL20 gl = Gdx.gl20;
    int numAttributes = attributes.size();
    for (int i = 0; i < numAttributes; i++) {
        VertexAttribute attribute = attributes.get(i);
        shader.disableVertexAttribute(attribute.alias);
    }
    gl.glBindBuffer(GL20.GL_ARRAY_BUFFER, 0);
    isBound = false;
}

void VertexBufferObjectSubData::invalidate () {
    bufferHandle = createBufferObject();
    isDirty = true;
}

void VertexBufferObjectSubData::dispose () {
    if (Gdx.gl20 != null) {
        tmpHandle.clear();
        tmpHandle.put(bufferHandle);
        tmpHandle.flip();
        GL20 gl = Gdx.gl20;
        gl.glBindBuffer(GL20.GL_ARRAY_BUFFER, 0);
        gl.glDeleteBuffers(1, tmpHandle);
        bufferHandle = 0;
    } else {
        tmpHandle.clear();
        tmpHandle.put(bufferHandle);
        tmpHandle.flip();
        GL11 gl = Gdx.gl11;
        gl.glBindBuffer(GL11.GL_ARRAY_BUFFER, 0);
        gl.glDeleteBuffers(1, tmpHandle);
        bufferHandle = 0;
    }
}

int VertexBufferObjectSubData::getBufferHandle () {
    return bufferHandle;
}
