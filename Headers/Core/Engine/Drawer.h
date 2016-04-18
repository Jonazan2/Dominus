//
//  Drawer.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 18/4/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef Drawer_h
#define Drawer_h

#include "VertexArrayObject.h"
#include "ShaderProgram.h"

class Drawer {
public:
    Drawer( std::shared_ptr<VertexArrayObject> vao,
            std::shared_ptr<ShaderProgram> program );
    ~Drawer();
    
    void draw( GLenum mode, GLint first, GLsizei count );
    
private:
    std::shared_ptr<VertexArrayObject> vao;
    std::shared_ptr<ShaderProgram> program;
};

#endif /* Drawer_h */
