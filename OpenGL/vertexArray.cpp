//
//  vertexArray.cpp
//  OpenGL
//
//  Created by 李荣嘉 on 2018/3/25.
//  Copyright © 2018年 EricLee Corp. All rights reserved.
//

#include "vertexArray.hpp"

vertexArray::vertexArray() { 
    glCall(glGenVertexArrays(1, &rendererId));
}

vertexArray::~vertexArray() { 
    glCall(glDeleteVertexArrays(1, &rendererId));
}

void vertexArray::addBuffer(vertexBuffer& vb, const vertexBufferLayout& vl) {
    bind();
    vb.bind();
    const auto& elements = vl.getElements();
    unsigned int offset = 0;
    for (int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        glCall(glEnableVertexAttribArray(i));
        glCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, vl.getStride(), (const void*)offset));
        // glVertexAttribPointer - the index 0 of this vertex array is going to be bound to
        // the currently bound gl array buffer, this code links vao and buffer together
        offset += element.count * vertexBufferElement::getSizeOfType(element.type);
    }
}

void vertexArray::bind() const { 
    glCall(glBindVertexArray(rendererId));
}

void vertexArray::unBind() const { 
    glCall(glBindVertexArray(0));
}

