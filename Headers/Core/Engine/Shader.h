//
//  Shader.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 29/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef Shader_h
#define Shader_h

#include <OpenGL/gl3.h>
#include <string>
#include <vector>

class Shader {
public:
    Shader( std::string file, GLenum type );
    ~Shader( );
    
    void compile();
    const GLuint getUID();
private:
    bool compileShader( GLuint shader );
    GLuint uid;
    std::string filePath;
    const char * data;
    GLenum type;
};

#endif /* Shader_h */
