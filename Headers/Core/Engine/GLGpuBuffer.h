//
//  GLGpuBuffer.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 24/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef GLGpuBuffer_h
#define GLGpuBuffer_h

#include "GpuBuffer.h"

class GLGpuBuffer : public GpuBuffer {
public:
    GLGpuBuffer();
    ~GLGpuBuffer();
    
    void push( float* vector, GLsizeiptr offset, GLsizeiptr vectorSize );
    void bind( GLuint bufferUID );
    void unBind();
    void clear( GLsizeiptr size );
    void reserve( GLsizeiptr size );
    GLuint genBuffer( );
    void* mapBuffer( GLuint bufferUID );
};

#endif /* GLGpuBuffer_h */
