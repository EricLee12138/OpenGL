//
//  vertexBuffer.hpp
//  OpenGL
//
//  Created by 李荣嘉 on 2018/3/25.
//  Copyright © 2018年 EricLee Corp. All rights reserved.
//

#ifndef vertexBuffer_hpp
#define vertexBuffer_hpp

#include <GL/glew.h>

#include "renderer.hpp"

class vertexBuffer {
private:
    unsigned int rendererId;
public:
    vertexBuffer(const void* data, unsigned int size);
    ~vertexBuffer();

    void bind();
    void unbind();
};

#endif /* vertexBuffer_hpp */
