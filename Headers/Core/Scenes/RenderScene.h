#ifndef RenderScene_h
#define RenderScene_h

#include "GameScene.h"
#include "Log.hpp"
#include "HorizontalLayout.h"
#include "VerticalLayout.h"
#include "Button.h"
#include "PngTextureLoader.h"
#include "GLGpuTexture.h"
#include "ObjLoader.h"
#include "MapBuilder.h"
#include "MomoNode.h"
#include "MemoryUtils.h"
#include "Log.hpp"
#include "HorizontalLayout.h"
#include "VerticalLayout.h"
#include "Button.h"
#include "PngTextureLoader.h"
#include "GLGpuTexture.h"
#include "ObjLoader.h"
#include "MapBuilder.h"
#include "MomoNode.h"

class RenderScene : public GameScene {
public:
    RenderScene();
    ~RenderScene();
    
    void onUpdate( double delta );
    void onSceneCreated( Scene* scene );
    void onCosumeInput( std::vector<std::shared_ptr<Event>>* );
    
    void onKeyDown( std::shared_ptr<Event> event );
    void onMouseDragged( double xRel, double yRel );
    
    void populateScene( Scene* scene );
    void populateUI( Scene* scene );

    Scene* scene;
    
    bool upPressed;
    bool downPressed;
    bool leftPressed;
    bool rightPressed;
    bool rightClickPressed;

    float xSaved;
    float ySaved;
};

#endif /* RenderScene_h */
