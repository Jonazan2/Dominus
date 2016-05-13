//
//  MeshBuilderTest.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 4/5/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include <stdio.h>
#include "gtest/gtest.h"
#include "MeshBuilder.h"
#include "Mesh.hpp"
#include "Exception.h"
#include <climits>

class MeshBuilderTest : public ::testing::Test
{
public:
    MeshBuilderTest() {
        meshBuilder = new MeshBuilder;
        triplet1 = std::vector<int>{ 1, 1, 1 };
        triplet2 = std::vector<int>{ 2, 2, 2 };
        triplet3 = std::vector<int>{ 3, 3, 3 };
        
        pairVn1 = std::vector<int>{ 1, INT_MAX, 1 };
        pairVn2 = std::vector<int>{ 2, INT_MAX, 2 };
        pairVn3 = std::vector<int>{ 3, INT_MAX, 3 };
        
        pairVt1 = std::vector<int>{ 1, 1, INT_MAX };
        pairVt2 = std::vector<int>{ 2, 2, INT_MAX };
        pairVt3 = std::vector<int>{ 3, 3, INT_MAX };
        
        glm::vec3 vert1 = glm::vec3( 1, 2, 3 );
        glm::vec3 vert2 = glm::vec3( 4, 5, 6 );
        glm::vec3 vert3 = glm::vec3( 7, 8, 9 );
        
        glm::vec2 uv1 = glm::vec2( 1, 2 );
        glm::vec2 uv2 = glm::vec2( 3, 4 );
        glm::vec2 uv3 = glm::vec2( 5, 6 );
        
        glm::vec3 normal1 = glm::vec3( 1, 2, 3 );
        glm::vec3 normal2 = glm::vec3( 4, 5, 6 );
        glm::vec3 normal3 = glm::vec3( 7, 8, 9 );
        vertices = std::vector<glm::vec3>{ vert1, vert2, vert3 };
        uvs = std::vector<glm::vec2>{ uv1, uv2, uv3 };
        normals = std::vector<glm::vec3>{ normal1, normal2, normal3 };
        
        //v  1 2 3
        //v  4 5 6
        //v  7 8 9
        //vt 1 2
        //vt 3 4
        //vt 5 6
        //vn 1 2 3
        //vn 4 5 6
        //vn 7 8 9
    }
    
    virtual void SetUp() {

    }
    
    virtual void TearDown() {
        
    }
    MeshBuilder* meshBuilder;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::vector<int>triplet1;
    std::vector<int>triplet2;
    std::vector<int>triplet3;
    
    std::vector<int>pairVn1;
    std::vector<int>pairVn2;
    std::vector<int>pairVn3;
    
    std::vector<int>pairVt1;
    std::vector<int>pairVt2;
    std::vector<int>pairVt3;
};

// Triangle triple: 1/1/1 2/2/2 3/3/3

TEST_F( MeshBuilderTest, MapValuesCorruptedShape ) {
    std::vector<std::vector<int>>triangleTriple{ triplet3, triplet1, triplet2 };
    std::shared_ptr<Shape> shape = std::make_shared<Shape>( Shape() );
    std::shared_ptr<ShapeInfo> shapeInfo =
    std::make_shared<ShapeInfo>( ShapeInfo() );
    try {
        meshBuilder->mapValues( triangleTriple, shapeInfo, shape );
    } catch ( ObjFormatException e ) {
        //TODO: add ASSERT
    }
}

TEST_F( MeshBuilderTest, MapValuesTriangleTripletTest ) {
    std::vector<std::vector<int>>triangleTriple{ triplet3, triplet1, triplet2 };
    std::shared_ptr<Shape> shape = std::make_shared<Shape>( Shape() );
    std::shared_ptr<ShapeInfo> shapeInfo =
        std::make_shared<ShapeInfo>( ShapeInfo() );
    shapeInfo->vertices = vertices;
    shapeInfo->uvs = uvs;
    shapeInfo->normals = normals;
    meshBuilder->mapValues( triangleTriple, shapeInfo, shape );
    ASSERT_EQ( 3 , shape->vertices.size() );
    ASSERT_TRUE( glm::vec3( 7, 8, 9 ) == shape->vertices.at( 0 ) );
    ASSERT_TRUE( glm::vec3( 1, 2, 3 ) == shape->vertices.at( 1 ) );
    ASSERT_TRUE( glm::vec3( 4, 5, 6 ) == shape->vertices.at( 2 ) );
}

TEST_F( MeshBuilderTest, MapValuesTrianglePairVNTest ) {
    std::vector<std::vector<int>>trianglePair{ pairVn3, pairVn1, pairVn2 };
    std::shared_ptr<Shape> shape = std::make_shared<Shape>( Shape() );
    std::shared_ptr<ShapeInfo> shapeInfo =
    std::make_shared<ShapeInfo>( ShapeInfo() );
    shapeInfo->vertices = vertices;
    shapeInfo->uvs = uvs;
    shapeInfo->normals = normals;
    meshBuilder->mapValues( trianglePair, shapeInfo, shape );
    ASSERT_EQ( 3 , shape->normals.size() );
    ASSERT_EQ( 0, shape->uvs.size() );
    ASSERT_TRUE( glm::vec3( 7, 8, 9 ) == shape->normals.at( 0 ) );
    ASSERT_TRUE( glm::vec3( 1, 2, 3 ) == shape->normals.at( 1 ) );
    ASSERT_TRUE( glm::vec3( 4, 5, 6 ) == shape->normals.at( 2 ) );
}

TEST_F( MeshBuilderTest, MapValuesTrianglePairVTTest ) {
    std::vector<std::vector<int>>trianglePair{ pairVt3, pairVt1, pairVt2 };
    std::shared_ptr<Shape> shape = std::make_shared<Shape>( Shape() );
    std::shared_ptr<ShapeInfo> shapeInfo =
    std::make_shared<ShapeInfo>( ShapeInfo() );
    shapeInfo->vertices = vertices;
    shapeInfo->uvs = uvs;
    shapeInfo->normals = normals;
    meshBuilder->mapValues( trianglePair, shapeInfo, shape );
    ASSERT_EQ( 3 , shape->uvs.size() );
    ASSERT_EQ( 0, shape->normals.size() );
    ASSERT_TRUE( glm::vec2( 5, 6 ) == shape->uvs.at( 0 ) );
    ASSERT_TRUE( glm::vec2( 1, 2 ) == shape->uvs.at( 1 ) );
    ASSERT_TRUE( glm::vec2( 3, 4 ) == shape->uvs.at( 2 ) );
}