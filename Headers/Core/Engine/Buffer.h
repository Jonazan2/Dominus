//
//  Buffer.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 23/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef Buffer_h
#define Buffer_h

#include "GpuBuffer.h"
#include "UnbindException.h"
#include <glm/glm.hpp>

class Buffer {
public:
    Buffer( GpuBuffer* buffer );
    ~Buffer();
    
    void push( float* vector, GLsizeiptr vectorSize );
    void bind();
    void unBind();
    void clear();
    void reserve( GLsizeiptr size );
    bool isEmpty();
    
    GLsizeiptr getSize();
    GLsizeiptr getPosition();
private:
    GpuBuffer* buffer;
    
    GLuint bufferUID;
    GLsizeiptr position;
    GLsizeiptr size;
    bool binded;
};

#endif /* Buffer_h */
