#ifndef __Dominus_RenderState_h__
#define __Dominus_RenderState_h__

#include "Node.h"

class RenderState {
public:
    virtual void init( ) = 0;
    virtual void updateCamera( glm::mat4 camera ) = 0;
    virtual void updateProjection( glm::mat4 projection ) = 0;
    virtual void updateLightSource( glm::vec3 light ) = 0;
    virtual void load( std::vector< std::shared_ptr< Node > > renderBatch ) = 0;
    virtual void draw( std::vector< std::shared_ptr< Node > > renderBatch ) = 0;
};

#endif /* _RENDER_STATE_H_ */
