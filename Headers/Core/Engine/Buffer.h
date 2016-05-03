#ifndef __Dominus_Buffer_h__
#define __Dominus_Buffer_h__

#include <glm/glm.hpp>
#include <memory>
#include "GpuBuffer.h"

class Buffer {
public:
    Buffer( std::unique_ptr< GpuBuffer > buffer );
    ~Buffer();
    
    void requestBufferMemory( float* vector, GLsizeiptr vectorSize );
    /**
     * Adds the given vector to the buffer memory if the total size doesn't
     * exceeds the buffer limits
     * return: true if the request succeded false otherwise
     **/
    bool add( float* vector, GLsizeiptr vectorSize );
    /**
     * Push the given vector to the buffer memory, if the total size
     * exceeds the buffer limits will request for more memory
     **/
    void push( float* vector, GLsizeiptr vectorSize );
    void bind();
    void unBind();
    void clear();
    void reserve( GLsizeiptr size );
    bool isEmpty() const;
    
    GLsizeiptr getSize();
    GLsizeiptr getPosition();
private:
    std::unique_ptr< GpuBuffer > buffer;
    GLuint bufferUID;
    GLsizeiptr position;
    GLsizeiptr size;
    bool binded;
};

#endif /* _BUFFER_H_ */
