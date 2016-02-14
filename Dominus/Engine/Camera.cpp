//
//  Camera.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 11/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Camera.h"

Camera::Camera()
                :   viewMatrix( 1 ),
                    position( 0 ),
                    target( 0 ),
                    up( 0 ) {

}

Camera::~Camera() {

}

glm::vec3 * Camera::getPosition() {
    return &position;
}

glm::vec3 * Camera::getTarget() {
    return &target;
}

glm::vec3 * Camera::getUp() {
    return &up;
}

glm::mat4 * Camera::getViewMatrix() {
    return &viewMatrix;
}