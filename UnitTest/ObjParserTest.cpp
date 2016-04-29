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
        vertexNormal = "1//3";
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
    ASSERT_EQ( INT_MAX, vec3.at( 2 ) );
}

TEST_F( ObjParserTest, LoadIndexVertexNormalTest ) {
    std::vector<int> vec3 = loader->loadIndex( vertexNormal );
    ASSERT_EQ( 3, vec3.size() );
    ASSERT_EQ( 1, vec3.at( 0 ) );
    ASSERT_EQ( INT_MAX, vec3.at( 1 ) );
    ASSERT_EQ( 3, vec3.at( 2 ) );
}

TEST_F( ObjParserTest, LoadIndexLine3ItemsTest ) {
    std::string indexLine = "1/2/3 1/2/3 1/2/3";
    std::vector<std::vector<int>> vec3 = loader->loadIndexLine( indexLine );
    ASSERT_EQ( 3, vec3.size() );
}

TEST_F( ObjParserTest, LoadIndexLine4ItemsTest ) {
    std::string indexLine = "1/2/3 1/2/3 1/2/3 1/2/3";
    std::vector<std::vector<int>> vec4 = loader->loadIndexLine( indexLine );
    ASSERT_EQ( 4, vec4.size() );
}

TEST_F( ObjParserTest, ParseShapeTest ) {
    StringStream* file = new StringStream;
    file->load( "shape1_parser_test.obj" );
    std::shared_ptr<Shape> shape = loader->loadShape( file );
    ASSERT_EQ( 2, shape->vertices.size() );
    ASSERT_EQ( 2, shape->normals.size() );
    ASSERT_EQ( 2, shape->uvs );
    ASSERT_EQ( 3, shape->indices.size() );
    ASSERT_TRUE( shape->material != "" );
}