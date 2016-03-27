//
//  GLGpuTexture.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 26/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef GLGpuTexture_h
#define GLGpuTexture_h

#include "GpuTexture.h"

class GLGpuTexture : public GpuTexture {
public:
    GLGpuTexture();
    ~GLGpuTexture();
    
    GLuint genTexture( );
    void push( int width, int height, bool alpha, GLubyte* data );
    void bind( GLuint textureUID );
    void unbind( );
};

#endif /* GLGpuTexture_h */
