//
//  shader.cpp
//  OpenGL
//
//  Created by 李荣嘉 on 2018/3/25.
//  Copyright © 2018年 EricLee Corp. All rights reserved.
//

#include "shader.hpp"

#include "renderer.hpp"

shader::shader(const std::string &filePath) : filePath(filePath), rendererId(0) {
    shaderSource shaderSrc = parseShader(filePath);
    rendererId = createShader(shaderSrc.vertexSrc, shaderSrc.fragmentSrc);
    bind();
}

shader::~shader() { 
    glCall(glDeleteProgram(rendererId));
}

shaderSource shader::parseShader(const std::string &filePath) {
    std::ifstream stream;
    stream.open(filePath);
    enum class shaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    shaderType type = shaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = shaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = shaderType::FRAGMENT;
            }
        } else {
            ss[int(type)] << line << std::endl;
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int shader::compileShader(const unsigned int type, const std::string &source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // TODO: errors handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char [length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Fail to compile " <<(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader." << std::endl << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int shader::createShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void shader::bind() const { 
    glCall(glUseProgram(rendererId));
}

void shader::unbind() const { 
    glCall(glUseProgram(0));
}

void shader::setUniform1f(const std::string &uniform, float value) {
    glCall(glUniform1f(getUniformLocation(uniform), value));
}

void shader::setUniform1i(const std::string &uniform, int value) {
    glCall(glUniform1i(getUniformLocation(uniform), value));
}

void shader::setUniform4f(const std::string &uniform, float v0, float v1, float v2, float v3) {
    glCall(glUniform4f(getUniformLocation(uniform), v0, v1, v2, v3));
}

int shader::getUniformLocation(const std::string &uniform) {
    if (uniformCache.find(uniform) != uniformCache.end()) {
        return uniformCache[uniform];
    }

    int location = glGetUniformLocation(rendererId, uniform.c_str());

    if (location == -1) {
        std::cout << "Warning: uniform '" << uniform << "' doesn't exist!" << std::endl;
    }
    uniformCache[uniform] = location;
    return location;
}
