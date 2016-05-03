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
#include "IOExceptions.h"

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
    std::istringstream in( indexLine );
    std::vector<std::vector<int>> vec3 = loader->loadIndexLine( &in );
    ASSERT_EQ( 3, vec3.size() );
}

TEST_F( ObjParserTest, LoadIndexLine4ItemsTest ) {
    std::string indexLine = "1/2/3 1/2/3 1/2/3 1/2/3";
    std::istringstream in( indexLine );
    std::vector<std::vector<int>> vec4 = loader->loadIndexLine( &in );
    ASSERT_EQ( 4, vec4.size() );
}

TEST_F( ObjParserTest, ParseShapeTest ) {
    std::shared_ptr<StringStream> file = std::shared_ptr<StringStream>( new StringStream );
    file->load( "shape1_parser_test.obj" );
    std::shared_ptr<Shape> shape = loader->loadShape( file );
    ASSERT_EQ( 2, shape->vertices.size() );
    ASSERT_EQ( 2, shape->normals.size() );
    ASSERT_EQ( 2, shape->uvs.size() );
    ASSERT_EQ( 3, shape->indices.size() );
    ASSERT_TRUE( !shape->material.empty() );
}

TEST_F( ObjParserTest, ParseShapeFinishBeforeEOF ) {
    std::shared_ptr<StringStream> file = std::shared_ptr<StringStream>( new StringStream );
    file->load( "shape2_parser_test.obj" );
    std::shared_ptr<Shape> shape = loader->loadShape( file );
    ASSERT_EQ( 2, shape->vertices.size() );
    ASSERT_EQ( 2, shape->normals.size() );
    ASSERT_EQ( 2, shape->uvs.size() );
    ASSERT_EQ( 3, shape->indices.size() );
    ASSERT_TRUE( !shape->material.empty() );
}

TEST_F( ObjParserTest, ParseVertexTest ) {
    std::string line = "1 1.2 1.3";
    std::istringstream in( line );
    glm::vec3 vertex = loader->loadVertex( &in );
    ASSERT_EQ( 1, vertex.x );
    ASSERT_EQ( 1.2f, vertex.y );
    ASSERT_EQ( 1.3f, vertex.z );
}

TEST_F( ObjParserTest, ParseVertex2floats ) {
    std::string line = "1 1.2";
    std::istringstream in( line );
    glm::vec3 vertex;
    try {
        vertex = loader->loadVertex( &in );
    } catch ( ParseException e ) {
        std::string errorCode( e.what() );
        ASSERT_TRUE( !errorCode.empty() );
    }
    ASSERT_EQ( 0, vertex.x );
    ASSERT_EQ( 0, vertex.y );
    ASSERT_EQ( 0, vertex.z );
}

TEST_F( ObjParserTest, ParseVertex4floats ) {
    std::string line = "1 1.2 1.3 1.4";
    std::istringstream in( line );
    glm::vec3 vertex;
    vertex = loader->loadVertex( &in );
    ASSERT_EQ( 1, vertex.x );
    ASSERT_EQ( 1.2f, vertex.y );
    ASSERT_EQ( 1.3f, vertex.z );
}

TEST_F( ObjParserTest, ParseVertexBadFormat ) {
    std::string line = "as1 1.2 1eee ";
    std::istringstream in( line );
    glm::vec3 vertex;
    try {
        vertex = loader->loadVertex( &in );
    } catch ( ParseException e ) {
        std::string errorCode( e.what() );
        ASSERT_TRUE( !errorCode.empty() );
    }
    ASSERT_EQ( 0, vertex.x );
    ASSERT_EQ( 0, vertex.y );
    ASSERT_EQ( 0, vertex.z );
}

TEST_F( ObjParserTest, ObjFileParseTest ) {
    std::shared_ptr<ObjInfo> objInfo = loader->load( "objFileParseTest.obj" );
    ASSERT_EQ( 3, objInfo->shapes.size() );
    ASSERT_TRUE( !objInfo->materialLib.empty() );
}

TEST_F( ObjParserTest, ObjFilerParseFNFTest ) {
    try {
        std::shared_ptr<ObjInfo> objInfo = loader->load( "FileNotFound.obj" );
    } catch( FileNotFoundException e ) {
        std::string error( e.what() );
        ASSERT_TRUE( !error.empty() );
    }
}