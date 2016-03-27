//
//  GpuTexture.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 26/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef GpuTexture_h
#define GpuTexture_h

#include <OpenGL/OpenGL.h>

class GpuTexture {
public:
    virtual void push( int width, int height, bool alpha, GLubyte* data ) = 0;
    virtual void bind( GLuint textureUID ) = 0;
    virtual void unbind( ) = 0;
    virtual GLuint genTexture() = 0;
};

#endif /* GpuTexture_h */
