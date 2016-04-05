#ifndef __Dominus_RenderScene_h__
#define __Dominus_RenderScene_h__

#include "GameScene.h"

class RenderScene : public GameScene {
public:
    RenderScene();
    ~RenderScene();
    
    void onUpdate( double delta );
    void onSceneCreated( Scene* scene );
    void onCosumeInput( std::vector< std::shared_ptr< Event > > );
    
    void onKeyDown( std::shared_ptr< Event > event );
    void onMouseDragged( const double xRel, const double yRel );
    
    void populateScene( Scene* scene );
    void populateUI( Scene* scene );
    
private:
    Scene* scene;
    
    bool upPressed;
    bool downPressed;
    bool leftPressed;
    bool rightPressed;
    bool rightClickPressed;

    float xSaved;
    float ySaved;
};

#endif /* _RENDER_SCENE_H_ */
