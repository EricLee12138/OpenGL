//
//  renderer.hpp
//  OpenGL
//
//  Created by 李荣嘉 on 2018/3/25.
//  Copyright © 2018年 EricLee Corp. All rights reserved.
//

#ifndef renderer_hpp
#define renderer_hpp

#include <iostream>

#include <glad/glad.h>
//#include <GL/glew.h>

#include "shader.hpp"
#include "vertexArray.hpp"
#include "indexBuffer.hpp"

#define ASSERT(x) if (!(x)) __asm__("int $3");
#define glCall(x) glClearError(); x; ASSERT(glLogCall(#x, __FILE__, __LINE__))

void glClearError();
bool glLogCall(const char* function, const char* file, const int line);

class renderer {
public:
    void clear() const;
    void draw(const vertexArray& va, const indexBuffer& ib, const shader& sh) const;
};

#endif /* renderer_hpp */
