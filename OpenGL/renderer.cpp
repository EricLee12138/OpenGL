//
//  renderer.cpp
//  OpenGL
//
//  Created by 李荣嘉 on 2018/3/25.
//  Copyright © 2018年 EricLee Corp. All rights reserved.
//

#include "renderer.hpp"

void glClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* function, const char* file, const int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ": " << line << std::endl;
        return false;
    }
    return true;
}
