//
//  BufferVec2.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 23/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "BufferVec2.h"

BufferVec2::BufferVec2() : offset( 0 ), size( 0 ) {

}

BufferVec2::~BufferVec2() {
    
}

void BufferVec2::reserve( GLuint units ) {
    size = ( sizeof ( GLfloat ) * 2 ) * units;
    glGenBuffers( 1, &bufferUID );
    bind();
    glBufferData( GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW );
}

void BufferVec2::bind() {
    glBindBuffer( GL_ARRAY_BUFFER, bufferUID );
}

void BufferVec2::clear() {
    bind();
    offset = 0;
    glBufferData( GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW );
}

void BufferVec2::push( std::vector< glm::vec2 > vector ) {
    bind();
    GLsizeiptr vecSize = ( sizeof ( GLfloat ) * 2 ) * vector.size();
    GLsizeiptr position = offset + vecSize;
    if( position < this->size ) {
        glBufferSubData( GL_ARRAY_BUFFER , offset, vecSize, &vector[0] );
        offset += vecSize;
    }else {
        //TODO: reserve more memory
    }
}