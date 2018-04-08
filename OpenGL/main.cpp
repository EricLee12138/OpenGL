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

//#include <GL/glew.h>
#include <glad/glad.h>
//#include <KHR/khrplatform.h>
#include <GLUT/glut.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "renderer.hpp"
#include "texture.hpp"
#include "vertexBuffer.hpp"
#include "indexBuffer.hpp"
#include "vertexArray.hpp"
#include "vertexBufferLayout.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

glm::mat4 func(float Translate, glm::vec3 const & Rotate)
{
    glm::mat4 Projection = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -100.0f, 100.0f);
    glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
    glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    glm::mat4 ViewRotateY = glm::rotate(ViewRotateX, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 View = glm::rotate(ViewRotateY, Rotate.z, glm::vec3(0.0f, 0.0f, -1.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
    glm::mat4 MVP = Projection * View * Model;

    return MVP;
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
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
//    glewExperimental = GL_TRUE;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
//    if (glewInit() != GLEW_OK) {
//        cout << "Error!" << endl;
//        return -1;
//    }
    
    float positions [] = {
        100.0f,   100.0f,   0.0f,   0.0f,
        200.0f,   100.0f,   1.0f,   0.0f,
        200.0f,   200.0f,   1.0f,   1.0f,
        100.0f,   200.0f,   0.0f,   1.0f
    };

    unsigned int indices [] = {
        0,  1,  2,
        2,  3,  0
    };

    glCall(glEnable(GL_BLEND));
    glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // shader
    shader shader("res/shaders/basic.shader");

    // renderer
    renderer renderer;

    // texture
    texture texture("res/images/maya.png");
    texture.bind();
    shader.setUniform1i("u_Texture", 0);

    // proj matrix
    glm::mat4 proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 0.0f));
    view = glm::rotate(view, 0.1f, glm::vec3(0.0f, 0.0f, -1.0f));
    glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 mvp = proj * view * model;
//    float angle = 30.0f / glm::pi<float>();
//    glm::mat4 mvp = func(0.0f, glm::vec3(0.0f, 0.0f, 0.05f));

//    glm::vec4 map(100.0f, 100.0f, 0.0f, 1.0f);
//    glm::vec4 result = proj * map;

    shader.setUniformMat4f("u_Mvp", mvp);

    // vertex array
    vertexArray vao;

    // vertex buffer object
    vertexBuffer vbo(positions, 4 * 4 * sizeof(float));

    // vertex buffer layout
    vertexBufferLayout vbl;

    // specify layout
    vbl.push(GL_FLOAT, 2);
    vbl.push(GL_FLOAT, 2);

    // link vertex buffer to vertex array according to vertex buffer layout
    vao.addBuffer(vbo, vbl);

    // index buffer
    indexBuffer ibo(indices, 6);

//    shader.unbind();
//    vao.unbind();
//    vbo.unbind();
//    ibo.unbind();

    float r = 0.0f;
    float increment = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();
//        shader.setUniform4f("u_Color", r, 0.5f, 0.8f, 1.0f);

        renderer.draw(vao, ibo, shader);

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

    glfwTerminate();
    return 0;
}
