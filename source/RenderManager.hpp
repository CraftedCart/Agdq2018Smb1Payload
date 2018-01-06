#ifndef GDQ_RENDER_RENDERMANAGER_HPP
#define GDQ_RENDER_RENDERMANAGER_HPP

#include "MeshSceneNode.hpp"

namespace RenderManager {
    extern GXRModeObj *screenMode;
    extern void *frameBuffer;
    extern vu8 readyForCopy;
    extern Mtx viewMatrix;
    extern Mtx projectionMatrix;
    extern guVector camera;
    extern guVector up;
    extern guVector look;
    extern GXColor backgroundColor;
    extern void *fifoBuffer;

    void init();
    void draw(SceneNode *rootNode);
    void drawSceneGraph(SceneNode *rootNode, Mtx transformMatrix);
    void drawMeshNode(MeshSceneNode *node, Mtx transformMatrix);
    void setLight(Mtx view, guVector lightPos, GXColor litCol, GXColor ambCol, GXColor matCol);
    void copyBuffers(u32 count __attribute__ ((unused)));
}

#endif

