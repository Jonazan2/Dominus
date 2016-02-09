//
//  Renderer.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 03/02/16.
//  Copyright (c) 2016 frikazos. All rights reserved.
//

#ifndef __Dominus__Renderer__
#define __Dominus__Renderer__

#include <stdio.h>
#include "Mesh.hpp"
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Node.hpp"

class Renderer{
public:
    Renderer();
    ~Renderer();
    void init();
    void render();
    void compileShader(GLuint shader);
    void onMouseDragged(double xRel, double yRel);
    void onMouseClicked(double x, double y);
    void onMouseReleased(double x, double y);
    void onMouseMoved(double x, double y);
private:
    double xPos;
    double yPos;
    GLFWwindow* window;
    GLuint vao;
    GLuint shader_programme;
    GLuint modelViewMatrix;
    GLuint projectionMatrix;
    GLuint lightPosition;
    GLuint normalMatrix;
    float delta;
    std::vector<Node*> nodes;
};

#endif /* defined(__Dominus__Renderer__) */
