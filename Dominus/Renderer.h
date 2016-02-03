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

class Renderer{
public:
    Renderer();
    ~Renderer();
    void init();
    void loadMesh(Mesh* mesh);
    void render();
private:
    GLFWwindow* window;
    GLuint vao;
    GLuint shader_programme;
    GLuint mvp;
    Mesh* mesh;
};

#endif /* defined(__Dominus__Renderer__) */
