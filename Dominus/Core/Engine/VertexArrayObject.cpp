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

int VertexArrayObject::getUID() {
    return uid;
}

void VertexArrayObject::bind() {
    glBindVertexArray ( uid );
    binded = true;
}

void VertexArrayObject::unBind() {
    glBindVertexArray( 0 );
    binded = false;
}

bool VertexArrayObject::isBinded() {
    return binded;
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

void VertexArrayObject::mapUniform1i( GLint uniform, GLint v0 ) {
    if( binded ){
        glUniform1i( uniform, v0 );
    } else {
        throw UnbindException( uniform );
    }
}

void VertexArrayObject::mapUniform3fv( GLint uniform, GLsizei count,
                                       const GLfloat *value ) {
    if( binded ){
        glUniform3fv( uniform, count, value );
    } else {
        throw UnbindException( uniform );
    }
}

void VertexArrayObject::mapUniformMatrix3fv( GLint uniform, GLsizei count,
                                             GLboolean transpose,
                                            const GLfloat *value ) {
    if( binded ){
        glUniformMatrix3fv( uniform, count, transpose, value );
    } else {
        throw UnbindException( uniform );
    }
}

void VertexArrayObject::mapUniformMatrix4fv( GLint uniform, GLsizei count,
                                             GLboolean transpose,
                                             const GLfloat *value ) {
    if( binded ){
        glUniformMatrix4fv( uniform, count, transpose, value );
    } else {
        throw UnbindException( uniform );
    }
}