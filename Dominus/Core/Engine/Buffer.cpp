//
//  Buffer.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 23/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Buffer.h"

Buffer::Buffer() : size( 0 ), maxSize( 0 ) {

}

Buffer::~Buffer() {

}

void Buffer::reserve( GLsizeiptr size ) {
    this->size = size;
    //Wrap it in a opengl container and use it as a mock class
    glGenBuffers( 1, &bufferUID );
    bind();
    glBufferData( GL_ARRAY_BUFFER, maxSize, NULL, GL_STATIC_DRAW );
    unBind();
}

void Buffer::bind() {
    glBindBuffer(  GL_ARRAY_BUFFER, bufferUID );
    binded = true;
}

void Buffer::unBind() {
    glBindBuffer(  GL_ARRAY_BUFFER, 0 );
    binded = false;
}

void Buffer::clear() {
    if ( binded ) {
        size = 0;
        glBufferData( GL_ARRAY_BUFFER, maxSize, NULL, GL_STATIC_DRAW );
    } else {
        //TODO: throw exception
    }
}

void Buffer::push( float* vector, GLsizeiptr vectorSize ) {
    if ( binded ) {
        GLsizeiptr totalSize = size + vectorSize;
        if( totalSize <= this->maxSize ) {
            glBufferSubData( GL_ARRAY_BUFFER , size, vectorSize, vector );
            size += vectorSize;
        } else {
            //TODO: reserve more memory
        }
    } else {
        //TODO: throw exception
    }
}

GLsizeiptr Buffer::getSize() {
    return size;
}