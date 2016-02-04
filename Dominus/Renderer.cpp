//
//  Renderer.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 03/02/16.
//  Copyright (c) 2016 frikazos. All rights reserved.
//

#include "Renderer.h"

Renderer::Renderer(){
}

Renderer::~Renderer(){
}

void Renderer::init(){
    //Init window
    
    if (!glfwInit ()) {
        fprintf (stderr, "ERROR: could not start GLFW3\n");
        return ;
    }
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow (640, 480, "Hello Triangle", NULL, NULL);
    if (!window) {
        fprintf (stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return ;
    }
    glfwMakeContextCurrent (window);
    
    // get version info
    const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString (GL_VERSION); // version as a string
    printf ("Renderer: %s\n", renderer);
    printf ("OpenGL version supported %s\n", version);
    
    // opengl states
    glEnable (GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as
    
    //create vao and set as current
    GLuint vao;
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    
    //create buffer object and set as current
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    
    //Load shaders
    
    const char* vertex_shader =
    "#version 400\n"
    "in vec3 vp;"
    "uniform mat4 mvp;"
    "void main () {"
    "  gl_Position = mvp * vec4 (vp, 1.0);"
    "}";
    
    const char* fragment_shader =
    "#version 400\n"
    "out vec4 frag_colour;"
    "void main () {"
    "  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
    "}";
    
    GLuint vs = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource (vs, 1, &vertex_shader, NULL);
    glCompileShader (vs);
    GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource (fs, 1, &fragment_shader, NULL);
    glCompileShader (fs);
    
    shader_programme = glCreateProgram ();
    glAttachShader (shader_programme, fs);
    glAttachShader (shader_programme, vs);
    glLinkProgram (shader_programme);
    
    //retrieve shader uniforms and attributes ids
    mvp = glGetUniformLocation(shader_programme, "mvp");
    GLuint positionAttribute = glGetAttribLocation(shader_programme, "vp");
    
    //buffer data
    mesh = new Mesh;
    mesh->loadObj("cube.obj");
    glBufferData (GL_ARRAY_BUFFER, (sizeof (GLfloat) * 3) * mesh->getVertices().size(), &mesh->getVertices()[0], GL_STATIC_DRAW);
    
    //set vertex array layout for shader attibute and enable attibute
    glVertexAttribPointer (positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(positionAttribute);
}

void Renderer::render(){
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0,0,-10),
                                       glm::vec3(0,0,0),
                                       glm::vec3(0.0f, 1.0f, 0.0f)
                                       );
    glm::mat4 projectionMatrix = glm::perspective(0.78f, (float)640/480, 0.01f, 100.0f);
    glm::mat4 mvpMatrix = projectionMatrix * viewMatrix;
    // wipe the drawing surface clear
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram (shader_programme);
    glUniformMatrix4fv(mvp, 1, GL_FALSE, &mvpMatrix[0][0]);
    glBindVertexArray (vao);
    // draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays (GL_TRIANGLES, 0, 35);
    // update other events like input handling
    glfwPollEvents ();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers (window);
}