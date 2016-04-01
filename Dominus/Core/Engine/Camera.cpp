//
//  Camera.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 11/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Camera.h"
#include <iostream>
Camera::Camera()
: viewMatrix( glm::mat4( 1 ) ),
position( glm::vec3 ( 0.0f, 0.0f, 10.0f ) ),
target( 0.0f, 0.0f, 0.0f ),
up( 0.0f, 1.0f, 0.0f ),
front( 0.0f, 0.0f, -1.0f ) {
    //TODO: Can these methods fail?, what is the result of an error here?
    viewMatrix = glm::lookAt( position, position + front, up );
    projectionMatrix = glm::perspective( 0.78f, (float)640/480, 0.01f, 100.0f );
    yaw = -90.0f;
    pitch = 0;
}

Camera::~Camera() {

}

void Camera::onUpdate() {
//    std::cout << "Camera position: "
//    << position.x << ", "
//    << position.y << ", "
//    <<position.z << std::endl;
    
    viewMatrix = glm::lookAt( position, position + front, up );
    rotationUpdate();
}

void Camera::rotationUpdate() {
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    
    glm::vec3 frontSaved = front;
    frontSaved.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    frontSaved.y = sin(glm::radians(pitch));
    frontSaved.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(frontSaved);
}

void Camera::onRestore( Scene* scene ) {
    
}

void Camera::onRender( Scene* scene ) {
    
}

void Camera::onRenderChildrends( Scene* scene ) {
    
}

void Camera::onPostRender( Scene* scene ) {

}
