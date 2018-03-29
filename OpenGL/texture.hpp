//
//  texture.hpp
//  OpenGL
//
//  Created by 李荣嘉 on 2018/3/29.
//  Copyright © 2018年 EricLee Corp. All rights reserved.
//

#ifndef texture_hpp
#define texture_hpp

#include <iostream>
#include <string>

#include "renderer.hpp"

class texture {
private:
    unsigned int rendererId;
    std::string filePath;
    unsigned char* localBuffer;
    int width, height, bpp;

public:
    texture(const std::string& filePath);
    ~texture();

    void bind(unsigned int slot = 0) const;
    void unbind();

    inline int getWidth() { return width; }
    inline int getHeight() { return height; }
};

#endif /* texture_hpp */
