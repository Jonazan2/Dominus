//
//  Header.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 25/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef Texture_h
#define Texture_h

#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include <iostream>
#include <OpenGL/OpenGL.h>
class Texture {
public:
    Texture( std::string filePath );
    ~Texture();
    
    GLubyte* getImageData();
    int getWidth();
    int getHeight();
private:
    bool loadPngImage( const char *name, int &outWidth, int &outHeight,
                      bool &outHasAlpha, GLubyte **outData );
    unsigned char* image;
    int width;
    int height;
    bool hasAlpha;
    std::string filePath;
};

#endif /* Texture_h */