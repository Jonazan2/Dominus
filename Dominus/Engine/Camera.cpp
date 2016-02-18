//
//  Camera.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 11/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Camera.h"

Camera::Camera()
                :   viewMatrix( glm::mat4( 1 ) ),
                    position( glm::vec3 ( 0.0f, 0.0f, -15.0f ) ),
                    target( 0.0f, 0.0f, 0.0f ),
                    up( 0.0f, 1.0f, 0.0f ) {
    viewMatrix = glm::lookAt( position, target, up );
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