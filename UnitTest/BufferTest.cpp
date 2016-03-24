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

using ::testing::Return;

class BufferTest : public ::testing::Test
{
public:
    
    BufferTest() {
        buffer = new Buffer( &mockGpuBuffer );
    }
    
    virtual void SetUp() {
        EXPECT_CALL( mockGpuBuffer, genBuffer() ).WillOnce(testing::Return( 1 ) );
        buffer->reserve( 128 );
        buffer->bind();
    }
    
    virtual void TearDown() {
        MockGPUBuffer mockGpuBuffer;
        buffer = new Buffer( &mockGpuBuffer );
    }
    
    MockGPUBuffer mockGpuBuffer;
    Buffer* buffer;
};

TEST_F( BufferTest, EmptyBufferPushUnbindVector ) {
    buffer->unBind();
    GLsizeiptr size = 32;
    float* vector = nullptr;
    try {
        buffer->push( vector, size );
    } catch ( const UnbindException &e ) {
        ASSERT_EQ( 128, buffer->getSize() );
    }
}

TEST_F( BufferTest, EmptyBufferPushVector ) {
    GLsizeiptr size = 32;
    float* vector = nullptr;
    //EXPECT_CALL( mockGpuBuffer, mapBuffer( 0 ) );
    buffer->push( vector, size );
    ASSERT_EQ( 32, buffer->getPosition() );
    ASSERT_EQ( 128, buffer->getSize() );
}

TEST_F( BufferTest, EmptyBufferPushVectorOverflow ) {
    GLsizeiptr size = 256;
    float* vector = nullptr;
    buffer->push( vector, size );
    ASSERT_EQ( 256, buffer->getPosition() );
    ASSERT_EQ( 256, buffer->getSize() );
}

TEST_F( BufferTest, EmptyBufferPushEqualVector ) {
    GLsizeiptr size = 128;
    float* vector = nullptr;
    buffer->push( vector, size );
    ASSERT_EQ( 128, buffer->getPosition() );
    ASSERT_EQ( 128, buffer->getSize() );
}

TEST_F( BufferTest, FilledBufferPushVector ) {
    GLsizeiptr position = 64;
    float* vector = nullptr;
    buffer->push( vector, position );
    ASSERT_EQ( 64, buffer->getPosition() );
    ASSERT_EQ( 128, buffer->getSize() );
    
    GLsizeiptr size = 32;
    buffer->push( vector, size );
    ASSERT_EQ( 96, buffer->getPosition() );
    ASSERT_EQ( 128, buffer->getSize() );
}

TEST_F( BufferTest, FilledBufferPushVectorEqual ) {
    GLsizeiptr position = 64;
    float* vector = nullptr;
    buffer->push( vector, position );
    ASSERT_EQ( 64, buffer->getPosition() );
    ASSERT_EQ( 128, buffer->getSize() );
    
    GLsizeiptr size = 64;
    buffer->push( vector, size );
    ASSERT_EQ( 128, buffer->getPosition() );
    ASSERT_EQ( 128, buffer->getSize() );
}

TEST_F( BufferTest, FilledBufferPushVectorOverflow ) {
    GLsizeiptr position = 64;
    float* vector = nullptr;
    buffer->push( vector, position );
    ASSERT_EQ( 64, buffer->getPosition() );
    ASSERT_EQ( 128, buffer->getSize() );
    
    GLsizeiptr size = 128;
    buffer->push( vector, size );
    ASSERT_EQ( 192, buffer->getPosition() );
    ASSERT_EQ( 192, buffer->getSize() );
}