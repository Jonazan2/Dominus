#ifndef __Dominus_InputHandler_h__
#define __Dominus_InputHandler_h__

#include <vector>
#include <memory>

#include "Event.h"

class InputHandler {
public:
    virtual std::vector< std::shared_ptr< Event > > poolEvents() = 0;
    virtual void init() = 0;
};

#endif /* _INPUT_HANDLER_H_ */
