#include "Texture.h"

Texture::Texture( )
    : width(0), height(0), hasAlpha( false ),
    image( nullptr ), loader( nullptr ),
    gpuTexture( nullptr ), binded( false ), loaded( false ) {
}

Texture::Texture( std::unique_ptr<GpuTexture> gpuTexture )
: Texture() {
    this->gpuTexture = std::move(gpuTexture);
    textureUID = this->gpuTexture->genTexture();
}

Texture::Texture( std::unique_ptr< GpuTexture > gpuTexture,
                  std::unique_ptr< TextureLoader > loader )
    : Texture( std::move(gpuTexture) ) {
    this->loader = std::move( loader );
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

Texture::~Texture() {
    delete image;
}