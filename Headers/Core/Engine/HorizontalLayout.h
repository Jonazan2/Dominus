#ifndef __Dominus__HorizontalLayout__
#define __Dominus__HorizontalLayout__

#include <stdio.h>

#include "Layout.h"

class HorizontalLayout : public Layout {
public:
    HorizontalLayout();
    HorizontalLayout( int id );
    ~HorizontalLayout();
    
    void measureDisposition();
    
    std::vector< glm::vec2 > wrapDisposition();
    std::vector< glm::vec2 > weightDisposition();
};

#endif /* HORIZONTAL_LAYOUT_H_ */
