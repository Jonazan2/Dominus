//
//  Renderer.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 03/02/16.
//  Copyright (c) 2016 frikazos. All rights reserved.
//

#include "Renderer.h"
#include "Log.hpp"

Renderer* classPointer = nullptr;

Renderer::Renderer() : xPos(0), yPos(0){
    classPointer = this;
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
        Log::getInstance().e(&errorLog[0]);
    }
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(classPointer){
        classPointer->onMouseMoved(xpos, ypos);
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    double xrelease, yrelease;
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        Log::getInstance() << "right button clicked";
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << xpos << std::endl;
        std::cout << ypos << std::endl;
    }else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        Log::getInstance() << "left button clicked";
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << xpos << std::endl;
        std::cout << ypos << std::endl;
        if(classPointer){
            classPointer->onMouseClicked(xpos, ypos);
        }
    }else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        Log::getInstance() << "left button released";
        glfwGetCursorPos(window, &xrelease, &yrelease);
        std::cout << xrelease - xpos << std::endl;
        std::cout << yrelease - ypos << std::endl;
        if(classPointer){
            classPointer->onMouseReleased(xrelease - xpos, yrelease - ypos);
        }
    }
}

void window_close_callback(GLFWwindow* window)
{
    Log::getInstance() << "window closed";
}

void Renderer::onMouseMoved(double x, double y){
    if(xPos != 0 && yPos != 0){
        double xRel = x - xPos;
        double yRel = y - yPos;
        onMouseDragged(xRel, yRel);
    }
}

void Renderer::onMouseClicked(double x, double y){
    xPos = x;
    yPos = y;
}

void Renderer::onMouseReleased(double x, double y){
    xPos = 0;
    yPos = 0;
}

void Renderer::onMouseDragged(double xRel, double yRel){
 
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
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window,mouse_button_callback);
    glfwSetWindowCloseCallback(window, window_close_callback);
    
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
    modelViewUID = glGetUniformLocation(shader_programme, "modelViewMatrix");
    projectionUID = glGetUniformLocation(shader_programme, "projectionMatrix");
    normalUID = glGetUniformLocation(shader_programme, "normalMatrix");
    lightPositionUID = glGetUniformLocation(shader_programme, "lightPosition");
    positionAttribute = glGetAttribLocation(shader_programme, "vp");
    normalAttribute = glGetAttribLocation(shader_programme, "normalAttribute");

}

void Renderer::render(){
    
}

void Renderer::updateProjection( glm::mat4 projectionMatrix ) {
    this->projectionMatrix = projectionMatrix;
}

void Renderer:: updateCamera( glm::mat4 viewMatrix ) {
    this->viewMatrix = viewMatrix;
}

void Renderer::updateLightSource( glm::vec3 lightSource ) {
    this->lightPosition = lightSource;
}

void Renderer::loadMesh( std::vector<Node*> renderBatch ) {
    //create buffer object and set as current
    GLuint buffers[2];
    glGenBuffers( 2, buffers );
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    
    //allocate buffer memory to load all the vertex
    GLsizeiptr vertexBufferSize = 0;
    GLsizeiptr normalBufferSize = 0;
    for ( int i = 0; i < renderBatch.size(); i++ ) {
        Node* node = renderBatch.at(i);
        Mesh* mesh = node->getMesh();
        vertexBufferSize += mesh->getSize();
        normalBufferSize += mesh->getNormalSize();
    }
    glBufferData (GL_ARRAY_BUFFER,
                  vertexBufferSize,
                  NULL,
                  GL_STATIC_DRAW);
    //buffer vertex data
    GLuint offset = 0;
    for ( int i = 0; i < renderBatch.size(); i++ ) {
        Node* node = renderBatch.at(i);
        glBufferSubData(GL_ARRAY_BUFFER, // target
                        offset, // offset
                        node->getMesh()->getSize(), // size
                        &node->getMesh()->getVertices()[0]); // data
        offset += node->getMesh()->getSize();
    }
    
    //set vertex array layout for shader attibute and enable attibute
    glVertexAttribPointer (positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(positionAttribute);
    
    //buffer vertex data
    glBindBuffer( GL_ARRAY_BUFFER, buffers[1] );
    glBufferData (GL_ARRAY_BUFFER,
                  normalBufferSize,
                  NULL,
                  GL_STATIC_DRAW);
    GLuint normalOffset = 0;
    for ( int i = 0; i < renderBatch.size(); i++ ) {
        Node* node = renderBatch.at(i);
        glBufferSubData(GL_ARRAY_BUFFER, // target
                        normalOffset, // offset
                        node->getMesh()->getNormalSize(), // size
                        &node->getMesh()->getNormals()[0]); // data
        normalOffset += node->getMesh()->getNormalSize();
    }
    
    //set normal array layout for shader attribute and enable attribute
    glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(normalAttribute);
}

void Renderer::draw( std::vector<Node*> renderBatch ) {
    // wipe the drawing surface clear
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram (shader_programme);
    glUniformMatrix4fv(projectionUID, 1, GL_FALSE, &projectionMatrix[0][0]);
    glUniform3fv(lightPositionUID, 1, &lightPosition[0]);
    glBindVertexArray (vao);
    GLuint offset = 0;
    for ( int i = 0; i < renderBatch.size() ; i++ ) {
        Node* node = renderBatch.at( i );
        glm::mat4 modelViewMatrix = viewMatrix * *node->getModelMatrix();
        glm::mat4 normalMat = glm::transpose( glm::inverse( modelViewMatrix ) );
        glm::mat3 normalMat3 = glm::mat3( normalMat );
        glUniformMatrix4fv(modelViewUID, 1, GL_FALSE, &modelViewMatrix[0][0]);
        glUniformMatrix3fv(normalUID, 1, GL_FALSE, &normalMat3[0][0]);
        // draw points from the currently bound VAO with current in-use shader
        glDrawArrays (GL_TRIANGLES,
                        offset,
                        (int)node->getMesh()->getVertices().size());
        offset += (int)node->getMesh()->getVertices().size();
    }
}

void Renderer::present() {
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers (window);
}