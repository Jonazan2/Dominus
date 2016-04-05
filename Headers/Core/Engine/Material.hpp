#ifndef Material_hpp
#define Material_hpp

#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>

class Material {
    
    enum IlluminationModel {
        COLOR_ON_AMBIENT_OFF = 0,
        COLOR_ON_AMBIENT_ON = 1,
        HIGHLIGHT_ON = 2,
        REFLECTION_ON_RAY_TRACE_ON = 3,
        TRANSPARENCY_GLASS_ON_RAY_TRACE_ON = 4,
        TRANSPARENCY_FRESNEL_ON_RAY_TRACE_ON = 5,
        TRANSPARENCY_REFRACTION_ON_REFLECTION_FRESNEL_OFF_RAY_TRACE_ON = 6,
        TRANSPARENCY_REFRACTION_ON_REFLECTION_FRESNEL_ON_RAY_TRACE_ON = 7,
        REFLECTION_ON_RAY_TRACE_OFF = 8,
        TRANSPARENCY_GLASS_ON_REFLECTION_RAY_TRACE_OFF = 9,
        CASTS_SHADOWS_ONTO_INVISIBLE_SURFACES = 10
    };
    
public:
    Material();
    void loadMaterial( const std::string );
    bool isTexturedMaterial() const;
    
    void setName( const std::string );
    std::string getName() const;
    void setAmbientColor( glm::vec3 );
    glm::vec3 getAmbientColor() const;
    void setDiffuseColor( glm::vec3 );
    glm::vec3 getDiffuseColor() const;
    void setSpecularColor( glm::vec3 );
    glm::vec3 getSpecularColor() const;
    void setWeightSpecularColor( const float );
    float getWeightSpecularColor() const;
    void setDissolved( const float );
    float getDissolved() const;
    void setTransparent( const float );
    float getTransparent() const;
    void setIlluminationModel( const IlluminationModel );
    IlluminationModel getIlluminationModel() const;
    
    void setAmbientTextureMap( const std::string );
    std::string getAmbientTextureMap() const;
    void setDiffuseTextureMap( const std::string );
    std::string getDiffuseTextureMap() const;
    void setSpecularTextureMap( const std::string );
    std::string getSpecularTextureMap() const;
    void setSpecularTextureHighlightMap( const std::string );
    std::string getSpecularTextureHighlightMap() const;
    void setAlphaTextureMap( const std::string );
    std::string getAlphaTextureMap() const;
    void setBumpTextureMap( const std::string );
    std::string getBumpTextureMap() const;
    void setDisplacementTextureMap( const std::string );
    std::string getDisplacementTextureMap() const;
    void setStencilTextureMap( const std::string );
    std::string getStencilTextureMap() const;
    
    ~Material();
    
private:
    std::string filePath;
    
    std::string name;
    glm::vec3 *ambientColor;
    glm::vec3 *diffuseColor;
    glm::vec3 *specularColor;
    float weightSpecularColor;
    float dissolved; // 1 - transparent
    float transparent; // 1 - dissolved
    IlluminationModel illuminationModel;

    std::string ambientTextureMap;
    std::string diffuseTextureMap;
    std::string specularTextureMap;
    std::string specularTextureHighlightMap;
    std::string alphaTextureMap;
    std::string bumpTextureMap;
    std::string displacementTextureMap;
    std::string stencilTextureMap;
};

#endif /* Material_hpp */
