#ifndef __Dominus__Frame_h__
#define __Dominus__Frame_h__

#include <glm/glm.hpp>

// TODO: this class can be turn into a struct since it doesn't have behaviour
class Frame {
public:
    Frame() : width(0), height(0) {}
    ~Frame() {}
    
    glm::vec2 position;
    int width;
    int height;
};

#endif /* _FRAME_H_ */
