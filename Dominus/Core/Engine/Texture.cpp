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
    std::cout << "Texture deleted\n";
}

void Texture::load( std::string file ) {
    loader->loadTexture( file.c_str(), width, height, hasAlpha, &image );
    loaded = true;
}

void Texture::push() {
    if( binded ) {
        if( width > 0 && height > 0 && image != nullptr  ) {
            gpuTexture->push( width, height, hasAlpha, image );
        } else {
            throw InvalidTextureException( textureUID, width, height );
        }
    } else {
        throw UnbindException( textureUID );
    }
}

void Texture::bind() {
    gpuTexture->bind( textureUID );
    binded = true;
}

void Texture::unbind() {
    gpuTexture->unbind();
    binded = false;
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