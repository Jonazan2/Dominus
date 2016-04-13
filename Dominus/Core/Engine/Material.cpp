#include "Material.h"

Material::Material() {}

void Material::loadMaterial( const std::string filePath) {
    this->filePath = filePath;
    std::ifstream file(filePath);
    std::string line;
    
    if (file.is_open()) {

        while (std::getline(file, line)) {
            float x, y, z;
            std::istringstream in(line);

            if (line.at(0) != '#') {
                std::string type;
                in >> type;
                
                if ( type == "newmtl" ) {
                    std::string value;
                    in >> value;
                    name = value;
                } else if ( type == "Ka") {
                    in >> x >> y >> z;
                    ambientColor = new glm::vec3(x,y,z);
                } else if ( type == "Kd") {
                    in >> x >> y >> z;
                    diffuseColor = new glm::vec3(x,y,z);
                } else if ( type == "Ks") {
                    in >> x >> y >> z;
                    specularColor = new glm::vec3(x,y,z);
                } else if ( type == "Ns" ) {
                    in >> weightSpecularColor;
                } else if ( type == "d") {
                    in >> dissolved;
                } else if ( type == "Tr") {
                    in >> transparent;
                } else if ( type == "illum") {
                    short value;
                    in >> value;
                    illuminationModel = IlluminationModel(value);
                } else if ( type == "map_Ka" ) {
                    in >> ambientTextureMap;
                } else if ( type == "map_Kd" ) {
                    in >> diffuseTextureMap;
                } else if ( type == "map_Ks" ) {
                    in >> specularTextureMap;
                } else if ( type == "map_Ns" ) {
                    in >> specularTextureHighlightMap;
                } else if ( type == "map_d" ) {
                    in >> alphaTextureMap;
                } else if ( type == "map_bump" || type == "bump" ) {
                    in >> bumpTextureMap;
                } else if ( type == "disp" ) {
                    in >> displacementTextureMap;
                } else if ( type == "decal" ) {
                    in >> stencilTextureMap;
                }
            }
        }
    }
    file.close();
}

bool Material::isTexturedMaterial() const {
    return !( ambientTextureMap.empty() && diffuseTextureMap.empty()
            && specularTextureMap.empty() && specularTextureHighlightMap.empty()
            && alphaTextureMap.empty() && bumpTextureMap.empty()
            && displacementTextureMap.empty() && stencilTextureMap.empty() );
}

void Material::setName( const std::string name ) {
    this->name = name;
}

std::string Material::getName() const {
    return name;
}

void Material::setAmbientColor( glm::vec3 ambientColor ) {
    this->ambientColor = &ambientColor;
}

glm::vec3 Material::getAmbientColor() const {
    return *ambientColor;
}

void Material::setDiffuseColor( glm::vec3 diffuseColor ) {
    this->diffuseColor = &diffuseColor;
}

glm::vec3 Material::getDiffuseColor() const {
    return *diffuseColor;
}

void Material::setSpecularColor( glm::vec3 specularColor ) {
    this->specularColor = &specularColor;
}

glm::vec3 Material::getSpecularColor() const {
    return *specularColor;
}

void Material::setWeightSpecularColor( const float weight ) {
    this->weightSpecularColor = weight;
}

float Material::getWeightSpecularColor() const {
    return weightSpecularColor;
}

void Material::setDissolved( const float dissolved ) {
    this->dissolved = dissolved;
}

float Material::getDissolved() const {
    return dissolved;
}

void Material::setTransparent( const float transparent ) {
    this->transparent = transparent;
}

float Material::getTransparent() const {
    return transparent;
}

void Material::setIlluminationModel( const IlluminationModel model ) {
    this->illuminationModel = model;
}

Material::IlluminationModel Material::getIlluminationModel() const {
    return illuminationModel;
}

void Material::setAmbientTextureMap( const std::string ambientMap ) {
    this->ambientTextureMap = ambientMap;
}

std::string Material::getAmbientTextureMap() const {
    return ambientTextureMap;
}

void Material::setDiffuseTextureMap( const std::string diffuseMap ) {
    this->diffuseTextureMap = diffuseMap;
}

std::string Material::getDiffuseTextureMap() const {
    return diffuseTextureMap;
}

void Material::setSpecularTextureMap( const std::string specularMap ) {
    this->specularTextureMap = specularMap;
}

std::string Material::getSpecularTextureMap() const {
    return specularTextureMap;
}

void Material::setSpecularTextureHighlightMap( const std::string highlightMap ) {
    this->specularTextureHighlightMap = highlightMap;
}

std::string Material::getSpecularTextureHighlightMap() const {
    return specularTextureHighlightMap;
}

void Material::setAlphaTextureMap( const std::string alphaMap ) {
    this->alphaTextureMap = alphaMap;
}

std::string Material::getAlphaTextureMap() const {
    return alphaTextureMap;
}

void Material::setBumpTextureMap( const std::string bumpMap ) {
    this->bumpTextureMap = bumpMap;
}

std::string Material::getBumpTextureMap() const {
    return bumpTextureMap;
}

void Material::setDisplacementTextureMap( const std::string displacementMap ) {
    this->displacementTextureMap = displacementMap;
}

std::string Material::getDisplacementTextureMap() const {
    return displacementTextureMap;
}

void Material::setStencilTextureMap( const std::string stencilMap ) {
    this->stencilTextureMap = stencilMap;
}

std::string Material::getStencilTextureMap() const {
    return stencilTextureMap;
}


Material::~Material() {

}