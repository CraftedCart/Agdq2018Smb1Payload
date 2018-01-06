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
        gdqLogo->getTransform().scl = {0.0f, 0.0f, 0.0f};
        rootNode->addChild(gdqLogo);

        while (1) {
            gdqLogo->getTransform().rot.y += 0.025;

            if (gdqLogo->getTransform().scl.x < 1.0f) {
                gdqLogo->getTransform().scl.x += 0.01f;
                gdqLogo->getTransform().scl.y += 0.01f;
                gdqLogo->getTransform().scl.z += 0.01f;
            } else {
                gdqLogo->getTransform().scl.x = 1.0f;
                gdqLogo->getTransform().scl.y = 1.0f;
                gdqLogo->getTransform().scl.z = 1.0f;
            }

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

