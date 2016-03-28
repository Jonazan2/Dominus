//
//  TextureLoader.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 26/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef TextureLoader_h
#define TextureLoader_h

#include<OpenGL/gl3.h>

class TextureLoader {
public:
    virtual void loadTexture( const char *fileName,
                             int &outWidth, int &outHeight, bool &outHasAlpha,
                             GLubyte **outData ) = 0;
};

#endif /* TextureLoader_h */
