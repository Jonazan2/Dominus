//
//  MomoRenderState.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 2/4/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "MomoRenderState.h"
#include "GLGpuBuffer.h"
#include "Shader.h"

MomoRenderState::MomoRenderState() {
    verticesBuffer = new Buffer( new GLGpuBuffer );
    uvsBuffer = new Buffer( new GLGpuBuffer );
    normalBuffer = new Buffer( new GLGpuBuffer );
}

MomoRenderState::~MomoRenderState() {

}

void MomoRenderState::updateCamera( glm::mat4 camera ) {
    this->viewMatrix = camera;
}

void MomoRenderState::updateProjection( glm::mat4 projection ) {
    this->projectionMatrix = projection;
}

void MomoRenderState::updateLightSource( glm::vec3 light ) {
    this->lightPosition = light;
}

void MomoRenderState::init() {
    Shader* vertexShader = new Shader( "vertex_shader.glsl",
                                      GL_VERTEX_SHADER );
    vertexShader->compile();
    
    Shader* fragmentShader = new Shader( "fragment_shader.glsl",
                                        GL_FRAGMENT_SHADER );
    fragmentShader->compile();
    
    shaderProgram = glCreateProgram ();
    glAttachShader ( shaderProgram, fragmentShader->getUID() );
    glAttachShader ( shaderProgram, vertexShader->getUID() );
    glLinkProgram ( shaderProgram );
    
    //retrieve shader uniforms and attributes ids
    textureUID = glGetUniformLocation(shaderProgram, "textureData");
    modelViewUID = glGetUniformLocation(shaderProgram, "modelViewMatrix");
    projectionUID = glGetUniformLocation(shaderProgram, "projectionMatrix");
    normalUID = glGetUniformLocation(shaderProgram, "normalMatrix");
    lightPositionUID = glGetUniformLocation(shaderProgram, "lightPosition");
    
    positionAttribute = 1;
    normalAttribute = 2;
    textureAttribute = 3;
    
    glGenVertexArrays ( 1, &vao );
}

void MomoRenderState::load( std::vector<Node *> renderBatch ) {
    glBindVertexArray ( vao );
    
    verticesBuffer->bind();
    for ( int i = 0; i < renderBatch.size(); i++ ) {
        Mesh* mesh = renderBatch.at(i)->getMesh();
        verticesBuffer->push( (float*) &mesh->getVertices()[0],
                             ( sizeof( GLfloat ) * 3 ) * mesh->getVertices().size() );
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
    
    glBindVertexArray( 0 );
}

void MomoRenderState::draw( std::vector<Node *> renderBatch ) {
    glUseProgram (shaderProgram);
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
    
    glBindVertexArray( 0 );
}

