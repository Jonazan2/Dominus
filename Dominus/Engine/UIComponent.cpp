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

std::vector<glm::vec3> UIComponent::getVertices() const {
    return vertices;
}

GLsizeiptr UIComponent::getVertexSize() const {
    return ( sizeof ( GLfloat ) * 3 ) * vertices.size();
}

void UIComponent::setTexture( Texture* texture ) {
    this->texture = texture;
    glm::vec2 topLeft = glm::vec2( 0, 0 );
    glm::vec2 topRight = glm::vec2( texture->getWidth(), 0 );
    glm::vec2 bottomLeft = glm::vec2( 0, texture->getHeight() );
    glm::vec2 bottomRight = glm::vec2( texture->getWidth(),
                                           texture->getHeight() );
    vertices.push_back( glm::vec3( topLeft, 0 ) );
    vertices.push_back( glm::vec3( bottomLeft, 0 ) );
    vertices.push_back( glm::vec3( topRight, 0 ) );
    vertices.push_back( glm::vec3( bottomLeft, 0 ) );
    vertices.push_back( glm::vec3( topRight, 0 ) );
    vertices.push_back( glm::vec3( bottomRight, 0 ) );
    
    glm::vec2 uvTopLeft = glm::vec2( 0, 0 );
    glm::vec2 uvTopRight = glm::vec2( 1, 0 );
    glm::vec2 uvBottomLeft = glm::vec2( 0, 1 );
    glm::vec2 uvBottomRight = glm::vec2( 1, 1 );
    
    uvs.push_back(uvBottomRight );
    uvs.push_back( uvTopRight );
    uvs.push_back( uvBottomLeft );
    uvs.push_back( uvTopRight );
    uvs.push_back( uvBottomLeft );
    uvs.push_back( uvTopLeft );
}

Texture* UIComponent::getTexture() const {
    return texture;
}

std::vector<glm::vec2> UIComponent::getUvs() const {
    return uvs;
}

GLsizeiptr UIComponent::getUvsSize() const {
    return ( sizeof ( GLfloat ) * 2 ) * uvs.size();
}
