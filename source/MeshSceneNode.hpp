#ifndef GDQ_RENDER_MESHSCENENODE_HPP
#define GDQ_RENDER_MESHSCENENODE_HPP

#include "SceneNode.hpp"

class MeshSceneNode : public SceneNode {
    public:
        f32 *meshVertices;
        f32 *meshNormals;
        u16 triangleCount;
};

#endif

