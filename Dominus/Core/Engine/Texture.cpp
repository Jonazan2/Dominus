//
//  Texture.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 25/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Texture.h"
#include "Exception.h"

Texture::Texture( )
: width(0), height(0), hasAlpha( false ),
image( nullptr ), loader( nullptr ),
gpuTexture( nullptr ), binded( false ), loaded( false )
{ }

Texture::Texture( GpuTexture* gpuTexture )
: Texture() {
    this->gpuTexture = gpuTexture;
    textureUID = gpuTexture->genTexture();
}

Texture::Texture( GpuTexture* gpuTexture, TextureLoader* loader )
: Texture( gpuTexture ) {
    this->loader = loader;
}

Texture::~Texture() {

}

void Texture::load( std::string file ) {
    loader->loadTexture( file.c_str(), width, height, hasAlpha, &image );
}

void Texture::push() {
    //TODO: check if the image data is already loaded
    if( binded ) {
        gpuTexture->push( width, height, hasAlpha, image );
    } else {
        throw UnbindException( textureUID );
    }
}

void Texture::bind() {
    gpuTexture->bind( textureUID );
}

void Texture::unbind() {
    gpuTexture->unbind();
}

GLuint Texture::getUID() {
    return textureUID;
}

GLubyte* Texture::getImageData( ) {
    return image;
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}