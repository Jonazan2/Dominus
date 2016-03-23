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

class BufferVec3 {
public:
    BufferVec3();
    ~BufferVec3();
    
    void push( std::vector< glm::vec3 > vector );
    void bind();
    void unBind();
    void clear();
    void reserve( GLuint units );
    void updateSize( GLuint units );
    
    GLsizeiptr getSize();
private:
    GLuint bufferUID;
    GLsizeiptr maxSize;
    GLsizeiptr size;
    bool binded;
};

#endif /* Buffer_h */
