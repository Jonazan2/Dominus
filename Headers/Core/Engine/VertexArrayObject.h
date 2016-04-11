//
//  VertexArrayObject.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 11/4/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef VertexArrayObject_h
#define VertexArrayObject_h

#include <OpenGL/gl3.h>

class VertexArrayObject {
public:
    VertexArrayObject();
    ~VertexArrayObject();
    
    void bind();
    void unBind();
    void mapAttribute( int attribute, int size, GLenum type,
                       GLboolean normalized, GLsizei stride,
                       const GLvoid *offset );
private:
    GLuint uid;
    bool binded;
};

#endif /* VertexArrayObject_h */
