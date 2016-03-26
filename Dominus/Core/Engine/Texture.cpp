//
//  Texture.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 25/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Texture.h"

Texture::Texture( TextureLoader* loader )
: width(0), height(0), hasAlpha( false ),
image( nullptr ), textureUID( -1 ), loader( loader )
{ }

Texture::~Texture() {

}

void Texture::loadTexture( std::string file ) {
    loader->loadTexture( file.c_str(), width, height, hasAlpha, &image );
}

GLubyte* Texture::getImageData() {
    return image;
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}