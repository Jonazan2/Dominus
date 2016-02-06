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

void Renderer::compileShader(GLuint shader){
    glCompileShader(shader);
    
    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        
        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
        std::cout << &errorLog[0] << std::endl;
    }
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
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    
    //create buffer object and set as current
    GLuint buffers[2];
    glGenBuffers(2, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    
    //Load shaders
 
    const char* vertex_shader =
    "#version 400\n"
    "in vec3 vp;"
    "in vec3 normalAttribute;"
    "out vec3 lightColor;"
    "uniform mat3 normalMatrix;"
    "uniform mat4 modelViewMatrix;"
    "uniform mat4 projectionMatrix;"
    "uniform vec3 lightPosition;"
    "void main () {"
    "  vec3 position = vec3(modelViewMatrix * vec4(vp, 1.0));"
    "  vec3 normal = normalize(normalMatrix * normalAttribute);"
    "  vec3 lightDirection = normalize(lightPosition - position);"
    "  float ndotl = max(dot(normal, lightDirection), 0.0);"
    "  lightColor = ndotl * vec3( 1.0 );"
    "  gl_Position = projectionMatrix * vec4 (position, 1.0);"
    "}";
    
    const char* fragment_shader =
    "#version 400\n"
    "in vec3 lightColor;"
    "out vec4 frag_colour;"
    "void main () {"
    "  frag_colour = vec4(lightColor, 1.0);"
    "}";
    
    GLuint vs = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource (vs, 1, &vertex_shader, NULL);
    compileShader(vs);
    GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource (fs, 1, &fragment_shader, NULL);
    compileShader(fs);
    
    shader_programme = glCreateProgram ();
    glAttachShader (shader_programme, fs);
    glAttachShader (shader_programme, vs);
    glLinkProgram (shader_programme);
    
    //retrieve shader uniforms and attributes ids
    modelViewMatrix = glGetUniformLocation(shader_programme, "modelViewMatrix");
    projectionMatrix = glGetUniformLocation(shader_programme, "projectionMatrix");
    normalMatrix = glGetUniformLocation(shader_programme, "normalMatrix");
    lightPosition = glGetUniformLocation(shader_programme, "lightPosition");
    GLuint positionAttribute = glGetAttribLocation(shader_programme, "vp");
    GLuint normalAttribute = glGetAttribLocation(shader_programme, "normalAttribute");
    
    //buffer data
    mesh = new Mesh;
    mesh->loadObj("cube.obj");

    //buffer vertex
    glBufferData (GL_ARRAY_BUFFER, (sizeof (GLfloat) * 3) * mesh->getVertices().size(), &mesh->getVertices()[0], GL_STATIC_DRAW);
    
    //set vertex array layout for shader attibute and enable attibute
    glVertexAttribPointer (positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(positionAttribute);
    
    //set normal frame buffer as current
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    //buffer normals into current buffer
    glBufferData(GL_ARRAY_BUFFER, (sizeof (GLfloat) * 3) * mesh->getNormals().size(), &mesh->getNormals()[0],
                 GL_STATIC_DRAW);
    //set normal array layout for shader attribute and enable attribute
    glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(normalAttribute);
}

void Renderer::render(){
    delta+= 0.1;
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0,0,-10),
                                       glm::vec3(0,0,0),
                                       glm::vec3(0.0f, 1.0f, 0.0f)
                                       );
    glm::mat4 projectionMat = glm::perspective(0.78f, (float)640/480, 0.01f, 100.0f);
    glm::mat4 scaleMatrix = glm::scale(glm::vec3(1,1, 1));
    glm::mat4 rotationMatrix = glm::rotate( delta * 0.5f, glm::vec3(1.0f,1.0f,0.0f));
    glm::mat4 modelMatrix = rotationMatrix * scaleMatrix;
    glm::mat4 modelViewMat = viewMatrix * modelMatrix;
    glm::mat4 normalMat = glm::inverse(modelViewMat);
    normalMat = glm::transpose(normalMat);
    glm::mat3 normalMat3 = glm::mat3(normalMat);
    glm::vec3 lightPos = glm::vec3(0.0, 0.0, 0.0);
    //glm::mat4 mvpMatrix = glm::mat4(1);
    // wipe the drawing surface clear
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram (shader_programme);
    glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, &projectionMat[0][0]);
    glUniformMatrix4fv(modelViewMatrix, 1, GL_FALSE, &modelViewMat[0][0]);
    glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, &normalMat3[0][0]);
    glUniform3fv(lightPosition, 1, &lightPos[0]);
    glBindVertexArray (vao);
    // draw points from the currently bound VAO with current in-use shader
    glDrawArrays (GL_TRIANGLES, 0, (int)mesh->getVertices().size());
    // update other events like input handling
    glfwPollEvents ();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers (window);
}