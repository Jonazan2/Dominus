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
    normalBuffer = new Buffer( new GLGpuBuffer );
    verticesBuffer = new Buffer( new GLGpuBuffer );
    
    shaderProgram = new ShaderProgram;
    
    colorUniformKey = "color";
    projectionUniformKey = "projectionMatrix";
    modelViewUniformKey = "modelViewMatrix";
    positionAttributeKey = "vertex";
    normalAttributeKey = "normal";
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
    Shader* vertexShader = new Shader( "shaders/map_vertex_shader.glsl",
                                       GL_VERTEX_SHADER );
    vertexShader->compile();
    
    Shader* fragmentShader = new Shader( "shaders/map_fragment_shader.glsl",
                                         GL_FRAGMENT_SHADER );
    fragmentShader->compile();
    
    shaderProgram->attachShader( vertexShader );
    shaderProgram->attachShader( fragmentShader );
    
    shaderProgram->linkProgram();
    
    shaderProgram->registerAttribute( positionAttributeKey );
    shaderProgram->registerAttribute( normalAttributeKey );
    shaderProgram->registerUnitform( projectionUniformKey );
    shaderProgram->registerUnitform( modelViewUniformKey );
    shaderProgram->registerUnitform( colorUniformKey );
    
    glGenVertexArrays ( 1, &vao );
}

void MapRenderState::load( std::vector<Node*> renderBatch ) {
    glBindVertexArray ( vao );
    
    verticesBuffer->bind();
    for ( int i = 0; i < renderBatch.size(); i++ ) {
        Mesh* mesh = renderBatch.at(i)->getMesh();
        GLsizeiptr size = ( sizeof( GLfloat ) * 3 ) * mesh->getVertices().size();
        verticesBuffer->push( (float*) &mesh->getVertices()[0], size );
    }
    
    //TODO: Dont allow this operation if the vao is not binded
    glVertexAttribPointer ( shaderProgram->getAttribute( positionAttributeKey ),
                            3, GL_FLOAT, GL_FALSE, 0, NULL) ;
    glEnableVertexAttribArray( shaderProgram->getAttribute(positionAttributeKey) );
    verticesBuffer->unBind();
    
    normalBuffer->bind();
    for ( int i = 0; i < renderBatch.size(); i++ ) {
        Mesh* mesh = renderBatch.at(i)->getMesh();
        GLsizeiptr size = ( sizeof( GLfloat ) * 3 ) * mesh->getNormals().size();
        normalBuffer->push( (float*) &mesh->getNormals()[0], size );
    }
    
    glVertexAttribPointer( shaderProgram->getAttribute( normalAttributeKey ),
                           3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( shaderProgram->getAttribute( normalAttributeKey ) );
    normalBuffer->unBind();
    
    glBindVertexArray( 0 );
}

void MapRenderState::draw( std::vector<Node*> renderBatch ) {
    shaderProgram->useProgram();
    glUniformMatrix4fv( shaderProgram->getUniform( projectionUniformKey ) ,
                        1, GL_FALSE, &projectionMatrix[0][0]);
    glBindVertexArray ( vao );

    int offset = 0;
    for ( int i = 0; i < renderBatch.size(); i++ ) {
        Node* node = renderBatch.at( i );
        //TODO: Fixed color: retrieve from material
        glm::vec3 color = glm::vec3( (i % 2) * 0.5f , 1.0f, 1.0f );
        glUniform3fv( shaderProgram->getUniform( colorUniformKey ),
                      1, &color[0] );
        
        glm::mat4 modelViewMatrix = viewMatrix * *node->getToWorldMatrix();
        glUniformMatrix4fv( shaderProgram->getUniform( modelViewUniformKey ),
                            1, GL_FALSE,
                            &modelViewMatrix[0][0]);
        glDrawArrays ( GL_TRIANGLES,
                       offset,
                       (int)node->getMesh()->getVertices().size());
        offset += (int)node->getMesh()->getVertices().size();
    }
    glBindVertexArray( 0 );
    shaderProgram->closeProgram();
}