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
#include "PngTextureLoader.h"
#include "MomoRenderState.h"
#include "MapRenderState.h"

Renderer::Renderer( GLFWwindow* window ) : window( window ) {

}

Renderer::~Renderer(){
}

void Renderer::init(){
    initOpenGLStates();
    loadUIShaders();
    
    states[MOMO_RENDER_STATE] = new MomoRenderState;
    states[MAP_RENDER_STATE] = new MapRenderState;
    
    currentState = states[MAP_RENDER_STATE];
    
    uiVerticesBufer = new Buffer( new GLGpuBuffer );
    uiUvsBuffer = new Buffer( new GLGpuBuffer );
    currentState->init();
}

void Renderer::initOpenGLStates() {
    const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString (GL_VERSION); // version as a string
    printf ("Renderer: %s\n", renderer);
    printf ("OpenGL version supported %s\n", version);
    
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);
    //enable alpha
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glClearColor( 0.5f, 0.5f, 1.0f, 1.0f );
    
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
}

void Renderer::updateState( const int stateCode ) {
    currentState = states[ stateCode ];
}

void Renderer:: updateProjection( glm::mat4 projectionMatrix ) {
    currentState->updateProjection( projectionMatrix );
}

void Renderer::updateViewMatrix( glm::mat4 viewMatrix ) {
    currentState->updateCamera( viewMatrix );
}

void Renderer::updateLightSource( glm::vec3 lightSource ) {
    currentState->updateLightSource( lightSource );
}

void Renderer::load( std::vector<Node *> renderBatch ) {
    currentState->load( renderBatch );
}

void Renderer::draw( std::vector<Node *> renderBatch ) {
    currentState->draw( renderBatch );
}

void Renderer::loadUIShaders() {
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
    
    uiTextureData = glGetUniformLocation( uiShaderProgram, "textureData" );
    uiMVPMatrix = glGetUniformLocation( uiShaderProgram,
                                        "modelViewProjectionMatrix" );
    
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
        
        uvs.push_back( uvBottomLeft );
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
    uiVerticesBufer->bind();
    
    for ( int i = 0; i < uiComponents.size(); i++ ) {
        Mesh* mesh = uiComponents.at(i)->mesh;
        uiVerticesBufer->push( (float*)&mesh->getVertices()[0],
                               ( sizeof ( GLfloat ) * 3 ) * mesh->getVertices().size() );
    }
    //set vertex array layout for shader attibute and enable attibute
    glVertexAttribPointer (uiPositionAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(uiPositionAttribute);
    
    uiUvsBuffer->bind();
    for ( int i = 0; i < uiComponents.size(); i++ ) {
        Mesh* mesh = uiComponents.at(i)->mesh;
        uiUvsBuffer->push( (float*)&mesh->getUvs()[0],
                           ( sizeof ( GLfloat ) * 2 ) * mesh->getUvs().size() );
    }
    //set uvs array layout for shader attribute and enable attribute
    glVertexAttribPointer( uiTextureAttribute, 2, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( uiTextureAttribute );

    for ( int i = 0;  i < uiComponents.size(); i++ ) {
        UIComponent* component = uiComponents.at( i );
        if( component->texture != nullptr ) {
            component->texture->bind();
            component->texture->push();
            component->texture->unbind();
        }
    }
}

void Renderer::drawUI(  ) {
    glm::mat4 orthoMatrix = glm::ortho( 0.0, 640.0, 480.0, 0.0 );
    glUseProgram ( uiShaderProgram );
    glBindVertexArray (vao);
    
    GLuint offset = 0;
    for ( int i = 0; i < uiComponents.size(); i++ ) {
        UIComponent* component = uiComponents.at( i );
        if( component->texture != nullptr ){
            component->texture->bind();
            glUniform1i(uiTextureData, 0);
        }

        glm::mat4 MVPMatrix = orthoMatrix;
        glUniformMatrix4fv(uiMVPMatrix, 1, GL_FALSE, &MVPMatrix[0][0]);

        glDrawArrays ( GL_TRIANGLES,
                      offset,
                      (int)component->mesh->getVertices().size() );
        offset += (int)component->mesh->getVertices().size();
        if( component->texture != nullptr ){
            component->texture->unbind();
        }
    }
}

void Renderer::clear() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::present() {
    glfwSwapBuffers (window);
}