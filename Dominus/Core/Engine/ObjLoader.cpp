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

void ObjLoader::load( const std::string filePath,
                      std::vector<glm::vec3>* outVertices,
                      std::vector<glm::vec2>* outUvs,
                      std::vector<glm::vec3>* outNormals ) {
    std::string line;
    std::ifstream file(filePath);
    
    if (file.is_open()) {
        std::vector<glm::vec3*> *tempVertices = new std::vector<glm::vec3 *>;
        std::vector<glm::vec2*> *tempTextureVertices = new std::vector<glm::vec2 *>;
        std::vector<glm::vec3*> *tempNormalsVertices = new std::vector<glm::vec3 *>;
        std::vector<int> *tempIndices = new std::vector<int>;
        
        while (std::getline(file, line)) {
            std::istringstream in(line);
            
            if (line.at(0) != '#') {
                
                float x, y, z;
                std::string type;
                in >> type;
                
                if( type == "v" ){
                    in >> x >> y >> z;
                    tempVertices->push_back( new glm::vec3(x,y,z) );
                }else if( type == "vt" ){
                    in >> x >> y;
                    tempTextureVertices->push_back( new glm::vec2(x,y) );
                }else if( type == "vn" ){
                    in >> x >> y >> z;
                    tempNormalsVertices->push_back( new glm::vec3(x,y,z) );
                }else if( type == "f" ) {
                    std::vector<std::string> triplets = split(line, ' ');
                    for ( std::string triplet : triplets ) {
                        std::vector<std::string> elements = split(triplet, '/');
                        
                        if (elements.size() == 2) {
                            // Although we can parse v//vn we are not handling this case
                            // while creating the final vertex list just yet
                            tempIndices->push_back(std::stoi(elements.at(0))); // v
                            tempIndices->push_back(std::stoi(elements.at(1))); // vn
                        } else if (elements.size() == 3) {
                            tempIndices->push_back(std::stoi(elements.at(0))); // v
                            tempIndices->push_back(std::stoi(elements.at(1))); // vt
                            tempIndices->push_back(std::stoi(elements.at(2))); // vn
                        }
                    }
                } else if ( type == "mtlib" || type == "usemtl" ) {
                    // We handle just one material per obj, but there could be
                    // multiple ones
                    std::string name;
                    in >> name;
                    //TODO: Parse material
                    //material.loadMaterial(name);
                }
            }
        }
        
        // Reserve memory before hand for vertices
        numTriangles = (int)tempIndices->size() / 9;
        outVertices->reserve(numTriangles);
        outUvs->reserve(numTriangles);
        outNormals->reserve(numTriangles);
        
        // Traverse faces list and create sorted list of vertices
        const int tempIndicesSize = (int) tempIndices->size();
        for( int i = 0; i < tempIndicesSize; i++ ){
            outVertices->push_back(*tempVertices->at(tempIndices->at(i) - 1));
            outUvs->push_back( *tempTextureVertices->at(tempIndices->at(++i) - 1) );
            outNormals->push_back( *tempNormalsVertices->at(tempIndices->at(++i) -1) );
        }
        
        // Free temporary vectors
        for ( auto vertex : *tempVertices ) {
            delete vertex;
        }
        delete tempVertices;
        
        for ( auto vertex : *tempTextureVertices ) {
            delete vertex;
        }
        delete tempTextureVertices;
        
        for ( auto vertex : *tempNormalsVertices ) {
            delete vertex;
        }
        delete tempNormalsVertices;
        
        delete tempIndices;
    }
    file.close();
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
