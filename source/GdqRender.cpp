#include "verts.h"
#include "norms.h"
//#include "colors.h"
#include "texcoords.h"
#include "pallete_tpl.h"
#include "pallete.h"
#include "models/spaceverts.h"
#include "models/spacenorms.h"
#include "models/spacetexcoords.h"
#include "space_tpl.h"
#include "space.h"
#include "MeshSceneNode.hpp"
#include "GdqRender.hpp"
#include "RenderManager.hpp"
#include <gccore.h>

namespace GdqRender {
    SceneNode *rootNode;

    int execute() {
        PADStatus pads[4];
        RenderManager::init();

        u16 frameTime = 0;

        //Set up the scene graph
        rootNode = new SceneNode();

        SceneNode *scrollContainer = new SceneNode();
        rootNode->addChild(scrollContainer);

        MeshSceneNode *gdqLogo = new MeshSceneNode();
        gdqLogo->meshVertices = MODEL_VERTS;
        gdqLogo->meshNormals = MODEL_NORMS;
        gdqLogo->meshUvs = MODEL_TEXCOORDS;
        //gdqLogo->meshColors = MODEL_COLORS;
        //gdqLogo->useVertexColoring = true;
        gdqLogo->triangleCount = 6616;
        GXTexObj palleteTex = RenderManager::loadTplTextureFromMemory(pallete_tpl, pallete_tpl_size, pallete);
        gdqLogo->texture = &palleteTex;
        gdqLogo->getTransform().pos.z = -50.0f;
        gdqLogo->getTransform().scl = {0.0f, 0.0f, 0.0f};
        scrollContainer->addChild(gdqLogo);

        MeshSceneNode *spaceBg = new MeshSceneNode();
        spaceBg->meshVertices = MODEL_SPACE_VERTS;
        spaceBg->meshNormals = MODEL_SPACE_NORMS;
        spaceBg->meshUvs = MODEL_SPACE_TEXCOORDS;
        spaceBg->triangleCount = 2;
        GXTexObj spaceTex = RenderManager::loadTplTextureFromMemory(space_tpl, space_tpl_size, space);
        spaceBg->texture = &spaceTex;
        spaceBg->getTransform().pos.z = -300.0f;
        spaceBg->isUnlit = true;
        scrollContainer->addChild(spaceBg);

        while (1) {
            gdqLogo->getTransform().rot.y += 0.022;
            gdqLogo->getTransform().rot.z += 0.001;
            //gdqLogo->getTransform().rot.x += 0.001;

            if (gdqLogo->getTransform().scl.x < 1.0f) {
                gdqLogo->getTransform().scl.x += 0.01f;
                gdqLogo->getTransform().scl.y += 0.01f;
                gdqLogo->getTransform().scl.z += 0.01f;
            } else {
                gdqLogo->getTransform().scl.x = 1.0f;
                gdqLogo->getTransform().scl.y = 1.0f;
                gdqLogo->getTransform().scl.z = 1.0f;
            }

            if (frameTime > 600) {
                scrollContainer->getTransform().pos.y += 0.2f;
            }

            if (frameTime > 1200) {
                gdqLogo->triangleCount = 0; //For performance
            }

            RenderManager::draw(rootNode);

            PAD_Read(pads);
            if (pads[0].button & PAD_BUTTON_START) {
                void (*reload)() = (void(*)()) 0x80001800;
                reload();
            }

            frameTime++;
        }
        return 0;
    }
}

