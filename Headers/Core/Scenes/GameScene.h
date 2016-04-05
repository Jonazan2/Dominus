#ifndef __Dominus_GameScene_h__
#define __Dominus_GameScene_h__

#include <vector>
#include <memory>

#include "Scene.h"
#include "Event.h"

class GameScene {
public:
    virtual void onSceneCreated( Scene* scene ) = 0;
    virtual void onUpdate( double delta ) = 0;
    virtual void onCosumeInput( std::vector< std::shared_ptr< Event > > ) = 0;
};

#endif /* _GAME_SCENE_H_ */
