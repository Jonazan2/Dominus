//
//  Text.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 2/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Text.h"

Text::Text() : UIComponent(), resource(""), changed(false)
{

}

Text::~Text()
{

}

void Text::render(Renderer *renderer)
{
    //TODO: Update render call
//    renderer->renderDrawShape(RECTANGLE_OUTLINE, position, Color(255, 0, 0), width, height);
//    //if the text has been changed create new texture with the new text
//    if (changed && resource != "") {
//        setTexture(renderer->loadText(resource, getColor()));
//        this->changed = false;
//    }
//    
//    if(texture != nullptr && resource != "" && texture->isVisible()){
//        texture->setPosition(getPosition().x, getPosition().y);
//        renderer->drawTexture(texture, width, height);
//    }
}

void Text::setTexture(Texture *texture)
{
    //TODO: Update texture logic
//    texture->hud = this->isHUD();
//    this->texture = texture;
}

void Text::setVisible(bool visible)
{
    //TODO: Update texture logic
    //this->texture->setVisible(visible);
}

//TODO: Color not implemented
//void Text::setColor(Color color)
//{
//    this->color = color;
//}
//
//Color Text::getColor()
//{
//    return color;
//}

void Text::setTextResource(std::string text)
{
    this->resource = text;
    this->changed = true;
}