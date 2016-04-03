//
//  ShaderProgram.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 3/4/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "ShaderProgram.h"
#include "Exception.h"

ShaderProgram::ShaderProgram()
: active( false ), linked( false ) {
    uid = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {

}

void ShaderProgram::attachShader( Shader* shader ) {
    shaders.push_back( shader );
    glAttachShader( uid , shader->getUID() );
}

void ShaderProgram::linkProgram() {
    GLint isLinked = 0;
    glLinkProgram( uid );
    glGetProgramiv( uid , GL_LINK_STATUS, &isLinked );
    
    if(isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv( uid, GL_INFO_LOG_LENGTH, &maxLength );
        
        //The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog( uid, maxLength, &maxLength, &infoLog[0] );
        //The program is useless now. So delete it.
        glDeleteProgram( uid );
        throw LinkProgramException( &infoLog[0] );
    }
    linked = true;
}

void ShaderProgram::registerAttribute( std::string attributeKey ) {
    //TODO: Check if the key has been succesfully retrieved
    if( linked ) {
        attributes[ attributeKey ] = glGetAttribLocation( uid,
                                                          attributeKey.c_str() );
    }else {
        throw ProgramNotLinkedException( uid );
    }
}

void ShaderProgram::registerUnitform( std::string uniformKey ) {
    if( linked ) {
        uniforms[ uniformKey ] = glGetUniformLocation( uid,
                                                       uniformKey.c_str() );
    }else {
        throw ProgramNotLinkedException( uid );
    }
}

GLuint ShaderProgram::getAttribute( std::string attributeKey ) {
    if ( attributes.find( attributeKey ) == attributes.end() ) {
        throw UnknowAttributeException( attributeKey.c_str() );
    } else {
        return attributes[ attributeKey ];
    }
}

GLuint ShaderProgram::getUniform( std::string uniformKey ) {
    if( uniforms.find( uniformKey ) == uniforms.end() ) {
        throw UnknowAttributeException( uniformKey.c_str() );
    }else {
        return uniforms[ uniformKey ];
    }
}

void ShaderProgram::useProgram() {
    if( linked ) {
        glUseProgram( uid );
        active = true;
    } else {
        throw ProgramNotLinkedException( uid );
    }
}

void ShaderProgram::closeProgram() {
    glUseProgram( 0 );
    active = false;
}