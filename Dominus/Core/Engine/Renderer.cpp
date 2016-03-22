//
//  Renderer.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 03/02/16.
//  Copyright (c) 2016 frikazos. All rights reserved.
//

#include "Renderer.h"
#include "Log.hpp"
#include "Texture.h"
#include "Shader.h"
#include "UIComponent.h"

Renderer::Renderer( GLFWwindow* window ) : window( window ) {

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

void Renderer::init(){
    // get version info
    const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString (GL_VERSION); // version as a string
    printf ("Renderer: %s\n", renderer);
    printf ("OpenGL version supported %s\n", version);
    
    // opengl states
    glEnable (GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as
    //enable alpha
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //create vao and set as current
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    
    Shader* vertexShader = new Shader( "vertex_shader.glsl", GL_VERTEX_SHADER );
    vertexShader->compile();
    
    Shader* fragmentShader = new Shader( "fragment_shader.glsl", GL_FRAGMENT_SHADER );
    fragmentShader->compile();
    
    shader_programme = glCreateProgram ();
    glAttachShader ( shader_programme, fragmentShader->getUID() );
    glAttachShader ( shader_programme, vertexShader->getUID() );
    glLinkProgram ( shader_programme );
    
    //retrieve shader uniforms and attributes ids
    textureUID = glGetUniformLocation(shader_programme, "textureData");
    modelViewUID = glGetUniformLocation(shader_programme, "modelViewMatrix");
    projectionUID = glGetUniformLocation(shader_programme, "projectionMatrix");
    normalUID = glGetUniformLocation(shader_programme, "normalMatrix");
    lightPositionUID = glGetUniformLocation(shader_programme, "lightPosition");
    
//    positionAttribute = glGetAttribLocation(shader_programme, "vp");
//    normalAttribute = glGetAttribLocation(shader_programme, "normalAttribute");
//    textureAttribute = glGetAttribLocation(shader_programme, "textureCoord");
    positionAttribute = 1;
    normalAttribute = 2;
    textureAttribute = 3;
    glClearColor( 0.5f, 0.5f, 1.0f, 1.0f );
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
    GLuint buffers[3];
    glGenBuffers( 3, buffers );
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    
    //allocate buffer memory to load all the vertex
    GLsizeiptr vertexBufferSize = 0;
    GLsizeiptr normalBufferSize = 0;
    GLsizeiptr uvBufferSize = 0;
    for ( int i = 0; i < renderBatch.size(); i++ ) {
        Node* node = renderBatch.at(i);
        Mesh* mesh = node->getMesh();
        vertexBufferSize += mesh->getSize();
        normalBufferSize += mesh->getNormalVerticesSize();
        uvBufferSize += mesh->getTextureVerticesSize();
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
                        node->getMesh()->getNormalVerticesSize(), // size
                        &node->getMesh()->getNormals()[0]); // data
        normalOffset += node->getMesh()->getNormalVerticesSize();
    }
    //set normal array layout for shader attribute and enable attribute
    glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(normalAttribute);
    
    int numTextures = 0;
    for ( int i = 0; i < renderBatch.size(); i++ ) {
        Mesh* mesh = renderBatch.at( i )->getMesh();
        if( !mesh->getTexturePath().empty() ) {
            numTextures++;
        }
    }
    GLuint textures [numTextures];
    glGenTextures(numTextures, textures);
    
    GLuint actualTexture = 0;
    //Texture loading
    for ( int i = 0;  i < renderBatch.size(); i++ ) {
        Mesh* mesh = renderBatch.at( i )->getMesh();
        if( !mesh->getTexturePath().empty() ) {
            Texture* textureData = new Texture( mesh->getTexturePath() );
            mesh->textureUID = textures[actualTexture];
            glBindTexture( GL_TEXTURE_2D, textures[actualTexture] );
            // Set the texture wrapping/filtering options (on the currently bound texture object)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
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
            actualTexture++;
        }
    }
    
    glBindBuffer( GL_ARRAY_BUFFER, buffers[2] );
    glBufferData ( GL_ARRAY_BUFFER,
                  uvBufferSize,
                  NULL,
                  GL_STATIC_DRAW );
    GLuint textureOffset = 0;
    for ( int i = 0; i < renderBatch.size(); i++ ) {
        Node* node = renderBatch.at( i );
        glBufferSubData(GL_ARRAY_BUFFER, // target
                        textureOffset, // offset
                        node->getMesh()->getTextureVerticesSize(), // size
                        &node->getMesh()->getUvs()[0]); // data
        textureOffset += node->getMesh()->getTextureVerticesSize();
    }
    
    //set uvs array layout for shader attribute and enable attribute
    glVertexAttribPointer( textureAttribute, 2, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( textureAttribute );
}

void Renderer::draw( std::vector<Node*> renderBatch ) {
    glUseProgram (shader_programme);
    glUniformMatrix4fv(projectionUID, 1, GL_FALSE, &projectionMatrix[0][0]);
    glUniform3fv(lightPositionUID, 1, &lightPosition[0]);
    glBindVertexArray (vao);
    
    GLuint offset = 0;
    for ( int i = 0; i < renderBatch.size() ; i++ ) {
        Node* node = renderBatch.at( i );
        // bind the texture and set the "tex" uniform in the fragment shader
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(textureUID, 0); //set to 0 because the texture is bound to GL_TEXTURE0
        glBindTexture(GL_TEXTURE_2D, node->getMesh()->textureUID);
        //
        glm::mat4 modelViewMatrix = viewMatrix * *node->getToWorldMatrix();
        glm::mat4 normalMat = glm::transpose( glm::inverse( modelViewMatrix ) );
        glm::mat3 normalMat3 = glm::mat3( normalMat );
        glUniformMatrix4fv(modelViewUID, 1, GL_FALSE, &modelViewMatrix[0][0]);
        glUniformMatrix3fv(normalUID, 1, GL_FALSE, &normalMat3[0][0]);
        // draw points from the currently bound VAO with current in-use shader
        glDrawArrays (GL_TRIANGLES,
                        offset,
                        (int)node->getMesh()->getVertices().size());
        offset += (int)node->getMesh()->getVertices().size();
        glBindTexture( GL_TEXTURE_2D , 0 );
    }
}

void Renderer::initUI() {
    Shader* vertexShader = new Shader(
                                      "shaders/ui_vertex_shader.glsl",
                                      GL_VERTEX_SHADER );
    vertexShader->compile();
    
    Shader* fragmentShader = new Shader(
                                        "shaders/ui_fragment_shader.glsl",
                                        GL_FRAGMENT_SHADER );
    fragmentShader->compile();
    
    uiShaderProgram = glCreateProgram ();
    glAttachShader ( uiShaderProgram, fragmentShader->getUID() );
    glAttachShader ( uiShaderProgram, vertexShader->getUID() );
    glLinkProgram ( uiShaderProgram );
    
    //retrieve shader uniforms and attributes ids
    uiTextureData = glGetUniformLocation(uiShaderProgram, "textureData");
    uiMVPMatrix = glGetUniformLocation(uiShaderProgram, "modelViewProjectionMatrix");
    
//    uiPositionAttribute = glGetAttribLocation(uiShaderProgram, "vertexCoord");
//    uiTextureAttribute = glGetAttribLocation(uiShaderProgram, "textureCoord");
    uiPositionAttribute = 4;
    uiTextureAttribute = 5;
}

void Renderer::drawtexture( UIComponent* component ){
    if( component->texture != nullptr ) {
        glm::vec2 position = component->getPosition();
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        glm::vec3 topLeft = glm::vec3( position.x, position.y, 0 );
        glm::vec3 topRight = glm::vec3( position.x + component->width,
                                       position.y, 0 );
        glm::vec3 bottomLeft = glm::vec3( position.x,
                                         position.y + component->height, 0 );
        glm::vec3 bottomRight = glm::vec3( position.x + component->width,
                                          position.y + component->height, 0 );
        
        vertices.push_back( topLeft );
        vertices.push_back( bottomLeft );
        vertices.push_back( topRight );
        vertices.push_back( bottomLeft );
        vertices.push_back( topRight);
        vertices.push_back( bottomRight );
        
        glm::vec2 uvTopLeft = glm::vec2( 0, 0 );
        glm::vec2 uvTopRight = glm::vec2( 1, 0 );
        glm::vec2 uvBottomLeft = glm::vec2( 0, 1 );
        glm::vec2 uvBottomRight = glm::vec2( 1, 1 );
        
        uvs.push_back(uvBottomLeft );
        uvs.push_back( uvTopLeft );
        uvs.push_back( uvBottomRight );
        uvs.push_back( uvTopLeft );
        uvs.push_back( uvBottomRight );
        uvs.push_back( uvTopRight );
        component->mesh->setVertices( vertices );
        component->mesh->setUvs( uvs );
        
        uiComponents.push_back( component );
    }
}

void Renderer::loadUI(  ) {
    //create buffer object and set as current
    GLuint buffers[2];
    glGenBuffers( 2, buffers );
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    
    //allocate buffer memory to load all the vertex
    GLsizeiptr vertexBufferSize = 0;
    GLsizeiptr uvBufferSize = 0;
    for ( int i = 0; i < uiComponents.size(); i++ ) {
        Mesh* uiComponent = uiComponents.at(i)->mesh;
        vertexBufferSize += uiComponent->getSize();
        uvBufferSize += uiComponent->getTextureVerticesSize();
    }
    glBufferData (GL_ARRAY_BUFFER,
                  vertexBufferSize,
                  NULL,
                  GL_STATIC_DRAW);
    //buffer vertex data
    GLuint offset = 0;
    for ( int i = 0; i < uiComponents.size(); i++ ) {
        Mesh* uiComponent = uiComponents.at(i)->mesh;
        glBufferSubData(GL_ARRAY_BUFFER, // target
                        offset, // offset
                        uiComponent->getSize(), // size
                        &uiComponent->getVertices()[0]); // data
        offset += uiComponent->getSize();
    }
    
    //set vertex array layout for shader attibute and enable attibute
    glVertexAttribPointer (uiPositionAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(uiPositionAttribute);
    
    int numTextures = 0;
    for ( int i = 0; i < uiComponents.size(); i++ ) {
        Mesh* uiComponent = uiComponents.at(i)->mesh;
        if( uiComponent->getTexture() != nullptr ) {
            numTextures++;
        }
    }
    GLuint textures [numTextures];
    glGenTextures(numTextures, textures);
    
    GLuint actualTexture = 0;
    //Texture loading
    for ( int i = 0;  i < uiComponents.size(); i++ ) {
        UIComponent* component = uiComponents.at( i );
        Mesh* mesh = uiComponents.at( i )->mesh;
        if( component->texture != nullptr ) {
            component->texture->textureUID = textures[actualTexture];
            glBindTexture( GL_TEXTURE_2D, textures[actualTexture] );
            // Set the texture wrapping/filtering options (on the currently bound texture object)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
            // Load and generate the texture
            glTexImage2D( GL_TEXTURE_2D,
                         0,
                         GL_RGBA,
                         component->texture->getWidth(),
                         component->texture->getHeight(),
                         0,
                         GL_RGBA,
                         GL_UNSIGNED_BYTE,
                         component->texture->getImageData() );
            glBindTexture( GL_TEXTURE, 0 );
            actualTexture++;
        }
    }
    
    glBindBuffer( GL_ARRAY_BUFFER, buffers[1] );
    glBufferData ( GL_ARRAY_BUFFER,
                  uvBufferSize,
                  NULL,
                  GL_STATIC_DRAW );
    GLuint textureOffset = 0;
    for ( int i = 0; i < uiComponents.size(); i++ ) {
        Mesh* uiComponent = uiComponents.at(i)->mesh;
        glBufferSubData(GL_ARRAY_BUFFER, // target
                        textureOffset, // offset
                        uiComponent->getTextureVerticesSize(), // size
                        &uiComponent->getUvs()[0]); // data
        textureOffset += uiComponent->getTextureVerticesSize();
    }
    
    //set uvs array layout for shader attribute and enable attribute
    glVertexAttribPointer( uiTextureAttribute, 2, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( uiTextureAttribute );
}

void Renderer::drawUI(  ) {
    glm::mat4 orthoMatrix = glm::ortho( 0.0, 640.0, 480.0, 0.0 );
    glUseProgram ( uiShaderProgram );
    glBindVertexArray (vao);
    
    GLuint offset = 0;
    for ( int i = 0; i < uiComponents.size(); i++ ) {
        UIComponent* uiComponent = uiComponents.at(i);
        Mesh* mesh = uiComponents.at(i)->mesh;
        glm::mat4 modelMatrix = glm::translate( glm::vec3(
                                                          uiComponent->position.x,
                                                          uiComponent->position.y,
                                                          0 ) );
        // bind the texture and set the "tex" uniform in the fragment shader
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(uiTextureData, 0); //set to 0 because the texture is bound to GL_TEXTURE0
        glBindTexture(GL_TEXTURE_2D, uiComponent->texture->textureUID);
        //
        glm::mat4 MVPMatrix = orthoMatrix;
        glUniformMatrix4fv(uiMVPMatrix, 1, GL_FALSE, &MVPMatrix[0][0]);
        // draw points from the currently bound VAO with current in-use shader
        glDrawArrays ( GL_TRIANGLES,
                      offset,
                      (int)mesh->getVertices().size() );
        offset += (int)mesh->getVertices().size();
        glBindTexture( GL_TEXTURE_2D , 0 );
    }
}

void Renderer::clear() {
    // wipe the drawing surface clear
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::present() {
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers (window);
    //uiComponents.clear();
}