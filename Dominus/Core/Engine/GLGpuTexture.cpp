//
//  GLGpuTexture.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 26/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "GLGpuTexture.h"
#include <OpenGL/gl3.h>

GLGpuTexture::GLGpuTexture() {
    
}

GLGpuTexture::~GLGpuTexture() {

}

GLuint GLGpuTexture::genTexture() {
    GLuint textureUID;
    glGenTextures( 1, &textureUID );
    return textureUID;
}

void GLGpuTexture::push( int width, int height, bool alpha, GLubyte *data ) {
    // Set the texture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    GLint format;
    if ( alpha ) {
        format = GL_RGBA;
    }else {
        format = GL_RGB;
    }
    // Load and generate the texture
    glTexImage2D( GL_TEXTURE_2D,
                 0,
                 format,
                 width,
                 height,
                 0,
                 format,
                 GL_UNSIGNED_BYTE,
                 data );
}

void GLGpuTexture::bind( GLuint textureUID ) {
    glBindTexture( GL_TEXTURE_2D , textureUID );
}

void GLGpuTexture::unbind() {
    glBindTexture( GL_TEXTURE_2D , 0 );
}