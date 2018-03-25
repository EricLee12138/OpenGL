//
//  vertexBufferLayout.hpp
//  OpenGL
//
//  Created by 李荣嘉 on 2018/3/25.
//  Copyright © 2018年 EricLee Corp. All rights reserved.
//

#ifndef vertexBufferLayout_hpp
#define vertexBufferLayout_hpp

#include <iostream>
#include <vector>

#include "GL/glew.h"
#include "renderer.hpp"

struct vertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned int normalized;

    static unsigned int getSizeOfType(unsigned int type) {
        switch(type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
        return 0;
    }

    static unsigned int getNormalized(unsigned int type) {
        switch(type) {
            case GL_FLOAT: return GL_FALSE;
            case GL_UNSIGNED_INT: return GL_FALSE;
            case GL_UNSIGNED_BYTE: return GL_TRUE;
        }
        ASSERT(false);
        return 0;
    }
};

class vertexBufferLayout {
private:
    std::vector<vertexBufferElement> elements;
    unsigned int stride;
public:
    vertexBufferLayout() : stride(0) {}
//    ~vertexBufferLayout();

    void push(unsigned int type, unsigned int count) {
        elements.push_back({ type, count, vertexBufferElement::getNormalized(type) });
        stride += count * vertexBufferElement::getSizeOfType(type);
    }

    inline const std::vector<vertexBufferElement> getElements() const { return elements; }
    inline const unsigned int getStride() const { return stride; }
};
#endif /* vertexBufferLayout_hpp */
