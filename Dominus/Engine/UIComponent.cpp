//
//  UIComponent.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 14/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "UIComponent.h"

UIComponent::UIComponent() : texture( nullptr ), x( 0 ), y( 0 ){
    
}

UIComponent::~UIComponent() {

}

std::vector<glm::vec3 *> UIComponent::getVertices() const {
    return vertices;
}

GLsizeiptr UIComponent::getVertexSize() const {
    return ( sizeof ( GLfloat ) * 3 ) * vertices.size();
}

void UIComponent::setTexture( Texture* texture ) {
    this->texture = texture;
    glm::vec2* topLeft = new glm::vec2( 0, 0 );
    glm::vec2* topRight = new glm::vec2( texture->getWidth(), 0 );
    glm::vec2* bottomLeft = new glm::vec2( 0, texture->getHeight() );
    glm::vec2* bottomRight = new glm::vec2( texture->getWidth(),
                                           texture->getHeight() );
    vertices.push_back( new glm::vec3( *topLeft, 0 ) );
    vertices.push_back( new glm::vec3( *bottomLeft, 0 ) );
    vertices.push_back( new glm::vec3( *topRight, 0 ) );
    vertices.push_back( new glm::vec3( *bottomLeft, 0 ) );
    vertices.push_back( new glm::vec3( *topRight, 0 ) );
    vertices.push_back( new glm::vec3( *bottomRight, 0 ) );
    
    uvs.push_back( topLeft );
    uvs.push_back( bottomLeft );
    uvs.push_back( topRight );
    uvs.push_back( bottomLeft );
    uvs.push_back( topRight );
    uvs.push_back( bottomRight );
}

Texture* UIComponent::getTexture() const {
    return texture;
}

std::vector<glm::vec2 *> UIComponent::getUvs() const {
    return uvs;
}

GLsizeiptr UIComponent::getUvsSize() const {
    return ( sizeof ( GLfloat ) * 2 ) * uvs.size();
}
