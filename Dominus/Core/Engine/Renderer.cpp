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

Renderer::Renderer( GLFWwindow* window ) : window( window ) {

}

Renderer::~Renderer(){
}

void Renderer::init(){
    initOpenGLStates();
    loadShaders();
    loadUIShaders();
    
    verticesBuffer = new Buffer( new GLGpuBuffer );
    uvsBuffer = new Buffer( new GLGpuBuffer );
    normalBuffer = new Buffer( new GLGpuBuffer );
    
    uiVerticesBufer = new Buffer( new GLGpuBuffer );
    uiUvsBuffer = new Buffer( new GLGpuBuffer );
}

void Renderer::initOpenGLStates() {
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
    glClearColor( 0.5f, 0.5f, 1.0f, 1.0f );
    
    //create vao and set as current
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
}

void Renderer::loadShaders() {
    
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
    
    positionAttribute = 1;
    normalAttribute = 2;
    textureAttribute = 3;
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
    
    uiTextureData = glGetUniformLocation(uiShaderProgram, "textureData");
    uiMVPMatrix = glGetUniformLocation(uiShaderProgram, "modelViewProjectionMatrix");
    
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

void Renderer::load( std::vector<Node*> renderBatch ) {
    verticesBuffer->bind();
    for ( int i = 0; i < renderBatch.size(); i++ ) {
        Mesh* mesh = renderBatch.at(i)->getMesh();
        verticesBuffer->push( (float*)&mesh->getVertices()[0],
                              ( sizeof ( GLfloat ) * 3 ) * mesh->getVertices().size() );
    }
    glVertexAttribPointer (positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(positionAttribute);
    
    normalBuffer->bind();
    for ( int i = 0; i < renderBatch.size(); i++ ) {
        Mesh* mesh = renderBatch.at(i)->getMesh();
        normalBuffer->push( (float*)&mesh->getNormals()[0],
                            ( sizeof ( GLfloat ) * 3 ) * mesh->getNormals().size() );
    }

    glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(normalAttribute);
    
    uvsBuffer->bind();
    for ( int i = 0; i < renderBatch.size(); i++ ) {
        Mesh* mesh = renderBatch.at(i)->getMesh();
        uvsBuffer->push( (float*)&mesh->getUvs()[0],
                         ( sizeof ( GLfloat ) * 2 ) * mesh->getUvs().size() );
    }
    
    glVertexAttribPointer( textureAttribute, 2, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( textureAttribute );
    
    //Texture loading
    for ( int i = 0;  i < renderBatch.size(); i++ ) {
        Texture* texture = renderBatch.at( i )->getMesh()->getTexture();
        if( texture != nullptr ){
            texture->bind();
            texture->push();
            texture->unbind();
        }
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

void Renderer::draw( std::vector<Node*> renderBatch ) {
    glUseProgram (shader_programme);
    glUniformMatrix4fv(projectionUID, 1, GL_FALSE, &projectionMatrix[0][0]);
    glUniform3fv(lightPositionUID, 1, &lightPosition[0]);
    glBindVertexArray (vao);
    
    GLuint offset = 0;
    for ( int i = 0; i < renderBatch.size() ; i++ ) {
        Node* node = renderBatch.at( i );
        if( node->getMesh()->getTexture() != nullptr ) {
            node->getMesh()->getTexture()->bind();
            glUniform1i(textureUID, 0);
        }
        
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
        if( node->getMesh()->getTexture() != nullptr ) {
            node->getMesh()->getTexture()->unbind();
        }
    }
}

void Renderer::drawUI(  ) {
    glm::mat4 orthoMatrix = glm::ortho( 0.0, 640.0, 480.0, 0.0 );
    glUseProgram ( uiShaderProgram );
    glBindVertexArray (vao);
    
    GLuint offset = 0;
    for ( int i = 0; i < uiComponents.size(); i++ ) {
        Mesh* mesh = uiComponents.at(i)->mesh;
        if( uiComponents.at(i)->texture != nullptr ){
            uiComponents.at(i)->texture->bind();
            glUniform1i(uiTextureData, 0);
        }

        glm::mat4 MVPMatrix = orthoMatrix;
        glUniformMatrix4fv(uiMVPMatrix, 1, GL_FALSE, &MVPMatrix[0][0]);

        glDrawArrays ( GL_TRIANGLES,
                      offset,
                      (int)mesh->getVertices().size() );
        offset += (int)mesh->getVertices().size();
        if( mesh->getTexture() != nullptr ){
            mesh->getTexture()->unbind();
        }
    }
}

void Renderer::updateProjection( glm::mat4 projectionMatrix ) {
    this->projectionMatrix = projectionMatrix;
}

void Renderer:: updateViewMatrix( glm::mat4 viewMatrix ) {
    this->viewMatrix = viewMatrix;
}

void Renderer::updateLightSource( glm::vec3 lightSource ) {
    this->lightPosition = lightSource;
}

void Renderer::clear() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::present() {
    glfwSwapBuffers (window);
}