//
//  Camera.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 11/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
    Camera();
    ~Camera();
    
    glm::vec3 * getUp();
    glm::vec3 * getPosition();
    glm::vec3 * getTarget();
    glm::mat4 * getViewMatrix();
private:
    glm::mat4 viewMatrix;
    glm::vec3 up;
    glm::vec3 position;
    glm::vec3 target;
};

#endif /* Camera_h */
