//
//  Text.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 2/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Text__
#define __ProjectWar__Text__

#include <stdio.h>
#include <iostream>
#include "Texture.h"
#include "UIComponent.h"

class Text : public UIComponent
{
public:
    //TODO: Color not implemented
    //const Color WHITE = Color(255,255,255);
    Text();
    virtual ~Text();
    void render(Renderer* renderer);
    void setTextResource(std::string text);
    void setVisible(bool visible);
    void setTexture(Texture* texture);
    
//    void setColor(Color color);
//    Color getColor();
    //TODO implement set font
    //TODO implement set text size
private:
    std::string resource;
    //Flag to know if the text resource has been changed
    bool changed;
    //Color color;
};

#endif /* defined(__ProjectWar__Text__) */
