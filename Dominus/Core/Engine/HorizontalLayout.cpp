#include "HorizontalLayout.h"

HorizontalLayout::HorizontalLayout()
    : Layout() {
}

void HorizontalLayout::measureDisposition() {
    std::vector< glm::vec2 > dispositionPoints;
    switch ( params.disposition ) {
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

std::vector<glm::vec2> HorizontalLayout::wrapDisposition() {
    std::vector< glm::vec2 > dispositionPoints;
    for ( auto component :  components ) {
        glm::vec2 start = position;
        glm::vec2 end;
        //If there are a previous end point start from there
        if ( !dispositionPoints.empty() ) {
            start.x = dispositionPoints.back().x;
        }
        dispositionPoints.push_back( start );
        
        end.x = start.x + component->width;
        end.y = position.y + component->height;
        
        if ( end.y != ( position.y + height ) ) {
            end.y = position.y + height;
        }else if( end.x > ( position.x + width ) ) {
            //If height limit is reached add the last point adjusted and finish
            //all the other elements will not be drawed
            end.x = position.x + width;
            dispositionPoints.push_back( end );
            return dispositionPoints;
        }
        dispositionPoints.push_back(end);
    }
    return dispositionPoints;
}

std::vector<glm::vec2> HorizontalLayout::weightDisposition() {
    float weightSum = 0;
    float actualWeight = 0;
    for ( auto component :  components ) {
        if ( component->weight < 0 ) {
            component->weight = 0;
        }
        weightSum = weightSum + component->weight;
    }
    
    std::vector< glm::vec2 > dispositionPoints;
    for ( auto component : components ) {
        glm::vec2 start = position;
        glm::vec2 end;
        
        //If there are a previous end point start from there
        if ( !dispositionPoints.empty() ) {
            start.x = dispositionPoints.back().x;
        }
        
        dispositionPoints.push_back(start);
        if ( weightSum > 0 ) {
            actualWeight = component->weight / weightSum;
        }
        
        end.x = start.x + width * actualWeight;
        end.y = position.y + component->height;
        if ( end.y != ( position.y + height ) ) {
            end.y = position.y + height;
        }
        
        dispositionPoints.push_back( end );
    }
    return dispositionPoints;
}

HorizontalLayout::~HorizontalLayout() {}