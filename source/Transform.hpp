#ifndef GDQ_RENDER_TRANSFORM_HPP
#define GDQ_RENDER_TRANSFORM_HPP

#include <gccore.h>

class Transform {
    public:
        guVector pos = {0.0f, 0.0f, 0.0f};
        guVector rot = {0.0f, 0.0f, 0.0f};
        guVector scl = {1.0f, 1.0f, 1.0f};
};

#endif

