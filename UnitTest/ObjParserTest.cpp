//
//  ObjParserTest.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 21/4/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include <stdio.h>
#include "gtest/gtest.h"
#include "ObjLoader.h"
#include <climits>

class ObjParserTest : public ::testing::Test
{
public:
    
    ObjParserTest() {
        loader = new ObjLoader;
        triplet = "1/2/3";
        vertexUv = "1/2";
        vertexNormal = "1//2";
    }
    
    virtual void SetUp() {
        loader = new ObjLoader;
    }
    
    virtual void TearDown() {

    }
    
    ObjLoader* loader;
    std::string triplet;
    std::string vertexUv;
    std::string vertexNormal;
};

TEST_F( ObjParserTest, LoadIndexTripletTest ) {
    std::vector<int> vec3 = loader->loadIndex( triplet );
    ASSERT_EQ( 3, vec3.size() );
    ASSERT_EQ( 1, vec3.at( 0 ) );
    ASSERT_EQ( 2, vec3.at( 1 ) );
    ASSERT_EQ( 3, vec3.at( 2 ) );
}

TEST_F( ObjParserTest, LoadIndexVertexUvTest ) {
    std::vector<int> vec3 = loader->loadIndex( vertexUv );
    ASSERT_EQ( 3, vec3.size() );
    ASSERT_EQ( 1, vec3.at( 0 ) );
    ASSERT_EQ( 2, vec3.at( 1 ) );
    ASSERT_EQ( 3, vec3.at( INT_MAX ) );
}

TEST_F( ObjParserTest, LoadIndexVertexNormalTest ) {
    std::vector<int> vec3 = loader->loadIndex( vertexNormal );
    ASSERT_EQ( 3, vec3.size() );
    ASSERT_EQ( 1, vec3.at( 0 ) );
    ASSERT_EQ( 2, vec3.at( INT_MAX ) );
    ASSERT_EQ( 3, vec3.at( 2 ) );
}