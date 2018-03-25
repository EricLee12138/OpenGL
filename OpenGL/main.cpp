//
//  main.cpp
//  OpenGL
//
//  Created by 李荣嘉 on 2018/3/18.
//  Copyright © 2018年 EricLee Corp. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLUT/glut.h>

#include "renderer.hpp"
#include "vertexBuffer.hpp"
#include "indexBuffer.hpp"
#include "vertexArray.hpp"
#include "vertexBufferLayout.hpp"

using namespace std;

struct shaderSource {
    string vertexSrc;
    string fragmentSrc;
};

static shaderSource parseShader(const string& filePath) {
    ifstream stream;
    stream.open(filePath);
    enum class shaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    string line;
    stringstream ss[2];
    shaderType type = shaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != string::npos) {
            if (line.find("vertex") != string::npos) {
                type = shaderType::VERTEX;
            } else if (line.find("fragment") != string::npos) {
                type = shaderType::FRAGMENT;
            }
        } else {
            ss[int(type)] << line << endl;
        }
    }

    return { ss[0].str(), ss[1].str() };
}

static unsigned int compileShader(const unsigned int type, const string& source) {
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
        cout << "Fail to compile " <<(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader." << endl << message << endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int createShader(const string& vertexShader, const string& fragmentShader) {
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

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);   // for Mac OS X
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glfwSwapInterval(1);

    if (!window) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        cout << "Error!" << endl;
        return -1;
    }

    shaderSource shaderSrc = parseShader("res/shaders/basic.shader");
    unsigned int shader = createShader(shaderSrc.vertexSrc, shaderSrc.fragmentSrc);
    glCall(glUseProgram(shader));

    unsigned int location = glGetUniformLocation(shader, "u_Color");
//    glUniform4f(location, 0.2f, 0.2f, 0.2f, 1.0f);

    float positions [] = {
        -0.5f,  -0.5f,
         0.5f,  -0.5f,
         0.5f,   0.5f,
        -0.5f,   0.5f
    };

    unsigned int indices [] = {
        0,  1,  2,
        2,  3,  0
    };

    // vertex array
    vertexArray vao;

    // vertex buffer object
    vertexBuffer vbo(positions, 6 * 2 * sizeof(float));

    // vertex buffer layout
    vertexBufferLayout vbl;

    // specify layout
    vbl.push(GL_FLOAT, 2);

    // link vertex buffer to vertex array according to vertex buffer layout
    vao.addBuffer(vbo, vbl);

    // index buffer
    indexBuffer ibo(indices, 6);

    glCall(glUseProgram(0));
    vao.unBind();
    vbo.unbind();
    ibo.unbind();

    float r = 0.0f;
    float increment = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glCall(glUseProgram(shader));
        vao.bind();
        vbo.bind();

        glUniform4f(location, r, 0.5f, 0.8f, 1.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        if (r < 0.0f || r > 1.0f) {
            increment *= -1;
        }
        r += increment;

//        // using legacy OpenGL to draw a triangle
//        glBegin(GL_TRIANGLES);
//        glVertex2f(0.0f, 0.5f);
//        glVertex2f(-0.5f, -0.5f);
//        glVertex2f(0.5f, -0.5f);
//        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
