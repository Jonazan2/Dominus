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
    vao = std::make_shared<VertexArrayObject>( VertexArrayObject() );
}

UIRenderState::~UIRenderState() {

}

void UIRenderState::init() {
    std::shared_ptr<Shader> vertexShader =
        std::shared_ptr<Shader>( new Shader( "shaders/ui_vertex_shader.glsl",
                                        GL_VERTEX_SHADER ) );
    vertexShader->compile();
    
    std::shared_ptr<Shader> fragmentShader =
        std::shared_ptr<Shader>( new Shader( "shaders/ui_fragment_shader.glsl",
                                        GL_FRAGMENT_SHADER ) );
    fragmentShader->compile();
    
    shaderProgram->attachShader( vertexShader );
    shaderProgram->attachShader( fragmentShader );
    
    shaderProgram->linkProgram();
    
    shaderProgram->registerUnitform( mvpUniformKey );
    shaderProgram->registerUnitform( textureDataUniformKey );
    shaderProgram->registerAttribute( positionAttributeKey );
    shaderProgram->registerAttribute( textureAttributeKey );
    
    vao->bind();
    
    uiVerticesBufer->bind();
    vao->mapAttribute( shaderProgram->getAttribute( positionAttributeKey ),
                           3, GL_FLOAT, GL_FALSE, 0, NULL);
    uiUvsBuffer->bind();
    
    uiUvsBuffer->bind();
    vao->mapAttribute( shaderProgram->getAttribute( textureAttributeKey ),
                          2, GL_FLOAT, GL_FALSE, 0, NULL );
    uiUvsBuffer->unBind();
    
    vao->unBind();
}

void UIRenderState::updateCamera( glm::mat4 camera ) {

}

void UIRenderState::updateProjection( glm::mat4 projection ) {

}

void UIRenderState::updateLightSource( glm::vec3 light ) {

}

void UIRenderState::load( std::shared_ptr<Node> node ) {
    vao->bind();
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
    
    vao->unBind();
}

void UIRenderState::draw( std::shared_ptr<Node> node ) {
    glm::mat4 orthoMatrix = glm::ortho( 0.0, 640.0, 480.0, 0.0 );
    shaderProgram->useProgram();
    vao->bind();
    
    if( node->getMesh()->getTexture() != nullptr ) {
        node->getMesh()->getTexture()->bind();
        vao->mapUniform1i( shaderProgram->getUniform( textureDataUniformKey ) , 0 );
    }
    
    glm::mat4 MVPMatrix = orthoMatrix;
    vao->mapUniformMatrix4fv( shaderProgram->getUniform( mvpUniformKey ),
                       1, GL_FALSE, &MVPMatrix[0][0] );
    
    glDrawArrays ( GL_TRIANGLES,
                  (int)offsetMap[node->getID()],
                  (int)node->getMesh()->getVertices().size() );
    if( node->getMesh()->getTexture() != nullptr ) {
        node->getMesh()->getTexture()->unbind();
    }

    
    vao->unBind();
    shaderProgram->releaseProgram();
}
