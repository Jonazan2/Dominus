#include "VerticalLayout.h"

//TODO building with and undefined id
VerticalLayout::VerticalLayout()
    : Layout() {
}

void VerticalLayout::measureDisposition() {
    std::vector< glm::vec2 > dispositionPoints;
    switch (params.disposition) {
        case WRAP_DISPOSITION:
            dispositionPoints = wrapDisposition();
            break;
        case WEIGHT_DISPOSITION:
            dispositionPoints = weightDisposition();
            break;
        default:
            break;
    }
    assignFrames( dispositionPoints );
    populateLayout( dispositionPoints );
}

std::vector< glm::vec2 > VerticalLayout::wrapDisposition() {
    std::vector< glm::vec2 > dispositionPoints;
    for ( std::shared_ptr< UIComponent > component :  components ) {
        glm::vec2 start = position;
        glm::vec2 end;
        //If there are a previous end point start from there
        if ( !dispositionPoints.empty() ) {
            start.y = dispositionPoints.back().y;
        }
        dispositionPoints.push_back(start);
        
        end.x = position.x + component->getWidth();
        end.y = start.y + component->getHeight();

        if ( end.x != ( position.x + width ) ) {
            end.x = position.x + width;
        } else if ( end.y > ( position.y + height ) ){
            //If height limit is reached add the last point adjusted and finish
            //all the other elements will not be drawed
            end.y = position.y + height;
            dispositionPoints.push_back( end );
            return dispositionPoints;
        }
        dispositionPoints.push_back(end);
    }
    return dispositionPoints;
}

std::vector< glm::vec2 > VerticalLayout::weightDisposition() {
    float weightSum = 0;
    float actualWeight = 0;
    for ( std::shared_ptr< UIComponent > component :  components ) {
        if ( component->getWeight() < 0 ) {
            component->setWeight( 0 );
        }
        weightSum = weightSum + component->getWeight();
    }
    
    std::vector<glm::vec2 > dispositionPoints;
    for ( std::shared_ptr< UIComponent > component : components ) {
        glm::vec2 start = position;
        glm::vec2 end;
        
        //If there are a previous end point start from there
        if ( !dispositionPoints.empty() ) {
            start.y = dispositionPoints.back().y;
        }
        
        dispositionPoints.push_back( start );
        if ( weightSum > 0 ) {
            actualWeight = component->getWeight() / weightSum;
        }
        
        end.x = position.x + component->getWidth();
        end.y = start.y + height * actualWeight;
        if ( end.x != ( position.x + width ) ) {
            end.x = position.x + width;
        }
        dispositionPoints.push_back( end );
    }
    return dispositionPoints;
}

VerticalLayout::~VerticalLayout() {}