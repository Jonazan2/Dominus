//
//  VerticalLayout.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 8/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "VerticalLayout.h"

//TODO building with and undefined id
VerticalLayout::VerticalLayout() : Layout()
{
    
}

VerticalLayout::~VerticalLayout()
{

}

void VerticalLayout::measureDisposition()
{
    std::vector<glm::vec2> dispositionPoints;
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
    assignFrames(dispositionPoints);
    populateLayout(dispositionPoints);
}

std::vector<glm::vec2> VerticalLayout::wrapDisposition()
{
    std::vector<glm::vec2> dispositionPoints;
    for (UIComponent* component :  components) {
        glm::vec2 start = position;
        glm::vec2 end;
        //If there are a previous end point start from there
        if (!dispositionPoints.empty()) {
            start.y = dispositionPoints.back().y;
        }
        dispositionPoints.push_back(start);
        
        end.x = position.x + component->width;
        end.y = start.y + component->height;

        if (end.x != position.x + width) {
            end.x = position.x + width;
        }else if(end.y > position.y + height){
            //If height limit is reached add the last point adjusted and finish
            //all the other elements will not be drawed
            end.y = position.y + height;
            dispositionPoints.push_back(end);
            return dispositionPoints;
        }
        dispositionPoints.push_back(end);
    }
    return dispositionPoints;
}

std::vector<glm::vec2> VerticalLayout::weightDisposition()
{
    std::vector<glm::vec2> dispositionPoints;
    float weightSum = 0;
    float actualWeight = 0;
    for (UIComponent* component :  components) {
        if (component->weight < 0) {
            component->weight = 0;
        }
        weightSum = weightSum + component->weight;
    }
    
    for (UIComponent* component : components) {
        glm::vec2 start = position;
        glm::vec2 end;
        
        //If there are a previous end point start from there
        if (!dispositionPoints.empty()) {
            start.y = dispositionPoints.back().y;
        }
        
        dispositionPoints.push_back(start);
        if (weightSum > 0) {
            actualWeight = component->weight / weightSum;
        }
        
        end.x = position.x + component->width;
        end.y = start.y + height * actualWeight;
        if (end.x != position.x + width) {
            end.x = position.x + width;
        }
        dispositionPoints.push_back(end);
    }
    return dispositionPoints;
}
