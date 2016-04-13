//
//  VertexArrayObject.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 11/4/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "VertexArrayObject.h"
#include "Exception.h"

VertexArrayObject::VertexArrayObject() : binded( false ) {
    glGenVertexArrays ( 1, &uid );
}

VertexArrayObject::~VertexArrayObject() {

}

void VertexArrayObject::bind() {
    glBindVertexArray ( uid );
    binded = true;
}

void VertexArrayObject::unBind() {
    glBindVertexArray( 0 );
    binded = false;
}

void VertexArrayObject::mapAttribute( int attribute, int size,
                                      GLenum type, GLboolean normalized,
                                      GLsizei stride, const GLvoid *offset ) {
    if( binded ){
        glVertexAttribPointer( attribute, size, type, normalized, stride, offset );
        glEnableVertexAttribArray( attribute );
    } else {
        throw UnbindException( attribute );
    }
}