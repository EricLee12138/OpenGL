//
//  vertexBuffer.cpp
//  OpenGL
//
//  Created by 李荣嘉 on 2018/3/25.
//  Copyright © 2018年 EricLee Corp. All rights reserved.
//

#include "vertexBuffer.hpp"

#include "renderer.hpp"

vertexBuffer::vertexBuffer(const void* data, unsigned int size) {
    glCall(glGenBuffers(1, &rendererId));   // create a buffer and get its id
    glCall(glBindBuffer(GL_ARRAY_BUFFER, rendererId));
    glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

vertexBuffer::~vertexBuffer() { 
    glCall(glDeleteBuffers(1, &rendererId));
}

void vertexBuffer::bind() const {
    glCall(glBindBuffer(GL_ARRAY_BUFFER, rendererId));;
}

void vertexBuffer::unbind() {
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));;
}

