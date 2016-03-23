//
//  BufferVec2.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 23/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef BufferVec2_h
#define BufferVec2_h

#include <vector>
#include <glm/glm.hpp>
#include <OpenGL/gl3.h>

class BufferVec2 {
public:
    BufferVec2( );
    ~BufferVec2();
    void push( std::vector< glm::vec2 > vector );
    void bind();
    void clear();
    void reserve( GLuint units );
private:
    GLuint offset;
    GLuint bufferUID;
    GLsizeiptr size;
};

#endif /* BufferVec2_h */
