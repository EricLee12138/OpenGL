//
//  vertexArray.hpp
//  OpenGL
//
//  Created by 李荣嘉 on 2018/3/25.
//  Copyright © 2018年 EricLee Corp. All rights reserved.
//

#ifndef vertexArray_hpp
#define vertexArray_hpp

#include "renderer.hpp"
#include "vertexBuffer.hpp"
#include "vertexBufferLayout.hpp"

class vertexArray {
private:
    unsigned int rendererId;
public:
    vertexArray();
    ~vertexArray();

    void bind() const;
    void unBind() const;
    void addBuffer(vertexBuffer& vb, const vertexBufferLayout& vl);
};

#endif /* vertexArray_hpp */
