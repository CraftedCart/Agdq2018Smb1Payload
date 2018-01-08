#include "verts.h"
#include "norms.h"
//#include "colors.h"
#include "texcoords.h"
#include "pallete_tpl.h"
#include "pallete.h"
#include "models/gdq2verts.h"
#include "models/gdq2norms.h"
#include "models/gdq2texcoords.h"
#include "pallete2_tpl.h"
#include "pallete2.h"
#include "models/spaceverts.h"
#include "models/spacenorms.h"
#include "models/spacetexcoords.h"
#include "space_tpl.h"
#include "space.h"
//#include "models/neogridverts.h"
//#include "models/neogridnorms.h"
//#include "models/neogridtexcoords.h"
//#include "neogrid_tpl.h"
//#include "neogrid.h"
#include "models/neolineverts.h"
#include "models/neolinenorms.h"
#include "models/neolinetexcoords.h"
#include "models/billboardverts.h"
#include "models/billboardnorms.h"
#include "models/billboardtexcoords.h"
#include "kappa_tpl.h"
#include "kappa.h"
#include "MeshSceneNode.hpp"
#include "GdqRender.hpp"
#include "RenderManager.hpp"
#include <gccore.h>
#include <algorithm>

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

        MeshSceneNode *gdq2Logo = new MeshSceneNode();
        gdq2Logo->meshVertices = MODEL_GDQ2_VERTS;
        gdq2Logo->meshNormals = MODEL_GDQ2_NORMS;
        gdq2Logo->meshUvs = MODEL_GDQ2_TEXCOORDS;
        gdq2Logo->triangleCount = 12600;
        GXTexObj pallete2Tex = RenderManager::loadTplTextureFromMemory(pallete2_tpl, pallete2_tpl_size, pallete2);
        gdq2Logo->texture = &pallete2Tex;
        gdq2Logo->getTransform().pos.z = -50.0f;
        gdq2Logo->getTransform().scl = {0.0f, 0.0f, 0.0f};
        gdq2Logo->setVisible(false);
        gdq2Logo->getTransform().rot.y = M_PI;
        scrollContainer->addChild(gdq2Logo);

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

        //MeshSceneNode *akappa = new MeshSceneNode();
        //akappa->meshVertices = MODEL_BILLBOARD_VERTS;
        //akappa->meshNormals = MODEL_BILLBOARD_NORMS;
        //akappa->meshUvs = MODEL_BILLBOARD_TEXCOORDS;
        //akappa->triangleCount = 2;
        //GXTexObj kappaTex = RenderManager::loadTplTextureFromMemory(kappa_tpl, kappa_tpl_size, kappa);
        //akappa->texture = &kappaTex;
        //akappa->getTransform().pos.z = -100.0f;
        //akappa->getTransform().scl = {20.0f, 20.0f, 20.0f};
        //akappa->isUnlit = true;
        //scrollContainer->addChild(akappa);

        MeshSceneNode *neoLine = new MeshSceneNode();
        neoLine->meshVertices = MODEL_NEOLINE_VERTS;
        neoLine->meshNormals = MODEL_NEOLINE_NORMS;
        neoLine->meshUvs = MODEL_NEOLINE_TEXCOORDS;
        neoLine->triangleCount = 12;
        neoLine->texture = &pallete2Tex;
        neoLine->getTransform().pos.z = 0.0f;
        neoLine->isUnlit = true;
        scrollContainer->addChild(neoLine);

        while (1) {
            if (gdqLogo != nullptr) {
                gdqLogo->getTransform().rot.y += 0.015;
                gdqLogo->getTransform().rot.z += 0.001;
                //gdqLogo->getTransform().rot.x += 0.001;
                gdq2Logo->getTransform().rot.y += 0.015;
                gdq2Logo->getTransform().rot.z += 0.001;

                if (gdq2Logo->getTransform().scl.x < 1.0f) {
                    gdqLogo->getTransform().scl.x += 0.01f;
                    gdqLogo->getTransform().scl.y += 0.01f;
                    gdqLogo->getTransform().scl.z += 0.01f;
                    gdq2Logo->getTransform().scl.x += 0.01f;
                    gdq2Logo->getTransform().scl.y += 0.01f;
                    gdq2Logo->getTransform().scl.z += 0.01f;
                } else {
                    gdqLogo->getTransform().scl.x = 1.0f;
                    gdqLogo->getTransform().scl.y = 1.0f;
                    gdqLogo->getTransform().scl.z = 1.0f;
                    gdq2Logo->getTransform().scl.x = 1.0f;
                    gdq2Logo->getTransform().scl.y = 1.0f;
                    gdq2Logo->getTransform().scl.z = 1.0f;
                }
            }

            //GDQ/GDQ2 logo flickering
            if (frameTime > 1200) {
                if (gdqLogo != nullptr) {
                    //Delete both GDQ logo nodes
                    std::vector<SceneNode*> &vec = scrollContainer->getChildren();
                    vec.erase(std::remove(vec.begin(), vec.end(), gdqLogo), vec.end());
                    delete gdqLogo;
                    gdqLogo = nullptr;
                    vec.erase(std::remove(vec.begin(), vec.end(), gdq2Logo), vec.end());
                    delete gdq2Logo;
                    gdq2Logo = nullptr;
                }
            } else if (frameTime > 136) {
                gdqLogo->setVisible(false);
                gdq2Logo->setVisible(true);

                static bool hasSetGdq2Scale = false;
                if (!hasSetGdq2Scale) {
                    gdq2Logo->getTransform().scl.x = 0.5f;
                    gdq2Logo->getTransform().scl.y = 0.5f;
                    gdq2Logo->getTransform().scl.z = 0.5f;
                    hasSetGdq2Scale = true;
                }
            } else if (frameTime > 128) {
                gdqLogo->setVisible(true);
                gdq2Logo->setVisible(false);
            } else if (frameTime > 120) {
                gdqLogo->setVisible(false);
                gdq2Logo->setVisible(true);
            } else if (frameTime > 108) {
                gdqLogo->setVisible(true);
                gdq2Logo->setVisible(false);
            } else if (frameTime > 100) {
                gdqLogo->setVisible(false);
                gdq2Logo->setVisible(true);
            } else if (frameTime > 68) {
                gdqLogo->setVisible(true);
                gdq2Logo->setVisible(false);
            } else if (frameTime > 60) {
                gdqLogo->setVisible(false);
                gdq2Logo->setVisible(true);
            }

            if (frameTime > 600) {
                scrollContainer->getTransform().pos.y += 0.2f;
            }

            RenderManager::draw(rootNode);

            PAD_Read(pads);
            if (pads[0].button & PAD_BUTTON_START) {
                //void (*reload)() = (void(*)()) 0x80001800;
                //reload();
                return 0;
            }

            frameTime++;
        }
        return 0;
    }
}

