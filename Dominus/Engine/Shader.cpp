//
//  Shader.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 29/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Shader.h"
#include "Log.hpp"
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>

Shader::Shader( std::string file, GLenum type )
                                                :   filePath( file ),
                                                    type( type ) {

}

Shader::~Shader( ) {

}

const GLuint Shader::getUID() {
    return uid;
}

bool Shader::compile() {
    uid = glCreateShader ( type );
    std::ifstream file( filePath );
    std::stringstream buffer;
    buffer << file.rdbuf();
    const std::string& tmp = buffer.str();
    data = tmp.c_str();
    glShaderSource ( uid, 1, &data, NULL );
    return compileShader( uid );
}

bool Shader::compileShader(GLuint shader){
    glCompileShader(shader);
    
    GLint isCompiled = 0;
    glGetShaderiv( shader, GL_COMPILE_STATUS, &isCompiled );
    if( isCompiled == GL_FALSE ) {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        
        std::vector<GLchar> errorLog( maxLength );
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
        Log::getInstance().e(&errorLog[0]);
        return false;
    }
    return true;
}