//
//  Layout.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 24/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Layout__
#define __ProjectWar__Layout__

#include <stdio.h>
#include <list>
#include <vector>
#include "Params.h"


#include "UIComponent.h"
#include "Event.h"

class Layout : public UIComponent
{
public:
    Layout();
    virtual ~Layout();
    virtual void addComponent( UIComponent* component) ;
    void render( Renderer* renderer );
    void setBackground( Texture* background );
    //TODO: Color not implemented
    //void setBackground(Color color);
    UIComponent* matchEvent( glm::vec2 position );
    void cleanComponents();
    
    void resize( float widthRatio, float heightRatio );
    void resetSize();
    
    virtual void onContentMeasureCompleted();
    
    bool handleEvent(const Event event);
    
    virtual void onMeasureCompleted();
    virtual void onMeasureChanged();
    virtual void measureDisposition();
    virtual void populateLayout( std::vector<glm::vec2> dispositionPoints );
    void assignFrames( std::vector<glm::vec2> dispositionPoints );
    virtual void assignFrames(
                              std::vector<glm::vec2>dispositionPoints,
                              std::vector<UIComponent*> components );
    
    std::vector<glm::vec2> layoutDisposition();
    std::list<UIComponent*> components;
private:
    //TODO remove
    Texture* background;
    //Color* backgroundColor;
};

#endif /* defined(__ProjectWar__Layout__) */
