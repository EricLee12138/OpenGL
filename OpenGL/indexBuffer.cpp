//
//  indexBuffer.cpp
//  OpenGL
//
//  Created by 李荣嘉 on 2018/3/25.
//  Copyright © 2018年 EricLee Corp. All rights reserved.
//

#include "indexBuffer.hpp"

indexBuffer::indexBuffer(unsigned int *data, unsigned int count) {
    glCall(glGenBuffers(1, &rendererId));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId));
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

indexBuffer::~indexBuffer() { 
    glCall(glDeleteBuffers(1, &rendererId));
}

void indexBuffer::bind() { 
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId));
}

void indexBuffer::unbind() { 
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
