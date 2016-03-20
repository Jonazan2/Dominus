//
//  UIComponent.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 24/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_UIComponent_h
#define ProjectWar_UIComponent_h

#include "Renderer.h"
#include "Params.h"
#include "Texture.h"
#include "Frame.h"
#include "Event.h"
#include "OnItemClickedListener.h"
#include "Mesh.hpp"

class UIComponent {
public:
    UIComponent();
    virtual ~UIComponent();
    virtual void render( Renderer* renderer );
    virtual UIComponent* matchEvent( glm::vec2 position );
    
    virtual bool handleEvent( const Event event );
    
    virtual void onMeasureCompleted();
    virtual void onMeasureChanged();
    
    virtual void resize( float widthRatio, float heightRatio );
    virtual void resetSize();
    
    void measureDimension();
    void measurePosition( glm::vec2 parentPosition,
                         int parentWidth,
                         int parentHeight );
    
    //readjust dimension when needed, never allowes a component higher or wider than the parent
    bool readjustDimension(int parentWidth, int parentHeight);
    //readjust component position to fix the margin displacement
    void readjustPosition();
    
    void center( glm::vec2 parentPosition, int parentWidth, int parentHeight ) ;
    void up( glm::vec2 parentPosition, int parentWidth, int parentHeight );
    void down( glm::vec2 parentPosition, int parentWidth, int parentHeight );
    void right( glm::vec2 parentPosition, int parentWidth, int parentHeight );
    void left( glm::vec2 parentPosition, int parentWidth, int parentHeight );
    void centerDown( glm::vec2 parentPosition, int parentWidth, int parentHeight );
    
    void setHUD( bool hud );
    bool isHUD();
    
    void setParams( Params params );
    Params getParams();
    
    void setPosition( int x, int y );
    void setPosition( glm::vec2 position );
    glm::vec2 getPosition();
    
    void setWidth( int width );
    int getWidth();
    
    void setHeight( int height );
    int getHeight();
    
    void setVisible( bool visible );
    bool isVisible();
    
    void setParent( UIComponent* component );
    UIComponent* getParent();
    
    UIComponent* parent;
    Params params;
    glm::vec2 position;
    Texture* texture;
    int width;
    int height;
    bool hud;
    bool visible;
    float weight;
    Frame frame;
    OnItemClickedListener* listener;
    Frame menuFrame;
    Mesh* mesh;
};

#endif
