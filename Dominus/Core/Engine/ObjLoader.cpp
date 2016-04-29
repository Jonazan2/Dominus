//
//  ObjLoader.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 28/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "ObjLoader.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>

ObjLoader::ObjLoader() {

}

ObjLoader::~ObjLoader() {

}

std::shared_ptr<Mesh> ObjLoader::load( const std::string filePath ) {
    std::shared_ptr<Mesh> mesh = std::shared_ptr<Mesh>( new Mesh() );
    std::string line;
    std::shared_ptr<StringStream> file =
        std::shared_ptr<StringStream>( new StringStream );
    file->load( filePath );
    while ( file->getLine( line ) ) {
        if( line.at( 0 ) != '#' ) {
            if( line.at( 0 ) == 'o' ) {
                mesh ->addShape( loadShape( file ) );
            }
        }
    }
    return mesh;
}

std::shared_ptr<Shape> ObjLoader::loadShape(
                        std::shared_ptr<StringStream> file ) {
    std::shared_ptr<Shape> shape = std::make_shared<Shape>( Shape() );
    std::string line;
    bool shapeSpace = true;
    while ( file->getLine( line ) && shapeSpace ) {
        std::istringstream in( line );
        std::string type;
        in >> type;
        if( type == "v" ) {
            glm::vec3 vertex = loadVertex( &in );
            shape->vertices.push_back(vertex);
        } else if( type == "vt" ) {
            glm::vec2 uv = loadUv( &in );
            shape->uvs.push_back( uv );
        } else if( type == "vn" ){
            glm::vec3 normal = loadNormal( &in );
            shape->normals.push_back(normal);
        } else if( type == "f" ) {
            shape->indices.push_back( loadIndexLine( &in ) );
        } else if ( type == "usemtl" ){
            shape->material = parseMaterialName( &in );
        }
        
        if( file->peekLine().at( 0 ) == 'o' ){
            shapeSpace = false;
        }
    }
    return shape;
}

std::string ObjLoader::parseMaterialName( std::istringstream *materiallLine ) {
    //TODO: implement
    return "material";
}


glm::vec3 ObjLoader::loadVertex( std::istringstream* in ) {
    float x, y, z = INT_MAX;
    *in >> x >> y >> z;
    //Check x,y,z integrity
    if( x == INT_MAX || y == INT_MAX || z == INT_MAX ) {
        throw UnbindException(-1);
    }
    return glm::vec3( x, y, z );
}

glm::vec2 ObjLoader::loadUv( std::istringstream* in ) {
    float x, y = INT_MAX;
    *in >> x >> y;
    //Check x,y,z integrity
    if( x == INT_MAX || y == INT_MAX ) {
        throw UnbindException(-1);
    }
    return  glm::vec2( x, y );
}

glm::vec3 ObjLoader::loadNormal( std::istringstream* in ) {
    float x, y, z = INT_MAX;
    *in >> x >> y >> z;
    //Check x,y,z integrity
    if( x == INT_MAX || y == INT_MAX || z == INT_MAX ) {
        throw UnbindException(-1);
    }
    return  glm::vec3( x, y, z );;
}

std::vector<std::vector<int>> ObjLoader::loadIndexLine(
                                            std::istringstream* indexLine ) {
    std::vector<std::vector<int>> indexRow;
    std::vector<std::string> indexComponents;
        /*
         //triangle
         [ item ] [ item ] [ item ]
         
         //quad
         [ item ] [ item ] [ item ] [ item ]
         
         */
    indexComponents = split( indexLine->str(), ' ' );
    for ( int i = 0; i < indexComponents.size(); i++ ) {
        //TODO: Check if the 3-4 index values has the same formatting
        if( indexComponents.at(i) != "f" ) {
            indexRow.push_back( loadIndex( indexComponents.at( i ) ) );
        }
    }

    
    return indexRow;
}

std::vector<int> ObjLoader::loadIndex( std::string indexString ) {
    std::vector<int> index;
    std::vector<std::string> indexComponents;
    
    std::size_t found = indexString.find( "//" );
    indexComponents = split ( indexString, '/' );
    if ( found!=std::string::npos ) {
        /*  v//vn  */
        if( indexComponents.size() == 3 ) {
            // (v, - , vn)
            index.push_back( std::stoi( indexComponents.at( V_KEY ) ) );
            index.push_back( INT_MAX );
            index.push_back( std::stoi( indexComponents.at( VN_KEY ) ) );
        } else {
            //formatting exception
        }
    } else {
        if( indexComponents.size() == 2 ) {
            /*  v/vt  */
            index.push_back( std::stoi( indexComponents.at( V_KEY ) ) );
            index.push_back( std::stoi( indexComponents.at( VT_KEY ) ) );
            index.push_back( INT_MAX );
        } else if( indexComponents.size() == 3 ) {
            /*  v/vt/vn  */
            index.push_back( std::stoi( indexComponents.at( V_KEY ) ) );
            index.push_back( std::stoi( indexComponents.at( VT_KEY ) ) );
            index.push_back( std::stoi( indexComponents.at( VN_KEY ) ) );
        } else {
            //formatting exception
        }
    }
    return index;
}

std::vector<std::string> ObjLoader::split( const std::string s,
                                           char delimiter ) const {
    std::vector<std::string> elements;
    if ( !s.empty() ) {
        std::stringstream ss( s );
        std::string token;
        
        while( getline( ss, token, delimiter ) ) {
            elements.push_back( token );
        }
    }
    return elements;
}
