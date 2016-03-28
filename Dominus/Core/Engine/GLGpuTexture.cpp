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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    
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
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 data );
}

void GLGpuTexture::bind( GLuint textureUID ) {
    glBindTexture( GL_TEXTURE_2D , textureUID );
    glActiveTexture( GL_TEXTURE0 );
}

void GLGpuTexture::unbind() {
    glBindTexture( GL_TEXTURE_2D , 0 );
}