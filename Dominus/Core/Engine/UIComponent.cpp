//
//  UIComponent.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 24/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "UIComponent.h"

UIComponent::UIComponent() : width(0), height(0), weight(0),hud(false), visible(true), texture(nullptr), parent(nullptr)
                , listener(nullptr)
{
    mesh = new Mesh;
}

UIComponent::~UIComponent()
{

}

void UIComponent::onMeasureCompleted()
{
    
}

void UIComponent::onMeasureChanged()
{

}

//TODO: Update event handling
bool UIComponent::handleEvent( const Event event ) {
//    bool result = false;
//    Point position = Point(event.x, event.y);
//    if (texture->matchPosition(position)) {
//        result = true;
//        if (listener != nullptr) {
//            listener->onItemClicked(this);
//        }
//    }
//
//    return result;
    return false;
}

//TODO: Update render call
void UIComponent::render(Renderer *renderer)
{
    //Update texture with the adjusted values for position and dimensions
//    if (texture!=nullptr && texture->isVisible()) {
//        texture->setPosition(position);
//        renderer->drawTexture(texture, width, height);
//    }
    renderer->drawtexture( this );
}

UIComponent* UIComponent::matchEvent(glm::vec2 position)
{
//    UIComponent* result = nullptr;
//    if (texture->matchPosition(position)) {
//        result = this;
//    }
//    return result;
    return nullptr;
}

//TODO: Update resize logic
void UIComponent::resize(float widthRatio, float heightRatio)
{
    //Resize according to the given ratio
    //update texture dimension to match the component
//    resizeCommand = new ResizeCommand(this, widthRatio, heightRatio);
//    resizeCommand->execute();
}

void UIComponent::resetSize()
{
    //resizeCommand->cancel();
}

void UIComponent::measureDimension()
{
    switch (params.width) {
        case FILL:
            this->width = parent->width;
            break;
        case WRAP:
            this->width = texture->getWidth();
            break;
        default:
            this->width = params.width;
            break;
    }
    
    switch (params.height) {
        case FILL:
            this->height = parent->height;
            break;
        case WRAP:
            this->height = texture->getHeight();
            break;
        default:
            this->height = params.height;
            break;
    }
    if (width < 0) {
        width = 0;
    }
    if (height < 0){
        height = 0;
    }
}

void UIComponent::measurePosition(
                                  glm::vec2 parentPosition,
                                  int parentWidth,
                                  int parentHeight ) {
    if (readjustDimension(parentWidth, parentHeight)) {
        switch (params.gravity) {
            case CENTER:
                center(parentPosition, parentWidth, parentHeight);
                break;
            case CENTER_DOWN:
                centerDown(parentPosition, parentWidth, parentHeight);
                break;
            case UP:
                up(parentPosition, parentWidth, parentHeight);
                break;
            case DOWN:
                down(parentPosition, parentWidth, parentHeight);
                break;
            case RIGHT:
                right(parentPosition, parentWidth, parentHeight);
                break;
            default:
                break;
        }
        readjustPosition();
    }
}

void UIComponent::readjustPosition()
{
    position.x = position.x + params.marginLeft;
    position.y = position.y + params.marginTop;
}

//rescale dimensions if needed (content bigger than container)
//return if the component could be drawed before the rescale (width, height > 0)
bool UIComponent::readjustDimension(int parentWidth, int parentHeight)
{
    bool result = true;
    int virtualWidth = width + params.marginLeft + params.marginRight;
    int virtualHeight = height + params.marginTop + params.marginDown;
    
    if (virtualWidth > parentWidth) {
        width = parentWidth - (params.marginLeft + params.marginRight);
    }
    if(virtualHeight > parentHeight){
        height = parentHeight - (params.marginTop + params.marginDown);
    }
    
    if (width < 0) {
        width = 0;
        result = false;
    }
    if(height < 0){
        height = 0;
        result = false;
    }
    
    return result;
}

void UIComponent::centerDown(glm::vec2 parentPosition, int parentWidth, int parentHeight)
{
    down(parentPosition, parentWidth, parentHeight);
    center(getPosition(), parentWidth, getHeight());
}

void UIComponent::center(glm::vec2 parentPosition, int parentWidth, int parentHeight)
{
    int virtualWidth = width + params.marginLeft + params.marginRight;
    int virtualHeight = height + params.marginTop + params.marginDown;

    int centerX = parentPosition.x + parentWidth / 2;
    int centerY = parentPosition.y + parentHeight / 2;
    int offsetX = virtualWidth / 2;
    int offsetY = virtualHeight / 2;
    setPosition(centerX - offsetX, centerY - offsetY);
}

void UIComponent::up(glm::vec2 parentPosition, int parentWidth, int parentHeight)
{
    int virtualWidth = width + params.marginLeft + params.marginRight;
    
    int centerX = parentPosition.x + parentWidth / 2;
    int offsetX = virtualWidth / 2;
    
    setPosition(centerX - offsetX, parentPosition.y);
}

void UIComponent::down(glm::vec2 parentPosition, int parentWidth, int parentHeight)
{
    int virtualWidth = width + params.marginLeft + params.marginRight;
    int virtualHeight = height + params.marginTop + params.marginDown;
    
    int y = parentPosition.y + parentHeight - virtualHeight;
    int centerX = parentPosition.x + parentWidth / 2;
    int offsetX = virtualWidth / 2;
    setPosition(centerX - offsetX, y);
}

void UIComponent::left(glm::vec2 parentPosition, int parentWidth, int parentHeight)
{
    int virtualHeight = height + params.marginTop + params.marginDown;
    
    int centerY = parentPosition.y + parentHeight / 2;
    int offsetY = virtualHeight / 2;
    
    setPosition(parentPosition.x, centerY - offsetY);
}

void UIComponent::right(glm::vec2 parentPosition, int parentWidth, int parentHeight)
{
    int virtualWidth = width + params.marginLeft + params.marginRight;
    int virtualHeight = height + params.marginTop + params.marginDown;
    
    int centerY = parentPosition.y + parentHeight / 2;
    int offsetY = virtualHeight / 2;
    
    int x = parentPosition.x + parentWidth - virtualWidth;
    setPosition(x, centerY - offsetY);
}

void UIComponent::setPosition(int x, int y)
{
    this->position.x = x;
    this->position.y = y;
}

void UIComponent::setPosition(glm::vec2 position)
{
    this->position = position;
}

glm::vec2 UIComponent::getPosition()
{
    return position;
}

void UIComponent::setWidth(int width)
{
    this->width = width;
}

int UIComponent::getWidth()
{
    return width;
}

void UIComponent::setHeight(int height)
{
    this->height = height;
}

int UIComponent::getHeight()
{
    return height;
}

bool UIComponent::isVisible()
{
    return visible;
}

void UIComponent::setVisible(bool visible)
{
    this->visible = visible;
}

void UIComponent::setParent(UIComponent *component)
{
    this->parent = component;
}

UIComponent* UIComponent::getParent()
{
    return parent;
}

void UIComponent::setHUD(bool hud)
{
    this->hud = hud;
}

bool UIComponent::isHUD()
{
    return hud;
}

void UIComponent::setParams(Params params)
{
    this->params = params;
}


Params UIComponent::getParams()
{
    return this->params;
}
