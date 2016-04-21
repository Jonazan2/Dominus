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

//std::shared_ptr<Mesh> ObjLoader::load( const std::string filePath ) {
//    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>( Mesh() );
//    std::string line;
//    std::ifstream file(filePath);
//    
//    if (file.is_open()) {
//        while (std::getline(file, line)) {
//            if ( line.at( 0 ) != '#' ) {
//                //load shape
//            }
//        }
//    }
//    file.close();
//    return mesh;
//}

std::shared_ptr<Shape> ObjLoader::loadShape( std::ifstream file ) {
    std::shared_ptr<Shape> shape = std::make_shared<Shape>( Shape() );
    //Check if stream starts in 'o' // otherwise throw exception
    std::string line;
    bool shapeSpace = true;
    while ( std::getline( file, line ) && shape ) {
        //stop when we found the start of another shape
        shapeSpace = ( line.at( 0 ) != 'o' );
        if( shapeSpace ) {
            std::istringstream in(line);
            std::string type;
            in >> type;
            
            if( type == "v" ) {
                glm::vec3 vertex = loadVertex( line );
                shape->vertices.push_back(vertex);
            }else if( type == "vt" ) {
                glm::vec2 uv = loadUv( line );
                shape->uvs.push_back( uv );
            }else if( type == "vn" ){
                glm::vec3 normal = loadNormal( line );
                shape->normals.push_back(normal);
            }else if( type == "f" ) {
                shape->indices.push_back( loadIndexLine( line ) );
            }
        }
    }
    return shape;
}

glm::vec3 ObjLoader::loadVertex( std::string vertexLine ) {
    glm::vec3 vertex;
    float x, y, z = 0;
    std::istringstream in( vertexLine );
    in >> x >> y >> z;
    //Check x,y,z integrity
    return vertex;
}

glm::vec2 ObjLoader::loadUv( std::string uvLine ) {
    glm::vec2 uv;
    float x, y = 0;
    std::istringstream in( uvLine );
    in >> x >> y;
    //Check x,y,z integrity
    return uv;
}

glm::vec3 ObjLoader::loadNormal( std::string normalLine ) {
    glm::vec3 normal;
    float x, y, z = 0;
    std::istringstream in( normalLine );
    in >> x >> y >> z;
    //Check x,y,z integrity
    return normal;
}

std::vector<std::vector<int>> ObjLoader::loadIndexLine( std::string indexLine ) {
    std::vector<std::vector<int>> indexRow;
    std::vector<std::string> indexComponents;
        /*
         //triangle
         [ item ] [ item ] [ item ]
         
         //quad
         [ item ] [ item ] [ item ] [ item ]
         
         */
    indexComponents = split( indexLine, ' ' );
    
    for ( int i = 0; i < indexComponents.size(); i++ ) {
        std::vector<std::string> itemValues;
        //TODO: Check if the 3-4 index values has the same formatting
        indexRow.push_back( loadIndex( itemValues.at( i ) ) );
    }
    
    return indexRow;
}

std::vector<int> ObjLoader::loadIndex( std::string indexString ) {
    std::vector<int> index;
    std::vector<std::string> indexComponents;
    index.reserve( 3 );
    
    std::size_t found = indexString.find( "//" );
    indexComponents = split ( indexString, '/' );
    if ( found!=std::string::npos ) {
        /*  v//vn  */
        if( indexComponents.size() == 2 ) {
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
