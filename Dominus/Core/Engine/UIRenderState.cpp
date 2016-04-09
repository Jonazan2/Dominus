//
//  UIRenderState.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 7/4/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "UIRenderState.h"

UIRenderState::UIRenderState() :
units( 0 ) {

}

UIRenderState::~UIRenderState() {

}

void UIRenderState::init() {
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
    
    shaderProgram->registerUnitform( mvpUniformKey );
    shaderProgram->registerUnitform( textureDataUniformKey );
    shaderProgram->registerAttribute( positionAttributeKey );
    shaderProgram->registerAttribute( textureAttributeKey );
    
    glGenVertexArrays ( 1, &vao );
    glBindVertexArray( vao );
    
    uiVerticesBufer->bind();
    glVertexAttribPointer ( shaderProgram->getAttribute( positionAttributeKey ),
                           3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray( shaderProgram->getAttribute(positionAttributeKey) );
    uiUvsBuffer->bind();
    
    uiUvsBuffer->bind();
    glVertexAttribPointer( shaderProgram->getAttribute( textureAttributeKey ),
                          2, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( shaderProgram->getAttribute( textureAttributeKey ) );
    uiUvsBuffer->unBind();
    
    glBindVertexArray( 0 );
}

void UIRenderState::updateCamera( glm::mat4 camera ) {

}

void UIRenderState::updateProjection( glm::mat4 projection ) {

}

void UIRenderState::updateLightSource( glm::vec3 light ) {

}

void UIRenderState::load( std::shared_ptr<Node> node ) {
    glBindVertexArray ( vao );
    std::shared_ptr<Mesh> mesh = node->getMesh();
    
    uiVerticesBufer->bind();
    GLsizeiptr size = ( sizeof ( GLfloat ) * 3 ) * mesh->getVertices().size();
    uiVerticesBufer->push( (float*)&mesh->getVertices()[0], size );
    //TODO: this should be automatic...
    offsetMap[node->getID()] = units;
    units += mesh->getVertices().size();
    uiVerticesBufer->unBind();
    
    uiUvsBuffer->bind();
    size = ( sizeof ( GLfloat ) * 2 ) * mesh->getUvs().size();
    uiUvsBuffer->push( (float*)&mesh->getUvs()[0], size );
    uiUvsBuffer->unBind();
    
    if( mesh->getTexture() != nullptr ) {
        mesh->getTexture()->bind();
        mesh->getTexture()->push();
        mesh->getTexture()->unbind();
    }
    
    glBindVertexArray ( 0 );
}

void UIRenderState::draw( std::shared_ptr<Node> node ) {
    glm::mat4 orthoMatrix = glm::ortho( 0.0, 640.0, 480.0, 0.0 );
    shaderProgram->useProgram();
    glBindVertexArray ( vao );
    
    if( node->getMesh()->getTexture() != nullptr ) {
        node->getMesh()->getTexture()->bind();
        glUniform1i( shaderProgram->getUniform( textureDataUniformKey ) , 0 );
    }
    
    glm::mat4 MVPMatrix = orthoMatrix;
    glUniformMatrix4fv( shaderProgram->getUniform( mvpUniformKey ),
                       1, GL_FALSE, &MVPMatrix[0][0] );
    
    glDrawArrays ( GL_TRIANGLES,
                  (int)offsetMap[node->getID()],
                  (int)node->getMesh()->getVertices().size() );
    if( node->getMesh()->getTexture() != nullptr ) {
        node->getMesh()->getTexture()->unbind();
    }

    
    glBindVertexArray( 0 );
    shaderProgram->closeProgram();
}
