#include "verts.h"
#include "norms.h"
#include "MeshSceneNode.hpp"
#include "GdqRender.hpp"
#include "RenderManager.hpp"

namespace GdqRender {
    SceneNode *rootNode;

    int execute() {
        PADStatus pads[4];
        RenderManager::init();

        //Set up the scene graph
        rootNode = new SceneNode();

        MeshSceneNode *gdqLogo = new MeshSceneNode();
        gdqLogo->meshVertices = MODEL_VERTS;
        gdqLogo->meshNormals = MODEL_NORMS;
        gdqLogo->triangleCount = 6616;
        gdqLogo->getTransform().pos.z = -50.0f;
        rootNode->addChild(gdqLogo);

        while (1) {
            RenderManager::draw(rootNode);

            PAD_Read(pads);
            if (pads[0].button & PAD_BUTTON_START) {
                void (*reload)() = (void(*)()) 0x80001800;
                reload();
            }
        }
        return 0;
    }
}

