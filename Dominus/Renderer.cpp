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
    glViewport(0, 0, 640, 480);
    //create vao and set as current
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
    "  frag_colour = vec4 (1.0, 1.0, 1.0, 1.0);"
    "}";
    
    const char* ui_vertex_shader =
    "#version 400\n"
    "in vec3 vp;"
    "uniform mat4 mvp;"
    "void main () {"
    "  gl_Position = mvp * vec4 (vp, 1.0);"
    "}";
    
    const char* ui_fragment_shader =
    "#version 400\n"
    "out vec4 frag_colour;"
    "void main () {"
    "  frag_colour = vec4 (0.5, 0.5, 0.5, 1.0);"
    "}";
    
    //Setting 3d shaders
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
    
    //setting ui shaders
    GLuint ui_vs = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource (ui_vs, 1, &ui_vertex_shader, NULL);
    glCompileShader (ui_vs);
    GLuint ui_fs = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource (ui_fs, 1, &ui_fragment_shader, NULL);
    glCompileShader (ui_fs);
    
    uiShaderProgram = glCreateProgram ();
    glAttachShader (uiShaderProgram, ui_fs);
    glAttachShader (uiShaderProgram, ui_vs);
    glLinkProgram (uiShaderProgram);
    
    //retrieve shader uniforms and attributes ids
    mvp = glGetUniformLocation(uiShaderProgram, "mvp");
    GLuint uiPositionAttribute = glGetAttribLocation(uiShaderProgram, "vp");
    
    //buffer data
    mesh = new Mesh;
    mesh->loadObj("cube.obj");
    
    glBufferData (GL_ARRAY_BUFFER, (sizeof (GLfloat) * 3) * mesh->getVertices().size(), &mesh->getVertices()[0], GL_STATIC_DRAW);
    //glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW);
    //set vertex array layout for shader attibute and enable attibute
    glVertexAttribPointer (positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(positionAttribute);
    
    //create vao and set as current
    glGenVertexArrays (1, &uiVao);
    glBindVertexArray (uiVao);
    
    //create buffer object and set as current
    GLuint uiBuffer;
    glGenBuffers(1, &uiBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uiBuffer);
    
    glm::vec3 topLeft = glm::vec3( 0, 0, 0 );
    glm::vec3 topRight = glm::vec3( 100, 0, 0 );
    glm::vec3 bottomLeft = glm::vec3( 0, 100, 0 );
    glm::vec3 bottomRight = glm::vec3( 100, 100, 0 );
    
    vertices.push_back( topLeft );
    vertices.push_back( topRight );
    vertices.push_back( bottomLeft );
    vertices.push_back( bottomLeft );
    vertices.push_back( topRight );
    vertices.push_back( bottomRight );
    
    glBufferData (GL_ARRAY_BUFFER, (sizeof (GLfloat) * 3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    //set vertex array layout for shader attibute and enable attibute
    glVertexAttribPointer (uiPositionAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(uiPositionAttribute);
}

void Renderer::render(){
    delta+= 0.5;
    glBindVertexArray (vao);
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0,0,-10),
                                       glm::vec3(0,0,0),
                                       glm::vec3(0.0f, 1.0f, 0.0f)
                                       );
    glm::mat4 projectionMatrix = glm::perspective(0.78f, (float)640/480, 0.01f, 100.0f);
    glm::mat4 mvpMatrix = projectionMatrix * viewMatrix;
    //glm::mat4 mvpMatrix = glm::mat4(1);
    // wipe the drawing surface clear
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram (shader_programme);
    glUniformMatrix4fv(mvp, 1, GL_FALSE, &mvpMatrix[0][0]);
    glBindVertexArray (vao);
    // draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays (GL_TRIANGLES, 0, mesh->getVertices().size());
    glUseProgram(uiShaderProgram);
    glBindVertexArray (uiVao);
    glm::mat4 orthoMatrix = glm::ortho(0.0, 640.0, 480.0, 0.0 );
    glUniformMatrix4fv(mvp, 1, GL_FALSE, &orthoMatrix[0][0]);
    // draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays (GL_TRIANGLES, 0, vertices.size());
    
    // update other events like input handling
    glfwPollEvents ();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers (window);
}