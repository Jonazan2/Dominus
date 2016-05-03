//
//  MeshBuilder.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 3/5/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "MeshBuilder.h"
#include "Mesh.hpp"

MeshBuilder::MeshBuilder() {

}

std::shared_ptr<Mesh> MeshBuilder::buildMesh(
                                    std::shared_ptr<ObjLoader> objParser ) {
    std::shared_ptr<Mesh> mesh = std::shared_ptr<Mesh>( new Mesh );
    std::shared_ptr<ObjInfo> objInfo = objParser->load( );
    for ( std::shared_ptr<Shape> shape :  objInfo->shapes ) {
        std::shared_ptr<Shape> meshShape = std::shared_ptr<Shape>( new Shape );
        for ( int i = 0;  i < shape->indices.size(); i++ ) {
            std::vector<std::vector<int>> indices = shape->indices.at( i );
            if( indices.size() == 3 ) {
                for ( std::vector<int> triplet : indices ) {
                    int vIndex = triplet.at( ObjLoader::V_KEY ) - 1;
                    int vtIndex = triplet.at( ObjLoader::VT_KEY ) - 1;
                    int vnIndex = triplet.at( ObjLoader::VN_KEY ) - 1;
                    meshShape->vertices.push_back( shape->vertices.at( vIndex ) );
                    meshShape->uvs.push_back( shape->uvs.at( vtIndex ) );
                    meshShape->normals.push_back( shape->normals.at( vnIndex ) );
                }
            } else if( indices.size() == 4 ) {
                std::vector<std::vector<int>> tripletLine0, tripletLine1;
                tripletLine0.push_back( indices.at( 0 ) );
                tripletLine0.push_back( indices.at( 1 ) );
                tripletLine0.push_back( indices.at( 2 ) );
                
                tripletLine1.push_back( indices.at( 0 ) );
                tripletLine1.push_back( indices.at( 2 ) );
                tripletLine1.push_back( indices.at( 3 ) );
                for ( std::vector<int> triplet : tripletLine0 ) {
                    int vIndex = triplet.at( ObjLoader::V_KEY ) - 1;
                    int vtIndex = triplet.at( ObjLoader::VT_KEY ) - 1;
                    int vnIndex = triplet.at( ObjLoader::VN_KEY ) - 1;
                    meshShape->vertices.push_back( shape->vertices.at( vIndex ) );
                    meshShape->uvs.push_back( shape->uvs.at( vtIndex ) );
                    meshShape->normals.push_back( shape->normals.at( vnIndex ) );
                }
                
                for ( std::vector<int> triplet : tripletLine1 ) {
                    int vIndex = triplet.at( ObjLoader::V_KEY ) - 1;
                    int vtIndex = triplet.at( ObjLoader::VT_KEY ) - 1;
                    int vnIndex = triplet.at( ObjLoader::VN_KEY ) - 1;
                    meshShape->vertices.push_back( shape->vertices.at( vIndex ) );
                    meshShape->uvs.push_back( shape->uvs.at( vtIndex ) );
                    meshShape->normals.push_back( shape->normals.at( vnIndex ) );
                }
            }
        }
        mesh->addShape( meshShape );
    }
    return mesh;
}