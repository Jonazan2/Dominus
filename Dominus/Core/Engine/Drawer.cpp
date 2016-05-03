//
//  Drawer.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 18/4/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Drawer.h"
#include "OpenGLExceptions.h"

#include <OpenGL/gl3.h>

Drawer::Drawer( std::shared_ptr<VertexArrayObject> vao,
                std::shared_ptr<ShaderProgram> program )
: vao( vao ), program( program ) {
    
}

Drawer::~Drawer() {

}

void Drawer::draw( GLenum mode, GLint first, GLsizei count ) {
    if( vao->isBinded() ) {
        if( program->isLinked() ) {
            glDrawArrays ( mode, first, count );
        } else {
            throw UnbindException( program->getUID() );
        }
    }else {
        throw UnbindException( vao->getUID() );
    }
}