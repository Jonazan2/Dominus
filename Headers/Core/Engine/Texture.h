#ifndef __Dominus_Texture_h__
#define __Dominus_Texture_h__

#include <string>

#include <OpenGL/OpenGL.h>

#include "TextureLoader.h"
#include "GpuTexture.h"
#include "Exception.h"
#include "MemoryUtils.h"

class Texture {
public:
    Texture( std::unique_ptr< GpuTexture >  gpuTexture,
             std::unique_ptr< TextureLoader > loader );
    Texture( std::unique_ptr< GpuTexture > gpuTexture );
    ~Texture();
    
    GLubyte* getImageData();
    int getWidth();
    int getHeight();
    void setWidth( int width );
    void setHeight( int height );
    void load( std::string file );
    void push();
    void bind();
    void unbind();
    GLuint getUID();
private:
    Texture( );
    bool loadPngImage( const char *name,
                      int &outWidth, int &outHeight,bool &outHasAlpha,
                      GLubyte **outData );
    GLubyte* image;
    int width;
    int height;
    bool hasAlpha;
    std::unique_ptr< TextureLoader > loader;
    std::unique_ptr< GpuTexture > gpuTexture;
    bool binded;
    bool loaded;
    GLuint textureUID;
};

#endif /* _TEXTURE_H_ */
