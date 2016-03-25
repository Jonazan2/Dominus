//
//  MockGPUBuffer.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 24/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef MockGPUBuffer_h
#define MockGPUBuffer_h

#include "gmock/gmock.h"
#include "GpuBuffer.h"

class MockGPUBuffer : public  GpuBuffer {
public:
    MOCK_METHOD3( push, void( float* vector,
                            GLsizeiptr offset,
                            GLsizeiptr vectorSize )) ;
    MOCK_METHOD1( bind, void( GLuint bufferUID ) );
    MOCK_METHOD0( unBind, void( ) );
    MOCK_METHOD1( clear, void( GLsizeiptr size ) );
    MOCK_METHOD1( reserve, void( GLsizeiptr size ) );
    MOCK_METHOD0( genBuffer, GLuint( ) );
    MOCK_METHOD1( mapBuffer, void*( GLuint bufferUID ) );
    MOCK_METHOD1( unMapBuffer, void( GLuint bufferUID ) );
    MOCK_METHOD2( getBufferSubData, void*( int offset, int size ) );
    MOCK_METHOD1( getBufferSize, void( int* ) );
};

#endif /* MockGPUBuffer_h */