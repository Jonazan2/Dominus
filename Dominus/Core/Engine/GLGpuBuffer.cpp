//
//  GLGpuBuffer.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 24/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "GLGpuBuffer.h"

GLGpuBuffer::GLGpuBuffer() {
    
}

GLGpuBuffer::~GLGpuBuffer() {
    
}

GLuint GLGpuBuffer::genBuffer() {
    GLuint bufferUID;
    glGenBuffers( 1, &bufferUID );
    return bufferUID;
}

void GLGpuBuffer::reserve( GLsizeiptr size ) {
    glBufferData( GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW );
}

void* GLGpuBuffer::mapBuffer( GLuint bufferUID ) {
    return glMapBuffer( GL_ARRAY_BUFFER , GL_READ_ONLY );
}

void GLGpuBuffer::unMapBuffer( GLuint bufferUID ) {
    glUnmapBuffer( GL_ARRAY_BUFFER );
}

void GLGpuBuffer::bind( GLuint bufferUID ) {
    glBindBuffer(  GL_ARRAY_BUFFER, bufferUID );
}

void GLGpuBuffer::unBind() {
    glBindBuffer(  GL_ARRAY_BUFFER, 0 );
}

void GLGpuBuffer::clear( GLsizeiptr size ) {
    glBufferData( GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW );
}

void GLGpuBuffer::push( float* vector,
                       GLsizeiptr offset ,GLsizeiptr vectorSize ) {
    glBufferSubData( GL_ARRAY_BUFFER , offset, vectorSize, vector );
}

void GLGpuBuffer::getBufferSize( int* size ) {
    glGetBufferParameteriv( GL_ARRAY_BUFFER, GL_BUFFER_SIZE, size );
}

void* GLGpuBuffer::getBufferSubData( int offset, int size ) {
    float* vector = new float[size];
    glGetBufferSubData( GL_ARRAY_BUFFER, offset, size, vector );
    return vector;
}
