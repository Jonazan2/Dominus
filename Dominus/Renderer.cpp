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
    delta = 0;
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
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    
    //create buffer object and set as current
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    
    //Load shaders
    
    const char* vertex_shader =
    "#version 400\n"
    "layout(location = 1) in vec3 vp;"
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
    
    const char* white_vertex_shader =
    "#version 400\n"
    "layout(location = 2) in vec3 vertexCoord;"
    "uniform mat4 mvp2;"
    "void main () {"
    "  gl_Position = mvp2 * vec4 (vertexCoord, 1.0);"
    "}";
    
    const char* white_fragment_shader =
    "#version 400\n"
    "out vec4 fragment_colour;"
    "void main () {"
    "  fragment_colour = vec4 (1.0, 1.0, 1.0, 1.0);"
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
   // GLuint positionAttribute = glGetAttribLocation(shader_programme, "vp");
    GLuint positionAttribute = 1;
    
    GLuint vs1 = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource (vs1, 1, &white_vertex_shader, NULL);
    glCompileShader (vs1);
    GLuint fs1 = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource (fs1, 1, &white_fragment_shader, NULL);
    glCompileShader (fs1);
    
    shaderProgram = glCreateProgram ();
    glAttachShader (shaderProgram, fs1);
    glAttachShader (shaderProgram, vs1);
    glLinkProgram (shaderProgram);
    
    //retrieve shader uniforms and attributes ids
    mvp2 = glGetUniformLocation(shaderProgram, "mvp2");
//    GLuint positionAttribute2 =
//        glGetAttribLocation(shaderProgram, "vertexCoord");
    GLuint positionAttribute2 = 2;
    //mvp2 = 3;

    //buffer data
//    mesh = new Mesh;
//    mesh->loadObj("cube.obj");
    mesh = getTriangleMesh();
    mesh2 = getTriangleMesh2();
    mesh->setPosition(glm::vec3(1.0,1.0,0.0));
    
    glBufferData(
                 GL_ARRAY_BUFFER,
                 (sizeof (GLfloat) * 3) * mesh->getVertices().size() +
                 (sizeof (GLfloat) * 3) * mesh2->getVertices().size(),
                 NULL, GL_STATIC_DRAW);
    
    glBufferSubData(GL_ARRAY_BUFFER,
                    0 ,
                    (sizeof (GLfloat) * 3) * mesh->getVertices().size() ,
                    &mesh->getVertices()[0]);
    glBufferSubData(GL_ARRAY_BUFFER,
                    (sizeof (GLfloat) * 3) * mesh->getVertices().size() ,
                    (sizeof (GLfloat) * 3) * mesh2->getVertices().size() ,
                    &mesh2->getVertices()[0]);

    //set vertex array layout for shader attibute and enable attibute
    glVertexAttribPointer (positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(positionAttribute);
    
    //set vertex array layout for shader attibute and enable attibute
    glVertexAttribPointer (positionAttribute2, 3, GL_FLOAT, GL_FALSE, 0,
                           (void*)((sizeof (GLfloat) * 3) * mesh->getVertices().size()) );
    glEnableVertexAttribArray(positionAttribute2);
}

Mesh* Renderer::getTriangleMesh() {
    Mesh* mesh = new Mesh;
    std::vector<glm::vec3> vertices = mesh->getVertices();
    vertices.push_back(glm::vec3( -1.0, -1.0, 0.0 ));
    vertices.push_back(glm::vec3( 1.0, -1.0, 0.0 ));
    vertices.push_back(glm::vec3( 0.0, 1.0, 0.0 ));
    mesh->setVertices(vertices);
    return mesh;
}

Mesh* Renderer::getTriangleMesh2() {
    Mesh* mesh = new Mesh;
    std::vector<glm::vec3> vertices = mesh->getVertices();
    vertices.push_back(glm::vec3( -1.0, -0.5, 0.0 ));
    vertices.push_back(glm::vec3( 1.0, -1.0, 0.0 ));
    vertices.push_back(glm::vec3( 0.0, 1.0, 0.0 ));
    mesh->setVertices(vertices);
    return mesh;
}

void Renderer::render(){
    delta+= 0.5;
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0,0,-10),
                                       glm::vec3(0,0,0),
                                       glm::vec3(0.0f, 1.0f, 0.0f)
                                       );
    glm::mat4 projectionMatrix = glm::perspective(0.78f, (float)640/480, 0.01f, 100.0f);
    glm::mat4 scaleMatrix = glm::scale(glm::vec3(1,1, 1));
    glm::mat4 rotationMatrix = glm::rotate( delta * 0.05f, glm::vec3(0.0f,1.0f,0.0f));
    glm::mat4 translate = glm::translate( mesh->getPosition() );
    glm::mat4 modelMatrix = translate * rotationMatrix * scaleMatrix;
    glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram (shader_programme);
    glUniformMatrix4fv(mvp, 1, GL_FALSE, &mvpMatrix[0][0]);
    glBindVertexArray (vao);

    glDrawArrays (GL_TRIANGLES, 0, (int)mesh->getVertices().size());

    glUseProgram(shaderProgram);
    mvpMatrix = projectionMatrix * viewMatrix;
    glUniformMatrix4fv(mvp2, 1, GL_FALSE, &mvpMatrix[0][0]);
    glDrawArrays (GL_TRIANGLES,
                  0,
                  (int)mesh2->getVertices().size());
    // update other events like input handling
    glfwPollEvents ();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers (window);
}