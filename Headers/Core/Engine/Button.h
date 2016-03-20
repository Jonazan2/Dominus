//
//  Button.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 24/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Button__
#define __ProjectWar__Button__

#include <stdio.h>

#include "UIComponent.h"

class Button : public UIComponent
{
public:
    Button();
    virtual ~Button();
    void render(Renderer* renderer);
    void setTexture(Texture* texture);
    void setImageResource(std::string resource);
private:
    std::string resource;
    bool resourceChanged;
};

#endif /* defined(__ProjectWar__Button__) */
