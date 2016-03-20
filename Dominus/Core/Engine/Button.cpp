//
//  Button.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 24/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Button.h"

Button::Button( ) : resource(""),resourceChanged(false)
{

}

Button::~Button()
{

}

void Button::render(Renderer *renderer)
{
     //TODO: Update draw call
    //UIComponent::render(renderer);
//    if (resourceChanged && resource != "") {
//        setTexture(renderer->loadTexture(resource));
//        resourceChanged= false;
//    }
//    
//    texture->setPosition(this->getPosition());
//    renderer->drawTexture(texture, this->getWidth(), this->getHeight());
    renderer->drawtexture( this );
}

void Button::setTexture(Texture *texture)
{
    //TODO: update texture logic
//    texture->hud = this->isHUD();
//    this->texture = texture;
    this->texture = texture;
}

void Button::setImageResource(std::string resource)
{
    this->resource = resource;
    resourceChanged = true;
}