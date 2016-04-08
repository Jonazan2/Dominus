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

MomoRenderState::MomoRenderState()
: units( 0 ) {
    verticesBuffer = new Buffer( new GLGpuBuffer );
    uvsBuffer = new Buffer( new GLGpuBuffer );
    normalBuffer = new Buffer( new GLGpuBuffer );
    
    shaderProgram = new ShaderProgram;
    
    textureUniformKey = "textureData";
    modelViewUniformKey = "modelViewMatrix";
    projectionUniformKey = "projectionMatrix";
    normalUniformKey = "normalMatrix";
    lightUniformKey = "lightPosition";
    
    positionAttributeKey = "vp";
    textureAttributeKey = "textureCoord";
    normalAttributeKey = "normalAttribute";
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
    
    shaderProgram->attachShader( vertexShader );
    shaderProgram->attachShader( fragmentShader );
    
    shaderProgram->linkProgram();
    
    shaderProgram->registerAttribute( positionAttributeKey );
    shaderProgram->registerAttribute( normalAttributeKey );
    shaderProgram->registerAttribute( textureAttributeKey );
    
    shaderProgram->registerUnitform( modelViewUniformKey );
    shaderProgram->registerUnitform( projectionUniformKey );
    shaderProgram->registerUnitform( normalUniformKey );
    shaderProgram->registerUnitform( lightUniformKey );
    shaderProgram->registerUnitform( textureUniformKey );
    
    glGenVertexArrays ( 1, &vao );
    glBindVertexArray ( vao );
    
    verticesBuffer->bind();
    glVertexAttribPointer( shaderProgram->getAttribute( positionAttributeKey ),
                          3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray( shaderProgram->getAttribute(positionAttributeKey) );
    verticesBuffer->unBind();
    
    normalBuffer->bind();
    glVertexAttribPointer( shaderProgram->getAttribute( normalAttributeKey ),
                          3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray( shaderProgram->getAttribute( normalAttributeKey ) );
    normalBuffer->unBind();
    
    uvsBuffer->bind();
    glVertexAttribPointer( shaderProgram->getAttribute( textureAttributeKey ),
                          2, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( shaderProgram->getAttribute( textureAttributeKey ) );
    uvsBuffer->unBind();
    
    glBindVertexArray ( 0 );
}

void MomoRenderState::load( Node* node ) {
    glBindVertexArray ( vao );
    Mesh* mesh = node->getMesh();
    
    verticesBuffer->bind();
    verticesBuffer->push( (float*) &mesh->getVertices()[0],
                         ( sizeof( GLfloat ) * 3 ) * mesh->getVertices().size() );
    offsetMap[node->getID()] = units;
    units += mesh->getVertices().size();
    verticesBuffer->unBind();
    
    normalBuffer->bind();
    normalBuffer->push( (float*)&mesh->getNormals()[0],
                       ( sizeof ( GLfloat ) * 3 ) * mesh->getNormals().size() );
    normalBuffer->unBind();
    
    uvsBuffer->bind();
    uvsBuffer->push( (float*)&mesh->getUvs()[0],
                    ( sizeof ( GLfloat ) * 2 ) * mesh->getUvs().size() );
    uvsBuffer->unBind();
    
    //Texture loading
    Texture* texture = mesh->getTexture();
    if( texture != nullptr ){
        texture->bind();
        texture->push();
        texture->unbind();
    }
    
    glBindVertexArray( 0 );
}

void MomoRenderState::draw( Node* node ) {
    
    shaderProgram->useProgram();
    glUniformMatrix4fv( shaderProgram->getUniform( projectionUniformKey ),
                        1, GL_FALSE, &projectionMatrix[0][0] );
    glUniform3fv( shaderProgram->getUniform( lightUniformKey ),
                  1, &lightPosition[0]);
    glBindVertexArray ( vao );
    
    if( node->getMesh()->getTexture() != nullptr ) {
        node->getMesh()->getTexture()->bind();
        glUniform1i( shaderProgram->getUniform( textureUniformKey ) , 0);
    }
    
    glm::mat4 modelViewMatrix = viewMatrix * *node->getToWorldMatrix();
    glm::mat4 normalMat = glm::transpose( glm::inverse( modelViewMatrix ) );
    glm::mat3 normalMat3 = glm::mat3( normalMat );
    glUniformMatrix4fv( shaderProgram->getUniform( modelViewUniformKey ),
                       1, GL_FALSE, &modelViewMatrix[0][0] );
    glUniformMatrix3fv( shaderProgram->getUniform( normalUniformKey ),
                       1, GL_FALSE, &normalMat3[0][0] );
    // draw points from the currently bound VAO with current in-use shader
    glDrawArrays (GL_TRIANGLES,
                  (int)offsetMap[node->getID()],
                  (int)node->getMesh()->getVertices().size() );

    if( node->getMesh()->getTexture() != nullptr ) {
        node->getMesh()->getTexture()->unbind();
    }

    
    glBindVertexArray( 0 );
    shaderProgram->closeProgram();
}