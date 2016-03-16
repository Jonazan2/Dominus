//
//  Renderer.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 03/02/16.
//  Copyright (c) 2016 frikazos. All rights reserved.
//

#include "Renderer.h"
#include "Texture.hpp"

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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    "in vec3 vertexCoord;"
    "in vec2 textureCoord;"
    "out vec2 fragmentTextureCoord;"
    "uniform mat4 mvp;"
    "void main () {"
    "  fragmentTextureCoord = textureCoord;"
    "  gl_Position = mvp * vec4 (vertexCoord, 1.0);"
    "}";
    
    const char* ui_fragment_shader =
    "#version 400\n"
    "in vec2 fragmentTextureCoord;"
    "out vec4 fragmentColor;"
    "uniform sampler2D textureData;"
    "void main () {"
    "  fragmentColor = texture( textureData, fragmentTextureCoord );"
    "}";
    
    //Setting 3d shaders
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
    mvp = glGetUniformLocation(shader_programme, "mvp");
    GLuint positionAttribute = glGetAttribLocation(shader_programme, "vp");
    
    //setting ui shaders
    GLuint ui_vs = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource (ui_vs, 1, &ui_vertex_shader, NULL);
    compileShader(ui_vs);
    GLuint ui_fs = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource (ui_fs, 1, &ui_fragment_shader, NULL);
    compileShader (ui_fs);
    
    uiShaderProgram = glCreateProgram ();
    glUseProgram(uiShaderProgram);
    glAttachShader (uiShaderProgram, ui_fs);
    glAttachShader (uiShaderProgram, ui_vs);
    glLinkProgram (uiShaderProgram);
    
    //retrieve shader uniforms and attributes ids
    uiMvp = glGetUniformLocation(uiShaderProgram, "mvp");
    textureDataUniform = glGetUniformLocation(uiShaderProgram, "textureData");
    GLuint uiPositionAttribute = glGetAttribLocation(uiShaderProgram, "vertexCoord");
    GLuint uiTextureAttribute = glGetAttribLocation(uiShaderProgram, "textureCoord");
    
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
    
    GLuint buffers[2];
    glGenBuffers(2, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    
    glm::vec3 topLeft = glm::vec3( 0, 0, 0 );
    glm::vec3 topRight = glm::vec3( 64, 0, 0 );
    glm::vec3 bottomLeft = glm::vec3( 0, 64, 0 );
    glm::vec3 bottomRight = glm::vec3( 64, 64, 0 );
    
    vertices.push_back( topLeft );
    vertices.push_back( topRight );
    vertices.push_back( bottomLeft );
    vertices.push_back( bottomLeft );
    vertices.push_back( topRight );
    vertices.push_back( bottomRight );
    
    glm::vec2 uvTopLeft = glm::vec2( 0.0, 0.0 );
    glm::vec2 uvTopRight = glm::vec2( 1.0, 0.0 );
    glm::vec2 uvBottomLeft = glm::vec2( 0.0, 1.0 );
    glm::vec2 uvBottomRight = glm::vec2( 1.0, 1.0 );
    
    uvs.push_back( uvTopLeft );
    uvs.push_back( uvTopRight );
    uvs.push_back( uvBottomLeft );
    uvs.push_back( uvBottomLeft );
    uvs.push_back( uvTopRight );
    uvs.push_back( uvBottomRight );
    
    glBufferData (GL_ARRAY_BUFFER, (sizeof (GLfloat) * 3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    //set vertex array layout for shader attibute and enable attibute
    glVertexAttribPointer (uiPositionAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(uiPositionAttribute);
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData (GL_ARRAY_BUFFER, (sizeof (GLfloat) * 2) * uvs.size(), &uvs[0], GL_STATIC_DRAW);
    //set vertex array layout for shader attibute and enable attibute
    glVertexAttribPointer (uiTextureAttribute, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(uiTextureAttribute);
    
    glGenTextures(1, &textureUID);
    
    glBindTexture( GL_TEXTURE_2D, textureUID );
    // Set the texture wrapping/filtering options (on the currently bound texture object)
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    Texture* textureData = new Texture( "g_bubble_red.png" );
    // Load and generate the texture
    glTexImage2D( GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 textureData->getWidth(),
                 textureData->getHeight(),
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 textureData->getImageData() );
    glBindTexture( GL_TEXTURE, 0 );
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
    
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(textureDataUniform, 0); //set to 0 because the texture is bound to GL_TEXTURE0
    glBindTexture(GL_TEXTURE_2D, textureUID);
    
    glm::mat4 orthoMatrix = glm::ortho(0.0, 640.0, 480.0, 0.0 );
    glUniformMatrix4fv(uiMvp, 1, GL_FALSE, &orthoMatrix[0][0]);
    // draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays (GL_TRIANGLES, 0, vertices.size());
    
    // update other events like input handling
    glfwPollEvents ();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers (window);
}