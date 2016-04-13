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
#include "Log.hpp"

MapRenderState::MapRenderState()
: units(0) {
    normalBuffer = std::shared_ptr<Buffer>( new Buffer( make_unique< GLGpuBuffer >() ));
    verticesBuffer = std::shared_ptr<Buffer>( new Buffer( make_unique< GLGpuBuffer >() ) );
    
    shaderProgram = std::shared_ptr<ShaderProgram>( new ShaderProgram );
    
    colorUniformKey = "color";
    projectionUniformKey = "projectionMatrix";
    modelViewUniformKey = "modelViewMatrix";
    positionAttributeKey = "vertex";
    normalAttributeKey = "normal";
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
    std::shared_ptr<Shader> vertexShader =
            std::shared_ptr<Shader>( new Shader( "shaders/map_vertex_shader.glsl",
                                         GL_VERTEX_SHADER ) );
    vertexShader->compile();
    
    std::shared_ptr<Shader> fragmentShader =
        std::shared_ptr<Shader>( new Shader( "shaders/map_fragment_shader.glsl",
                                        GL_FRAGMENT_SHADER ) );
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
    glBindVertexArray ( vao );
    
    //Setup vao with the given vbo
    verticesBuffer->bind();
    //TODO: Dont allow this operation if the vao is not binded
    glVertexAttribPointer ( shaderProgram->getAttribute( positionAttributeKey ),
                           3, GL_FLOAT, GL_FALSE, 0, NULL) ;
    glEnableVertexAttribArray( shaderProgram->getAttribute(positionAttributeKey) );
    verticesBuffer->unBind();
    
    normalBuffer->bind();
    glVertexAttribPointer( shaderProgram->getAttribute( normalAttributeKey ),
                          3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( shaderProgram->getAttribute( normalAttributeKey ) );
    normalBuffer->unBind();
    
    glBindVertexArray ( 0 );
}

void MapRenderState::load( std::shared_ptr<Node> node ) {
    std::shared_ptr<Mesh> mesh = node->getMesh();

    glBindVertexArray ( vao );
    
    verticesBuffer->bind();
    GLsizeiptr size = ( sizeof( GLfloat ) * 3 ) * mesh->getVertices().size();
    verticesBuffer->push( (float*) &mesh->getVertices()[0], size );
    //TODO: this should be automatic...
    offsetMap[node->getID()] = units;
    units += mesh->getVertices().size();
    verticesBuffer->unBind();
    
    normalBuffer->bind();
    size = ( sizeof( GLfloat ) * 3 ) * mesh->getNormals().size();
    normalBuffer->push( (float*) &mesh->getNormals()[0], size );
    normalBuffer->unBind();
    
    glBindVertexArray( 0 );
}

void MapRenderState::draw( std::shared_ptr<Node> node ) {
    shaderProgram->useProgram();
    glUniformMatrix4fv( shaderProgram->getUniform( projectionUniformKey ) ,
                       1, GL_FALSE, &projectionMatrix[0][0]);
    glBindVertexArray ( vao );
    
    glm::vec3 color = glm::vec3( (node->getID() % 2) * 0.5f , 1.0f, 1.0f );
    glUniform3fv( shaderProgram->getUniform( colorUniformKey ),
                 1, &color[0] );
    
    glm::mat4 modelViewMatrix = viewMatrix * *node->getToWorldMatrix();
    glUniformMatrix4fv( shaderProgram->getUniform( modelViewUniformKey ),
                       1, GL_FALSE,
                       &modelViewMatrix[0][0]);
    glDrawArrays ( GL_TRIANGLES,
                  (int)offsetMap[node->getID()],
                  (int)node->getMesh()->getVertices().size());
    glBindVertexArray( 0 );
    shaderProgram->closeProgram();
}

MapRenderState::~MapRenderState() {}