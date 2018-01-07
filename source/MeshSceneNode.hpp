#ifndef GDQ_RENDER_MESHSCENENODE_HPP
#define GDQ_RENDER_MESHSCENENODE_HPP

#include "SceneNode.hpp"

class MeshSceneNode : public SceneNode {
    public:
        f32 *meshVertices;
        f32 *meshNormals;
        f32 *meshUvs;
        u8 *meshColors;
        bool useVertexColoring = false;
        u16 triangleCount;
        GXTexObj *texture = nullptr;
};

#endif

