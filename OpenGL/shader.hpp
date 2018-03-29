//
//  shader.hpp
//  OpenGL
//
//  Created by 李荣嘉 on 2018/3/25.
//  Copyright © 2018年 EricLee Corp. All rights reserved.
//

#ifndef shader_hpp
#define shader_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

#include <glad/glad.h>
//#include <GL/glew.h>

struct shaderSource {
    std::string vertexSrc;
    std::string fragmentSrc;
};

class shader {
private:
    unsigned int rendererId;
    std::string filePath;
    std::unordered_map<std::string, int> uniformCache;

    shaderSource parseShader(const std::string& filePath);
    unsigned int compileShader(const unsigned int type, const std::string& source);
    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
public:
    shader(const std::string& filePath);
    ~shader();

    void bind() const;
    void unbind() const;
    void setUniform1f(const std::string& uniform, float value);
    void setUniform1i(const std::string& uniform, int value);
    void setUniform4f(const std::string& uniform, float v0, float v1, float v2, float v3);
    int getUniformLocation(const std::string& uniform);
};

#endif /* shader_hpp */
