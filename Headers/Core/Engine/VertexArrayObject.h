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
    /* Maps and enables the given attribute */
    void mapAttribute( int attribute, int size, GLenum type,
                       GLboolean normalized, GLsizei stride,
                       const GLvoid *offset );
    void mapUniformMatrix4fv( GLint uniform, GLsizei count,
                              GLboolean transpose, const GLfloat *value );
    void mapUniformMatrix3fv( GLint uniform, GLsizei count,
                              GLboolean transpose, const GLfloat *value );
    void mapUniform3fv( GLint uniform, GLsizei count, const GLfloat *value );
    void mapUniform1i( GLint uniform, GLint v0 );
private:
    GLuint uid;
    bool binded;
};

#endif /* VertexArrayObject_h */

