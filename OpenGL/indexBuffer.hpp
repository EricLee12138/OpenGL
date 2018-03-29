//
//  indexBuffer.hpp
//  OpenGL
//
//  Created by 李荣嘉 on 2018/3/25.
//  Copyright © 2018年 EricLee Corp. All rights reserved.
//

#ifndef indexBuffer_hpp
#define indexBuffer_hpp

#include <glad/glad.h>
//#include <GL/glew.h>

class indexBuffer {
private:
    unsigned int rendererId;
    unsigned int count;
public:
    indexBuffer(unsigned int* data, unsigned int count);
    ~indexBuffer();
    void bind() const;
    void unbind();

    inline unsigned int getCount() const { return count; }
};

#endif /* indexBuffer_hpp */
