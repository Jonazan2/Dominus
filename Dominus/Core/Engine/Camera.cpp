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
    //TODO: Can these methods fail?, what is the result of an error here?
    viewMatrix = glm::lookAt( position, position + front, up );
    projectionMatrix = glm::perspective( 0.78f, (float)640/480, 0.01f, 100.0f );
}

Camera::~Camera() {

}

void Camera::onUpdate() {
    viewMatrix = glm::lookAt( position, position + front, up );
}

void Camera::onRestore( Scene* scene ) {
    
}

void Camera::onRender( Scene* scene ) {
    
}

void Camera::onRenderChildrends( Scene* scene ) {
    
}

void Camera::onPostRender( Scene* scene ) {

}
