//
//  MeshBuilder.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 3/5/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "MeshBuilder.h"
#include "Mesh.hpp"
#include "Exception.h"

MeshBuilder::MeshBuilder() {

}

std::shared_ptr<Mesh> MeshBuilder::buildMesh(
                                    std::shared_ptr<ObjLoader> objParser ) {
    std::shared_ptr<Mesh> mesh = std::shared_ptr<Mesh>( new Mesh );
    std::shared_ptr<ObjInfo> objInfo = objParser->load( );
    for ( std::shared_ptr<ShapeInfo> shapeInfo :  objInfo->shapes ) {
        std::shared_ptr<Shape> meshShape = std::shared_ptr<Shape>( new Shape );
        for ( int i = 0;  i < shapeInfo->indices.size(); i++ ) {
            std::vector<std::vector<int>> indices = shapeInfo->indices.at( i );
            if( indices.size() == 3 ) {
                mapValues( indices, shapeInfo, meshShape );
            } else if( indices.size() == 4 ) {
                std::vector<std::vector<int>> tripletLine0, tripletLine1;
                //counterclockwise
                tripletLine0.push_back( indices.at( 0 ) );
                tripletLine0.push_back( indices.at( 1 ) );
                tripletLine0.push_back( indices.at( 2 ) );
                
                tripletLine1.push_back( indices.at( 0 ) );
                tripletLine1.push_back( indices.at( 2 ) );
                tripletLine1.push_back( indices.at( 3 ) );
                mapValues( tripletLine0, shapeInfo, meshShape );
                mapValues( tripletLine1, shapeInfo, meshShape );
            }
        }
        mesh->addShape( meshShape );
    }
    return mesh;
}

void MeshBuilder::mapValues( const std::vector<std::vector<int>> vectorRow,
                             const std::shared_ptr<ShapeInfo> shapeInfo,
                             std::shared_ptr<Shape> shape ) {
    for ( std::vector<int> vector : vectorRow ) {
        int vIndex = vector.at( ObjLoader::V_KEY ) - 1;
        int vtIndex = vector.at( ObjLoader::VT_KEY ) - 1;
        int vnIndex = vector.at( ObjLoader::VN_KEY ) - 1;
        
        if( shapeInfo->vertices.empty() &&
            shapeInfo->uvs.empty() &&
            shapeInfo->normals.empty() ) {
            throw ObjFormatException( "corrupted info" );
        }

        if ( vnIndex < shapeInfo->vertices.size() ) {
            shape->vertices.push_back( shapeInfo->vertices.at( vIndex ) );
        }
        if ( vtIndex < shapeInfo->uvs.size() ) {
            shape->uvs.push_back( shapeInfo->uvs.at( vtIndex ) );
        }
        if ( vnIndex < shapeInfo->normals.size() ) {
            shape->normals.push_back( shapeInfo->normals.at( vnIndex ) );
        }
    }
}