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

//TODO: Check if the gpu memory allocation can fail and handle error.
void Buffer::reserve( GLsizeiptr size ) {
    if( binded ){
        this->size = size;
        buffer->reserve( size );
    } else {
        throw UnbindException( bufferUID );
    }
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
    if( !add( vector, vectorSize ) ) {
        requestBufferMemory( vector, vectorSize );
        add( vector, vectorSize );
    }
}

bool Buffer::add( float* vector, GLsizeiptr vectorSize ) {
    if ( binded ) {
        GLsizeiptr totalSize = position + vectorSize;
        if( totalSize <= this->size ) {
            buffer->push( vector, position, vectorSize );
            position += vectorSize;
            return true;
        } else {
            return false;
        }
    } else {
        throw UnbindException( bufferUID );
    }
}

void Buffer::requestBufferMemory( float *vector, GLsizeiptr vectorSize ) {
    GLsizeiptr totalSize = position + vectorSize;
    //buffer not defined
    if( size == 0 ){
        reserve( totalSize );
    } else if( !isEmpty() ) {  //buffer defined and with saved content
        //save gpu buffer state
        float* savedBuffer =
            (float*)buffer->getBufferSubData( 0, (int)position );
        reserve( totalSize );
        //restore gpu buffer state
        buffer->push( savedBuffer, 0, position );
        delete savedBuffer;
    } else {
        buffer->reserve( totalSize );
    }

}

GLsizeiptr Buffer::getSize() {
    return size;
}

GLsizeiptr Buffer::getPosition() {
    return position;
}

bool Buffer::isEmpty() const {
    return position == 0;
}