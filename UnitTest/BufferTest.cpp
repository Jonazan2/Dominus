//
//  BufferTest.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 23/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "MockGPUBuffer.h"
#include "gtest/gtest.h"
#include "Buffer.h"
#include "MemoryUtils.h"
#include "OpenGLExceptions.h"

using ::testing::Return;

class BufferTest : public ::testing::Test
{
public:
    
    BufferTest() {
        buffer = new Buffer( make_unique< MockGPUBuffer >() );
    }
    
    virtual void SetUp() {
        //EXPECT_CALL( mockGpuBuffer, genBuffer() ).WillOnce(testing::Return( 1 ) );
        buffer->bind();
    }
    
    virtual void TearDown() {
        MockGPUBuffer mockGpuBuffer;
        buffer = new Buffer( make_unique< MockGPUBuffer >() );
    }
    
    std::unique_ptr<GpuBuffer> mockGpuBuffer;
    Buffer* buffer;
};

TEST_F( BufferTest, UnbindedBufferAddVector ) {
    buffer->unBind();
    GLsizeiptr size = 32;
    float* vector = nullptr;
    try {
        buffer->add( vector, size );
    } catch ( const UnbindException &e ) {
        ASSERT_EQ( 0, buffer->getSize() );
    }
}

TEST_F( BufferTest, EmptyBufferAddVector ) {
    buffer->reserve( 128 );
    GLsizeiptr size = 32;
    float* vector = nullptr;
    
    buffer->push( vector, size );
    ASSERT_EQ( 32, buffer->getPosition() );
    ASSERT_EQ( 128, buffer->getSize() );
}

TEST_F( BufferTest, EmptyBufferAddVectorOverflow ) {
    buffer->reserve( 128 );
    GLsizeiptr size = 256;
    float* vector = nullptr;
    
    bool added = buffer->add( vector, size );
    ASSERT_EQ( false, added );
    ASSERT_EQ( 128, buffer->getSize() );
}

TEST_F( BufferTest, EmptyBufferAddEqualVector ) {
    buffer->reserve( 128 );
    
    GLsizeiptr size = 128;
    float* vector = nullptr;
    
    bool added = buffer->add( vector, size );
    ASSERT_EQ( true , added );
    ASSERT_EQ( 128, buffer->getPosition() );
    ASSERT_EQ( 128, buffer->getSize() );
}

TEST_F( BufferTest, FilledBufferAddVector ) {
    buffer->reserve( 128 );
    
    GLsizeiptr position = 64;
    float* vector = nullptr;
    bool added = buffer->add( vector, position );
    ASSERT_EQ( true , added );
    ASSERT_EQ( 64, buffer->getPosition() );
    ASSERT_EQ( 128, buffer->getSize() );
    
    GLsizeiptr size = 32;
    added = buffer->add( vector, size );
    ASSERT_EQ( true , added );
    ASSERT_EQ( 96, buffer->getPosition() );
    ASSERT_EQ( 128, buffer->getSize() );
}

TEST_F( BufferTest, FilledBufferAddVectorEqual ) {
    buffer->reserve( 128 );
    
    GLsizeiptr position = 64;
    float* vector = nullptr;
    buffer->add( vector, position );
    ASSERT_EQ( 64, buffer->getPosition() );
    ASSERT_EQ( 128, buffer->getSize() );
    
    GLsizeiptr size = 64;
    bool added = buffer->add( vector, size );
    ASSERT_EQ( true , added );
    ASSERT_EQ( 128, buffer->getPosition() );
    ASSERT_EQ( 128, buffer->getSize() );
}

TEST_F( BufferTest, FilledBufferAddVectorOverflow ) {
    buffer->reserve( 128 );
    
    GLsizeiptr position = 64;
    float* vector = nullptr;
    buffer->add( vector, position );
    ASSERT_EQ( 64, buffer->getPosition() );
    ASSERT_EQ( 128, buffer->getSize() );
    
    GLsizeiptr size = 128;
    bool added = buffer->add( vector, size );
    ASSERT_EQ( false , added );
    ASSERT_EQ( 64, buffer->getPosition() );
    ASSERT_EQ( 128, buffer->getSize() );
}

TEST_F( BufferTest, UnReservedBufferRequest ) {
    GLsizeiptr size = 64;
    float* vector = nullptr;
    
    buffer->requestBufferMemory( vector, size );
    ASSERT_EQ( 64, buffer->getSize() );
    ASSERT_EQ( 0, buffer->getPosition() );
}

TEST_F( BufferTest, ReservedEmptyBufferRequest ) {
    buffer->reserve( 128 );
    GLsizeiptr size = 64;
    float* vector = nullptr;
    
    buffer->requestBufferMemory( vector, size );
    ASSERT_EQ( 64, buffer->getSize() );
    ASSERT_EQ( 0, buffer->getPosition() );
}

TEST_F( BufferTest, ReservedNotEmptyBufferRequest ) {
    buffer->reserve( 128 );
    
    GLsizeiptr position = 64;
    float* vector = nullptr;
    buffer->add( vector, position );
    ASSERT_EQ( 64, buffer->getPosition() );
    ASSERT_EQ( 128, buffer->getSize() );
    
    GLsizeiptr size = 32;
    
    buffer->requestBufferMemory( vector, size );
    ASSERT_EQ( 64, buffer->getPosition() );
    ASSERT_EQ( 96, buffer->getSize() );
}

TEST_F( BufferTest, ReservedNotEmptyBufferRequestFill ) {
    buffer->reserve( 128 );
    
    GLsizeiptr position = 64;
    float* vector = nullptr;
    buffer->add( vector, position );
    ASSERT_EQ( 64, buffer->getPosition() );
    ASSERT_EQ( 128, buffer->getSize() );
    
    GLsizeiptr size = 64;
    
    buffer->requestBufferMemory( vector, size );
    ASSERT_EQ( 64, buffer->getPosition() );
    ASSERT_EQ( 128, buffer->getSize() );
}

TEST_F( BufferTest, ReservedNotEmptyBufferRequestOverflow ) {
    buffer->reserve( 128 );
    
    GLsizeiptr position = 64;
    float* vector = nullptr;
    buffer->add( vector, position );
    ASSERT_EQ( 64, buffer->getPosition() );
    ASSERT_EQ( 128, buffer->getSize() );
    
    GLsizeiptr size = 128;
    
    buffer->requestBufferMemory( vector, size );
    ASSERT_EQ( 64, buffer->getPosition() );
    ASSERT_EQ( 192, buffer->getSize() );
}