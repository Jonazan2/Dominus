//
//  InputHandler.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 10/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef InputHandler_h
#define InputHandler_h

#include "Event.h"

class InputHandler {
public:
    virtual Event* poolEvent() = 0;
    virtual void init() = 0;
};

#endif /* InputHandler_h */
