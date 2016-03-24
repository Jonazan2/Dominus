//
//  Buffer.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 23/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef Buffer_h
#define Buffer_h

#include <vector>
#include <glm/glm.hpp>
#include <OpenGL/gl3.h>

class Buffer {
public:
    Buffer();
    ~Buffer();
    
    void push( float* vector, GLsizeiptr vectorSize );
    void bind();
    void unBind();
    void clear();
    void reserve( GLsizeiptr size );
    
    GLsizeiptr getSize();
private:
    GLuint bufferUID;
    GLsizeiptr maxSize;
    GLsizeiptr size;
    bool binded;
};

#endif /* Buffer_h */
