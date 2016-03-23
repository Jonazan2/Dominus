//
//  Buffer.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 23/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "BufferVec3.h"

BufferVec3::BufferVec3() : size( 0 ), maxSize( 0 ) {

}

BufferVec3::~BufferVec3() {

}

void BufferVec3::reserve( GLuint units ) {
    updateSize( units );
    //Wrap it in a opengl container and use it as a mock class
    glGenBuffers( 1, &bufferUID );
    bind();
    glBufferData( GL_ARRAY_BUFFER, maxSize, NULL, GL_STATIC_DRAW );
    unBind();
}

void BufferVec3::updateSize( GLuint units ) {
    maxSize = ( sizeof ( GLfloat ) * 3 ) * units;
}

void BufferVec3::bind() {
    glBindBuffer(  GL_ARRAY_BUFFER, bufferUID );
    binded = true;
}

void BufferVec3::unBind() {
    glBindBuffer(  GL_ARRAY_BUFFER, 0 );
    binded = false;
}

void BufferVec3::clear() {
    if ( binded ) {
        size = 0;
        glBufferData( GL_ARRAY_BUFFER, maxSize, NULL, GL_STATIC_DRAW );
    } else {
        //TODO: throw exception
    }
}

void BufferVec3::push( std::vector< glm::vec3 > vector ) {
    if ( binded ) {
        GLsizeiptr vecSize = ( sizeof ( GLfloat ) * 3 ) * vector.size();
        GLsizeiptr totalSize = size + vecSize;
        if( totalSize <= this->maxSize ) {
            glBufferSubData( GL_ARRAY_BUFFER , size, vecSize, &vector[0] );
            size += vecSize;
        } else {
            //TODO: reserve more memory
        }
    } else {
        //TODO: throw exception
    }
}

GLsizeiptr BufferVec3::getSize() {
    return size;
}