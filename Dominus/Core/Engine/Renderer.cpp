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

Renderer::Renderer( GLFWwindow* window )
: window( window ), currentState( nullptr ) {
    shaderProgram = new ShaderProgram;
}

Renderer::~Renderer(){
}

void Renderer::init(){
    initOpenGLStates();
    
    positionAttributeKey = "vertexCoord";
    textureAttributeKey = "textureCoord";
    mvpUniformKey = "modelViewProjectionMatrix";
    textureDataUniformKey = "textureData";
    
    states[MOMO_RENDER_STATE] = new MomoRenderState;
    states[MAP_RENDER_STATE] = new MapRenderState;
    
    currentState = states[MAP_RENDER_STATE];
    
    uiVerticesBufer = new Buffer( new GLGpuBuffer );
    uiUvsBuffer = new Buffer( new GLGpuBuffer );
    
    states[MOMO_RENDER_STATE]->init();
    states[MAP_RENDER_STATE]->init();
    
    loadUIShaders();
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
    
    glGenVertexArrays ( 1, &vao );
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

void Renderer::load( Node *node ) {
    currentState->load( node );
}

void Renderer::draw( Node *node ) {
    currentState->draw( node );
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
    
    shaderProgram->attachShader( vertexShader );
    shaderProgram->attachShader( fragmentShader );
    
    shaderProgram->linkProgram();
    
    shaderProgram->registerUnitform( mvpUniformKey );
    shaderProgram->registerUnitform( textureDataUniformKey );
    shaderProgram->registerAttribute( positionAttributeKey );
    shaderProgram->registerAttribute( textureAttributeKey );
}

void Renderer::drawtexture( UIComponent* component ){
    if( component->getTexture() != nullptr ) {
        glm::vec2 position = component->getPosition();
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        glm::vec3 topLeft = glm::vec3( position.x, position.y, 0 );
        glm::vec3 topRight = glm::vec3( position.x + component->getWidth(),
                                       position.y, 0 );
        glm::vec3 bottomLeft = glm::vec3( position.x,
                                         position.y + component->getHeight(), 0 );
        glm::vec3 bottomRight = glm::vec3( position.x + component->getWidth(),
                                          position.y + component->getHeight(), 0 );
        
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
        component->getMesh()->setVertices( vertices );
        component->getMesh()->setUvs( uvs );
        
        uiComponents.push_back( std::shared_ptr< UIComponent >( component ) );
    }
}

void Renderer::loadUI(  ) {
    glBindVertexArray ( vao );

    uiVerticesBufer->bind();
    
    for ( int i = 0; i < uiComponents.size(); i++ ) {
        Mesh* mesh = uiComponents.at(i)->getMesh();
        GLsizeiptr size = ( sizeof ( GLfloat ) * 3 ) * mesh->getVertices().size();
        uiVerticesBufer->push( (float*)&mesh->getVertices()[0], size );
    }
    //set vertex array layout for shader attibute and enable attibute
    glVertexAttribPointer ( shaderProgram->getAttribute( positionAttributeKey ),
                            3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray( shaderProgram->getAttribute(positionAttributeKey) );
    
    uiUvsBuffer->bind();
    for ( int i = 0; i < uiComponents.size(); i++ ) {
        Mesh* mesh = uiComponents.at(i)->getMesh();
        GLsizeiptr size = ( sizeof ( GLfloat ) * 2 ) * mesh->getUvs().size();
        uiUvsBuffer->push( (float*)&mesh->getUvs()[0], size );
    }
    //set uvs array layout for shader attribute and enable attribute
    glVertexAttribPointer( shaderProgram->getAttribute( textureAttributeKey ),
                           2, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( shaderProgram->getAttribute( textureAttributeKey ) );

    for ( int i = 0;  i < uiComponents.size(); i++ ) {
        std::shared_ptr<UIComponent> component = uiComponents.at( i );
        if( component->getTexture() != nullptr ) {
            component->getTexture()->bind();
            component->getTexture()->push();
            component->getTexture()->unbind();
        }
    }
    glBindVertexArray ( 0 );
}

void Renderer::drawUI(  ) {
    glm::mat4 orthoMatrix = glm::ortho( 0.0, 640.0, 480.0, 0.0 );
    shaderProgram->useProgram();
    glBindVertexArray ( vao );
    
    GLuint offset = 0;
    for ( int i = 0; i < uiComponents.size(); i++ ) {
        std::shared_ptr<UIComponent> component = uiComponents.at( i );
        if( component->getTexture() != nullptr ) {
            component->getTexture()->bind();
            glUniform1i( shaderProgram->getUniform( textureDataUniformKey ) , 0 );
        }

        glm::mat4 MVPMatrix = orthoMatrix;
        glUniformMatrix4fv( shaderProgram->getUniform( mvpUniformKey ),
                            1, GL_FALSE, &MVPMatrix[0][0] );

        glDrawArrays ( GL_TRIANGLES,
                      offset,
                      (int)component->getMesh()->getVertices().size() );
        offset += (int)component->getMesh()->getVertices().size();
        if( component->getTexture() != nullptr ) {
            component->getTexture()->unbind();
        }
    }
    
    glBindVertexArray( 0 );
    shaderProgram->closeProgram();
}

void Renderer::clear() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::present() {
    glfwSwapBuffers (window);
}