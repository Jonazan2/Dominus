//
//  Event.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 20/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Event.h"

Event::Event()
                :   x( 0 ),
                    y( 0 ),
                    xRelative( 0 ),
                    yRelative( 0 ),
                    keyCode( 0 ),
                    type( EVENT_NONE ),
                    consumed( false ){

}

Event::Event( Event* event ) {
    this->x = event->x;
    this->y = event->y;
    this->xRelative = event->xRelative;
    this->yRelative = event->yRelative;
    this->keyCode = event->keyCode;
    this->type = event->type;
}

Event::~Event() {

}