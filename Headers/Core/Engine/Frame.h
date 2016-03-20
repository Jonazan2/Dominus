//
//  Frame.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 4/9/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_Frame_h
#define ProjectWar_Frame_h

#include <glm/glm.hpp>

class Frame
{
public:
    Frame() : width(0), height(0)
    {}
    ~Frame(){}
    
    glm::vec2 position;
    int width;
    int height;
};

#endif
