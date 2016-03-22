//
//  Camera.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 11/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include "INode.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera : public INode{
public:
    Camera();
    ~Camera();
    
    void update();
    
    void onRestore( Scene* scene );
    void onRender( Scene* scene );
    void onRenderChildrends( Scene* scene );
    void onPostRender( Scene* scene ) ;
    
    glm::mat4 viewMatrix;
    glm::vec3 up;
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 target;
};

#endif /* Camera_h */
