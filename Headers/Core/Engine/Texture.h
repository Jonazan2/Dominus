//
//  Header.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 25/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef Texture_h
#define Texture_h

#include <OpenGL/OpenGL.h>
#include <string>
#include "TextureLoader.h"
#include "GpuTexture.h"

class Texture {
public:
    Texture( );
    Texture( GpuTexture* gpuTexture, TextureLoader* loader );
    Texture( GpuTexture* gpuTexture );
    ~Texture( );
    
    GLubyte* getImageData();
    int getWidth();
    int getHeight();
    void setWidth( int width );
    void setHeight( int height );
    void load( std::string file );
    void push( );
    void bind( );
    void unbind();
    GLuint getUID();
private:
    bool loadPngImage( const char *name,
                      int &outWidth, int &outHeight,bool &outHasAlpha,
                      GLubyte **outData );
    GLubyte* image;
    int width;
    int height;
    bool hasAlpha;
    TextureLoader* loader;
    GpuTexture* gpuTexture;
    bool binded;
    bool loaded;
    GLuint textureUID;
};

#endif /* Texture_h */
