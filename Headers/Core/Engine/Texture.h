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

class Texture {
public:
    Texture( TextureLoader* loader );
    ~Texture( );
    
    GLubyte* getImageData();
    int getWidth();
    int getHeight();
    void setWidth( int width );
    void setHeight( int height );
    void loadTexture( std::string file );
    GLuint textureUID;
    
private:
    bool loadPngImage( const char *name,
                      int &outWidth, int &outHeight,bool &outHasAlpha,
                      GLubyte **outData );
    GLubyte* image;
    int width;
    int height;
    bool hasAlpha;
    TextureLoader* loader;
};

#endif /* Texture_h */
