#ifndef __Dominus__VerticalLayout__
#define __Dominus__VerticalLayout__

#include <stdio.h>
#include <vector>

#include "Layout.h"

class VerticalLayout : public Layout {
public:
    VerticalLayout();
    virtual ~VerticalLayout();
    
    void measureDisposition();
    
    std::vector< glm::vec2 > wrapDisposition();
    std::vector< glm::vec2 > weightDisposition();
};

#endif /* _VERTICAL_LAYOUT_H_ */
