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
    
    shaderProgram = glCreateProgram ();
    glAttachShader ( shaderProgram, fragmentShader->getUID() );
    glAttachShader ( shaderProgram, vertexShader->getUID() );
    glLinkProgram ( shaderProgram );
    
    GLint isLinked = 0;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isLinked);
    
    if(isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
        
        //The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);
        std::cout <<  &infoLog[0] << std::endl;
        //The program is useless now. So delete it.
        glDeleteProgram(shaderProgram);
        
        //Provide the infolog in whatever manner you deem best.
        //Exit with failure.
    }
    
    //retrieve shader uniforms and attributes ids
    projectionUID = glGetUniformLocation( shaderProgram, "projectionMatrix" );
    modelViewUID = glGetUniformLocation( shaderProgram, "modelViewMatrix" );
    
    colorUniform = glGetUniformLocation( shaderProgram, "color" );
    
    positionAttribute = 6;
    normalAttribute = 7;
    
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
    glVertexAttribPointer ( positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL) ;
    glEnableVertexAttribArray( positionAttribute );
    verticesBuffer->unBind();
    
    normalBuffer->bind();
    for ( int i = 0; i < renderBatch.size(); i++ ) {
        Mesh* mesh = renderBatch.at(i)->getMesh();
        GLsizeiptr size = ( sizeof( GLfloat ) * 3 ) * mesh->getNormals().size();
        normalBuffer->push( (float*) &mesh->getNormals()[0], size );
    }
    
    glVertexAttribPointer( normalAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( normalAttribute );
    normalBuffer->unBind();
    
    glBindVertexArray( 0 );
}

void MapRenderState::draw( std::vector<Node*> renderBatch ) {
    glUseProgram ( shaderProgram );
    glUniformMatrix4fv( projectionUID , 1, GL_FALSE, &projectionMatrix[0][0]);
    glBindVertexArray ( vao );

    int offset = 0;
    for ( int i = 0; i < renderBatch.size(); i++ ) {
        Node* node = renderBatch.at( i );
        //TODO: Fixed color: retrieve from material
        glm::vec3 color = glm::vec3( (i % 2) * 0.5f , 1.0f, 1.0f );
        glUniform3fv(colorUniform, 1, &color[0] );
        
        glm::mat4 modelViewMatrix = viewMatrix * *node->getToWorldMatrix();
        glUniformMatrix4fv( modelViewUID , 1, GL_FALSE,
                            &modelViewMatrix[0][0]);
        glDrawArrays ( GL_TRIANGLES,
                       offset,
                       (int)node->getMesh()->getVertices().size());
        offset += (int)node->getMesh()->getVertices().size();
    }
    glBindVertexArray( 0 );
}