//
//  GPUBuffer.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 24/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef GPUBuffer_h
#define GPUBuffer_h

#include <OpenGL/gl3.h>

class GpuBuffer {
public:
    virtual void push( float* vector,
                      GLsizeiptr offset,
                      GLsizeiptr vectorSize ) = 0;
    virtual void bind( GLuint bufferUID ) = 0;
    virtual void unBind() = 0;
    virtual void clear( GLsizeiptr size ) = 0;
    virtual void reserve( GLsizeiptr size ) = 0;
    virtual GLuint genBuffer( ) = 0;
    virtual void* mapBuffer( GLuint bufferUID ) = 0;
};

#endif /* GPUBuffer_h */
