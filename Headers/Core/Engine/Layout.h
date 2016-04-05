#ifndef __Dominus__Layout__
#define __Dominus__Layout__

#include <stdio.h>
#include <vector>

#include "Params.h"
#include "UIComponent.h"
#include "Event.h"

class Layout : public UIComponent {
public:
    Layout();
    virtual ~Layout();
    
    virtual void addComponent( UIComponent* component) ;
    void render( Renderer* renderer );
    void setBackground( Texture* background );
    UIComponent* matchEvent( glm::vec2 position );
    void cleanComponents();
    void resize( float widthRatio, float heightRatio );
    void resetSize();
    bool handleEvent(const Event event);
    
    virtual void onContentMeasureCompleted();
    virtual void onMeasureCompleted();
    virtual void onMeasureChanged();
    virtual void measureDisposition();
    virtual void populateLayout( std::vector<glm::vec2> dispositionPoints );
    void assignFrames( std::vector<glm::vec2> dispositionPoints );
    virtual void assignFrames(std::vector< glm::vec2 > dispositionPoints,
                              std::vector< UIComponent* > components );
    
    std::vector< glm::vec2 > layoutDisposition();
    
protected:
    std::vector< UIComponent*> components;
    
private:
    Texture* background;

};

#endif /* LAYOUT_H_ */
