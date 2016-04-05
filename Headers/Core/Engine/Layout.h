#ifndef __Dominus__Layout__
#define __Dominus__Layout__

#include <stdio.h>
#include <vector>
#include <memory>

#include "Params.h"
#include "UIComponent.h"
#include "Event.h"

class Layout : public UIComponent {
public:
    Layout();
    virtual ~Layout();
    
    virtual void addComponent( std::shared_ptr< UIComponent > component ) ;
    void render( Renderer *renderer );
    void setBackground( std::shared_ptr< Texture > background );
    std::shared_ptr<UIComponent> matchEvent( glm::vec2 position );
    void cleanComponents();
    void resize( float widthRatio, float heightRatio );
    void resetSize();
    bool handleEvent( const Event event );
    
    virtual void onContentMeasureCompleted();
    virtual void onMeasureCompleted();
    virtual void onMeasureChanged();
    virtual void measureDisposition();
    virtual void populateLayout( std::vector<glm::vec2> dispositionPoints );
    void assignFrames( std::vector<glm::vec2> dispositionPoints );
    virtual void assignFrames(std::vector< glm::vec2 > dispositionPoints,
                              std::vector< std::shared_ptr< UIComponent >> components );
    
    std::vector< glm::vec2 > layoutDisposition();
    
protected:
    std::vector< std::shared_ptr< UIComponent > > components;
    
private:
    std::shared_ptr< Texture > backgroundTexture;

};

#endif /* _LAYOUT_H_ */
