//
//  BufferTest.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 23/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "gtest/gtest.h"
#include "BufferVec3.h"

class BufferTest : public ::testing::Test
{
public:
    
    BufferTest() {
        buffer = new BufferVec3;
    }
    
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        buffer = new BufferVec3;
    }
    
    BufferVec3* buffer;
};

TEST_F( BufferTest, PushEmptyVector ) {
    std::vector<glm::vec3> vector;
    buffer->push( vector );
    ASSERT_EQ( 0, buffer->getSize() );
}

TEST_F( BufferTest, PushVectorBiggerThanReserved ) {
    buffer->bind();
    std::vector<glm::vec3> vector;
    vector.push_back( glm::vec3( 1 ) );
    vector.push_back( glm::vec3( 1 ) );
    vector.push_back( glm::vec3( 1 ) );
    
    buffer->push( vector );
    ASSERT_EQ( 0, buffer->getSize() );
}

TEST_F( BufferTest, PushVectorBufferUnBinded ) {
    buffer->updateSize( 12 );
    std::vector<glm::vec3> vector;
    vector.push_back( glm::vec3( 1 ) );
    vector.push_back( glm::vec3( 1 ) );
    vector.push_back( glm::vec3( 1 ) );
    
    buffer->push( vector );
    ASSERT_EQ( 0, buffer->getSize() );
}

TEST_F( BufferTest, PushVectorBufferEmpty ) {
    buffer->updateSize( 12 );
    buffer->bind();
    std::vector<glm::vec3> vector;
    vector.push_back( glm::vec3( 1 ) );
    vector.push_back( glm::vec3( 1 ) );
    vector.push_back( glm::vec3( 1 ) );
    
    buffer->push( vector );
    ASSERT_EQ( 36, buffer->getSize() );
}

TEST_F( BufferTest, PushVectorFillBuffer ) {
    buffer->updateSize( 3 );
    buffer->bind();
    std::vector<glm::vec3> vector;
    vector.push_back( glm::vec3( 1 ) );
    vector.push_back( glm::vec3( 1 ) );
    vector.push_back( glm::vec3( 1 ) );
    
    buffer->push( vector );
    ASSERT_EQ( 36, buffer->getSize() );
}

TEST_F( BufferTest, PushVectorBufferNotEmpty ) {
    buffer->updateSize( 12 );
    buffer->bind();
    std::vector<glm::vec3> vector;
    vector.push_back( glm::vec3( 1 ) );
    buffer->push( vector );
    
    ASSERT_EQ( 12, buffer->getSize() );
    std::vector<glm::vec3> vector2;
    vector2.push_back( glm::vec3( 1 ) );
    vector2.push_back( glm::vec3( 1 ) );
    buffer->push( vector2 );
    ASSERT_EQ( 36, buffer->getSize() );
}
