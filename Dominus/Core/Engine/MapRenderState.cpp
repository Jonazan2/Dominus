//
//  MapRenderState.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 2/4/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "MapRenderState.h"
#include "Shader.h"
#include "GLGpuBuffer.h"

MapRenderState::MapRenderState() {
    colorBuffer = new Buffer( new GLGpuBuffer );
    verticesBuffer = new Buffer( new GLGpuBuffer );
}

MapRenderState::~MapRenderState() {

}

void MapRenderState::updateCamera( glm::mat4 camera ) {
    this->viewMatrix = camera;
}

void MapRenderState::updateProjection( glm::mat4 projection ) {
    this->projectionMatrix = projection;
}

void MapRenderState::updateLightSource( glm::vec3 light ) {
    //TODO: not handling illumination
}

void MapRenderState::init() {
    Shader* vertexShader = new Shader( "map_vertex_shader.glsl",
                                       GL_VERTEX_SHADER );
    vertexShader->compile();
    
    Shader* fragmentShader = new Shader( "map_fragment_shader.glsl",
                                         GL_FRAGMENT_SHADER );
    fragmentShader->compile();
    
    shaderProgram = glCreateProgram ();
    glAttachShader ( shaderProgram, fragmentShader->getUID() );
    glAttachShader ( shaderProgram, vertexShader->getUID() );
    glLinkProgram ( shaderProgram );
    
    //retrieve shader uniforms and attributes ids
    projectionMatrixUID = glGetUniformLocation( shaderProgram , "modelViewMatrix" );
    modelViewMatrixUID = glGetUniformLocation( shaderProgram , "projectionMatrix" );
    
    positionAttribute = glGetAttribLocation( shaderProgram , "vertex" );
    colorAttribute = glGetAttribLocation( shaderProgram , "color" );
    
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
}

void MapRenderState::load( std::vector<Node*> renderBatch ) {
    verticesBuffer->bind();
    for ( int i = 0; i < renderBatch.size(); i++ ) {
        Mesh* mesh = renderBatch.at(i)->getMesh();
        verticesBuffer->push( (float*) &mesh->getVertices()[0],
                              ( sizeof( GLfloat ) * 3 ) *
                                mesh->getVertices().size() );
    }
    
    //TODO: Dont allow this operation if the vao is not binded
    glVertexAttribPointer ( positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL) ;
    glEnableVertexAttribArray( positionAttribute );
    verticesBuffer->unBind();
    
    colorBuffer->bind();
    for ( int i = 0; i < renderBatch.size(); i++ ) {
        Mesh* mesh = renderBatch.at(i)->getMesh();
        colorBuffer->push( (float*) &mesh->getNormals()[0],
                             ( sizeof( GLfloat ) * 3 ) *
                                mesh->getNormals().size() );
    }
    
    glVertexAttribPointer( colorAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( colorAttribute );
    colorBuffer->unBind();
}

void MapRenderState::draw( std::vector<Node*> renderBatch ) {
    glUseProgram ( shaderProgram );
    glUniformMatrix4fv( projectionMatrixUID , 1, GL_FALSE, &projectionMatrix[0][0]);
    glBindVertexArray ( vao );

    int offset = 0;
    for ( int i = 0; i < renderBatch.size(); i++ ) {
        Node* node = renderBatch.at( i );
        glm::mat4 modelViewMatrix = viewMatrix * *node->getToWorldMatrix();
        glUniformMatrix4fv( modelViewMatrixUID , 1, GL_FALSE,
                            &modelViewMatrix[0][0]);
        glDrawArrays ( GL_TRIANGLES,
                       offset,
                       (int)node->getMesh()->getVertices().size());
        offset += (int)node->getMesh()->getVertices().size();
    }
    glBindVertexArray( 0 );
}