#ifndef GDQ_RENDER_GDQRENDER_HPP
#define GDQ_RENDER_GDQRENDER_HPP

#include "SceneNode.hpp"
#include <gccore.h>

namespace GdqRender {
    extern SceneNode *rootNode;

    int execute();
    void updateScreen(Mtx viewMatrix);
}

#endif

