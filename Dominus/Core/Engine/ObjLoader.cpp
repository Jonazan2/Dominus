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
    numTriangles = 0;
}

ObjLoader::~ObjLoader() {

}

std::shared_ptr<Mesh> ObjLoader::load( const std::string filePath ) {
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>( Mesh() );
    std::string line;
    std::ifstream file(filePath);
    
    if (file.is_open()) {
        while (std::getline(file, line)) {
            if ( line.at( 0 ) != '#' ) {
                //load shape
            }
        }
    }
    file.close();
    return mesh;
}

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
                std::vector<glm::vec3> vertex = loadVertex( line );
            }else if( type == "vt" ) {
                std::vector<glm::vec2> uv = loadUv( line );
            }else if( type == "vn" ){
                std::vector<glm::vec3> normal = loadNormal( line );
            }else if( type == "f" ) {
                std::vector<int> index = loadIndex( line);
            }
        }
    }
    return shape;
}

std::vector<std::string> ObjLoader::split( const std::string s, const char delimiter ) const {
    std::vector<std::string> elements;
    if ( !s.empty() ) {
        std::stringstream ss(s);
        std::string token;
        
        while(getline(ss, token, delimiter)) {
            elements.push_back(token);
        }
    } else {
        elements.push_back(s);
    }
    
    return elements;
}
