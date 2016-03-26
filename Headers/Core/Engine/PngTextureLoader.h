//
//  PngTextureLoader.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 26/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef PngTextureLoader_h
#define PngTextureLoader_h

#include "TextureLoader.h"

class PngTextureLoader : public TextureLoader {
public:
    PngTextureLoader();
    ~PngTextureLoader();
    void loadTexture( const char *fileName,
                     int &outWidth, int &outHeight, bool &outHasAlpha,
                     GLubyte **outData );
};

#endif /* PngTextureLoader_h */
