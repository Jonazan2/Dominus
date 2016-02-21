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
                    position( glm::vec3 ( 0.0f, 0.0f, 10.0f ) ),
                    target( 0.0f, 0.0f, 0.0f ),
                    up( 0.0f, 1.0f, 0.0f ),
                    front( 0.0f, 0.0f, -1.0f ){
    viewMatrix = glm::lookAt( position, position + front, up );
}

Camera::~Camera() {

}

void Camera::update() {
    viewMatrix = glm::lookAt( position, position + front, up );
}