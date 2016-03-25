//
//  Buffer.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 23/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Buffer.h"

Buffer::Buffer( GpuBuffer* buffer )
: size( 0 ), position( 0 ), buffer( buffer ) {
    bufferUID = buffer->genBuffer();
}

Buffer::~Buffer() { }

void Buffer::reserve( GLsizeiptr size ) {
    this->size = size;
    bind();
    buffer->reserve( size );
    unBind();
}

void Buffer::bind() {
    buffer->bind( bufferUID );
    binded = true;
}

void Buffer::unBind() {
    buffer->unBind();
    binded = false;
}

void Buffer::clear() {
    if ( binded ) {
        size = 0;
        buffer->clear( size );
    } else {
        throw new UnbindException( bufferUID );
    }
}

void Buffer::push( float* vector, GLsizeiptr vectorSize ) {
    if ( binded ) {
        GLsizeiptr totalSize = position + vectorSize;
        if( totalSize <= this->size ) {
            buffer->push( vector, position, vectorSize );
            position += vectorSize;
        } else {
            //Empty buffer
            if( isEmpty() ){
                buffer->reserve( vectorSize );
                buffer->push( vector, 0, vectorSize );
            } else if( position != 0 ) {
                //save gpu buffer state
                float* savedbuffer =
                    (float*)buffer->getBufferSubData( 0, (int)position );
                buffer->reserve( totalSize );
                //restored gpu buffer state
                buffer->push( savedbuffer, 0, position );
                buffer->push( vector, position, vectorSize );
                delete savedbuffer;
            }
            position = totalSize;
            size = totalSize;
        }
    } else {
        throw UnbindException( bufferUID );
    }
}

GLsizeiptr Buffer::getSize() {
    return size;
}

GLsizeiptr Buffer::getPosition() {
    return position;
}

bool Buffer::isEmpty() {
    return size == 0;
}