//
//  UIComponent.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 14/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef UIComponent_h
#define UIComponent_h

#include <vector>
#include <glm/glm.hpp>
#include <OpenGL/gl3.h>
#include "Texture.h"

class UIComponent {
public:
    UIComponent();
    ~UIComponent();
    
    std::vector<glm::vec3> getVertices() const;
    GLsizeiptr getVertexSize() const;
    std::vector<glm::vec2> getUvs() const;
    GLsizeiptr getUvsSize() const;
    void setTexture( Texture* texture );
    Texture* getTexture() const;
    
    int x;
    int y;
private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    Texture* texture;
};

#endif /* UIComponent_h */
