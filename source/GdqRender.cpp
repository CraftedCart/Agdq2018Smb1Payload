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
#include "models/credits/tasauthorsheadverts.h"
#include "models/credits/tasauthorsheadnorms.h"
#include "models/credits/tasauthorsheadtexcoords.h"
#include "models/credits/tasauthorsbodyverts.h"
#include "models/credits/tasauthorsbodynorms.h"
#include "models/credits/tasauthorsbodytexcoords.h"
#include "models/credits/revengheadverts.h"
#include "models/credits/revengheadnorms.h"
#include "models/credits/revengheadtexcoords.h"
#include "models/credits/revengbodyverts.h"
#include "models/credits/revengbodynorms.h"
#include "models/credits/revengbodytexcoords.h"
#include "models/credits/customreplayheadverts.h"
#include "models/credits/customreplayheadnorms.h"
#include "models/credits/customreplayheadtexcoords.h"
#include "models/credits/customreplaybodyverts.h"
#include "models/credits/customreplaybodynorms.h"
#include "models/credits/customreplaybodytexcoords.h"
#include "models/credits/tooldevheadverts.h"
#include "models/credits/tooldevheadnorms.h"
#include "models/credits/tooldevheadtexcoords.h"
#include "models/credits/tooldevbodyverts.h"
#include "models/credits/tooldevbodynorms.h"
#include "models/credits/tooldevbodytexcoords.h"
#include "models/credits/payloadheadverts.h"
#include "models/credits/payloadheadnorms.h"
#include "models/credits/payloadheadtexcoords.h"
#include "models/credits/payloadbodyverts.h"
#include "models/credits/payloadbodynorms.h"
#include "models/credits/payloadbodytexcoords.h"
#include "models/credits/presentersheadverts.h"
#include "models/credits/presentersheadnorms.h"
#include "models/credits/presentersheadtexcoords.h"
#include "models/credits/presentersbodyverts.h"
#include "models/credits/presentersbodynorms.h"
#include "models/credits/presentersbodytexcoords.h"
#include "models/credits/endingverts.h"
#include "models/credits/endingnorms.h"
#include "models/credits/endingtexcoords.h"
#include "MeshSceneNode.hpp"
#include "EmitterSceneNode.hpp"
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

        ParticleSceneNode *akappa = new ParticleSceneNode();
        akappa->meshVertices = MODEL_BILLBOARD_VERTS;
        akappa->meshNormals = MODEL_BILLBOARD_NORMS;
        akappa->meshUvs = MODEL_BILLBOARD_TEXCOORDS;
        akappa->triangleCount = 2;
        GXTexObj kappaTex = RenderManager::loadTplTextureFromMemory(kappa_tpl, kappa_tpl_size, kappa);
        akappa->texture = &kappaTex;
        akappa->getTransform().pos.z = -150.0f;
        akappa->getTransform().scl = {15.0f, 15.0f, 15.0f};
        akappa->isUnlit = true;
        akappa->acceleration = {0.0f, -0.05f, 0.0f};
        akappa->lifetime = 300;
        akappa->scaleMultiplier = 0.99f;

        EmitterSceneNode *emitter = new EmitterSceneNode();
        emitter->particleMesh = akappa;
        scrollContainer->addChild(emitter);

        MeshSceneNode *neoLine = new MeshSceneNode();
        neoLine->meshVertices = MODEL_NEOLINE_VERTS;
        neoLine->meshNormals = MODEL_NEOLINE_NORMS;
        neoLine->meshUvs = MODEL_NEOLINE_TEXCOORDS;
        neoLine->triangleCount = 12;
        neoLine->texture = &pallete2Tex;
        neoLine->isUnlit = true;
        scrollContainer->addChild(neoLine);

        //////////////// Credits ////////////////

        SceneNode *tasAuthors = new SceneNode();
        tasAuthors->getTransform().pos.x = -40.0f;
        tasAuthors->getTransform().pos.y = -105.0f;
        tasAuthors->getTransform().pos.z = -50.0f;
        tasAuthors->interpTargetTransform = tasAuthors->getTransform();
        tasAuthors->getTransform().pos.x = -120.0f;
        tasAuthors->getTransform().rot.y = M_PI;
        tasAuthors->setVisible(false);
        scrollContainer->addChild(tasAuthors);

        MeshSceneNode *tasAuthorsHead = new MeshSceneNode();
        tasAuthorsHead->meshVertices = MODEL_TASAUTHORSHEAD_VERTS;
        tasAuthorsHead->meshNormals = MODEL_TASAUTHORSHEAD_NORMS;
        tasAuthorsHead->meshUvs = MODEL_TASAUTHORSHEAD_TEXCOORDS;
        tasAuthorsHead->triangleCount = 2511;
        tasAuthorsHead->texture = &pallete2Tex;
        tasAuthors->addChild(tasAuthorsHead);

        MeshSceneNode *tasAuthorsBody = new MeshSceneNode();
        tasAuthorsBody->meshVertices = MODEL_TASAUTHORSBODY_VERTS;
        tasAuthorsBody->meshNormals = MODEL_TASAUTHORSBODY_NORMS;
        tasAuthorsBody->meshUvs = MODEL_TASAUTHORSBODY_TEXCOORDS;
        tasAuthorsBody->triangleCount = 4855;
        tasAuthorsBody->texture = &pallete2Tex;
        tasAuthorsBody->getTransform().pos.x = -256.0f;
        tasAuthors->addChild(tasAuthorsBody);

        SceneNode *revEng = new SceneNode();
        revEng->getTransform().pos.x = -40.0f;
        revEng->getTransform().pos.y = -140.0f;
        revEng->getTransform().pos.z = -50.0f;
        revEng->interpTargetTransform = revEng->getTransform();
        revEng->getTransform().pos.x = -120.0f;
        revEng->getTransform().rot.y = M_PI;
        revEng->setVisible(false);
        scrollContainer->addChild(revEng);

        MeshSceneNode *revEngHead = new MeshSceneNode();
        revEngHead->meshVertices = MODEL_REVENGHEAD_VERTS;
        revEngHead->meshNormals = MODEL_REVENGHEAD_NORMS;
        revEngHead->meshUvs = MODEL_REVENGHEAD_TEXCOORDS;
        revEngHead->triangleCount = 5282;
        revEngHead->texture = &pallete2Tex;
        revEng->addChild(revEngHead);

        MeshSceneNode *revEngBody = new MeshSceneNode();
        revEngBody->meshVertices = MODEL_REVENGBODY_VERTS;
        revEngBody->meshNormals = MODEL_REVENGBODY_NORMS;
        revEngBody->meshUvs = MODEL_REVENGBODY_TEXCOORDS;
        revEngBody->triangleCount = 10329;
        revEngBody->texture = &pallete2Tex;
        revEngBody->getTransform().pos.x = -256.0f;
        revEng->addChild(revEngBody);

        SceneNode *customReplay = new SceneNode();
        customReplay->getTransform().pos.x = -40.0f;
        customReplay->getTransform().pos.y = -202.0f;
        customReplay->getTransform().pos.z = -50.0f;
        customReplay->interpTargetTransform = customReplay->getTransform();
        customReplay->getTransform().pos.x = -120.0f;
        customReplay->getTransform().rot.y = M_PI;
        customReplay->setVisible(false);
        scrollContainer->addChild(customReplay);

        MeshSceneNode *customReplayHead = new MeshSceneNode();
        customReplayHead->meshVertices = MODEL_CUSTOMREPLAYHEAD_VERTS;
        customReplayHead->meshNormals = MODEL_CUSTOMREPLAYHEAD_NORMS;
        customReplayHead->meshUvs = MODEL_CUSTOMREPLAYHEAD_TEXCOORDS;
        customReplayHead->triangleCount = 5792;
        customReplayHead->texture = &pallete2Tex;
        customReplay->addChild(customReplayHead);

        MeshSceneNode *customReplayBody = new MeshSceneNode();
        customReplayBody->meshVertices = MODEL_CUSTOMREPLAYBODY_VERTS;
        customReplayBody->meshNormals = MODEL_CUSTOMREPLAYBODY_NORMS;
        customReplayBody->meshUvs = MODEL_CUSTOMREPLAYBODY_TEXCOORDS;
        customReplayBody->triangleCount = 16081;
        customReplayBody->texture = &pallete2Tex;
        customReplayBody->getTransform().pos.x = -256.0f;
        customReplay->addChild(customReplayBody);

        SceneNode *toolDev = new SceneNode();
        toolDev->getTransform().pos.x = -40.0f;
        toolDev->getTransform().pos.y = -282.0f;
        toolDev->getTransform().pos.z = -50.0f;
        toolDev->interpTargetTransform = toolDev->getTransform();
        toolDev->getTransform().pos.x = -120.0f;
        toolDev->getTransform().rot.y = M_PI;
        toolDev->setVisible(false);
        scrollContainer->addChild(toolDev);

        MeshSceneNode *toolDevHead = new MeshSceneNode();
        toolDevHead->meshVertices = MODEL_TOOLDEVHEAD_VERTS;
        toolDevHead->meshNormals = MODEL_TOOLDEVHEAD_NORMS;
        toolDevHead->meshUvs = MODEL_TOOLDEVHEAD_TEXCOORDS;
        toolDevHead->triangleCount = 3854;
        toolDevHead->texture = &pallete2Tex;
        toolDev->addChild(toolDevHead);

        MeshSceneNode *toolDevBody = new MeshSceneNode();
        toolDevBody->meshVertices = MODEL_TOOLDEVBODY_VERTS;
        toolDevBody->meshNormals = MODEL_TOOLDEVBODY_NORMS;
        toolDevBody->meshUvs = MODEL_TOOLDEVBODY_TEXCOORDS;
        toolDevBody->triangleCount = 14330;
        toolDevBody->texture = &pallete2Tex;
        toolDevBody->getTransform().pos.x = -256.0f;
        toolDev->addChild(toolDevBody);

        SceneNode *payload = new SceneNode();
        payload->getTransform().pos.x = -40.0f;
        payload->getTransform().pos.y = -336.0f;
        payload->getTransform().pos.z = -50.0f;
        payload->interpTargetTransform = payload->getTransform();
        payload->getTransform().pos.x = -120.0f;
        payload->getTransform().rot.y = M_PI;
        payload->setVisible(false);
        scrollContainer->addChild(payload);

        MeshSceneNode *payloadHead = new MeshSceneNode();
        payloadHead->meshVertices = MODEL_PAYLOADHEAD_VERTS;
        payloadHead->meshNormals = MODEL_PAYLOADHEAD_NORMS;
        payloadHead->meshUvs = MODEL_PAYLOADHEAD_TEXCOORDS;
        payloadHead->triangleCount = 7956;
        payloadHead->texture = &pallete2Tex;
        payload->addChild(payloadHead);

        MeshSceneNode *payloadBody = new MeshSceneNode();
        payloadBody->meshVertices = MODEL_PAYLOADBODY_VERTS;
        payloadBody->meshNormals = MODEL_PAYLOADBODY_NORMS;
        payloadBody->meshUvs = MODEL_PAYLOADBODY_TEXCOORDS;
        payloadBody->triangleCount = 3529;
        payloadBody->texture = &pallete2Tex;
        payloadBody->getTransform().pos.x = -256.0f;
        payload->addChild(payloadBody);

        SceneNode *presenters = new SceneNode();
        presenters->getTransform().pos.x = -40.0f;
        presenters->getTransform().pos.y = -376.0f;
        presenters->getTransform().pos.z = -50.0f;
        presenters->interpTargetTransform = presenters->getTransform();
        presenters->getTransform().pos.x = -120.0f;
        presenters->getTransform().rot.y = M_PI;
        presenters->setVisible(false);
        scrollContainer->addChild(presenters);

        MeshSceneNode *presentersHead = new MeshSceneNode();
        presentersHead->meshVertices = MODEL_PRESENTERSHEAD_VERTS;
        presentersHead->meshNormals = MODEL_PRESENTERSHEAD_NORMS;
        presentersHead->meshUvs = MODEL_PRESENTERSHEAD_TEXCOORDS;
        presentersHead->triangleCount = 3419;
        presentersHead->texture = &pallete2Tex;
        presenters->addChild(presentersHead);

        MeshSceneNode *presentersBody = new MeshSceneNode();
        presentersBody->meshVertices = MODEL_PRESENTERSBODY_VERTS;
        presentersBody->meshNormals = MODEL_PRESENTERSBODY_NORMS;
        presentersBody->meshUvs = MODEL_PRESENTERSBODY_TEXCOORDS;
        presentersBody->triangleCount = 3434;
        presentersBody->texture = &pallete2Tex;
        presentersBody->getTransform().pos.x = -256.0f;
        presenters->addChild(presentersBody);

        MeshSceneNode *endingBody = new MeshSceneNode();
        endingBody->meshVertices = MODEL_ENDING_VERTS;
        endingBody->meshNormals = MODEL_ENDING_NORMS;
        endingBody->meshUvs = MODEL_ENDING_TEXCOORDS;
        endingBody->triangleCount = 12484;
        endingBody->texture = &pallete2Tex;
        endingBody->getTransform().pos.x = -35.0f;
        endingBody->getTransform().pos.y = -200.0f;
        endingBody->getTransform().scl.x = 0.4f;
        endingBody->getTransform().scl.y = 0.4f;
        endingBody->getTransform().scl.z = 0.4f;
        endingBody->setVisible(false);
        endingBody->isUnlit = true;
        scrollContainer->addChild(endingBody);

        //////////////// End Credits ////////////////

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

            //Credits
            //Hiding
            if (frameTime == 2900) {
                presenters->setVisible(false);
            } else if (frameTime == 2700) {
                payload->setVisible(false);
            } else if (frameTime == 2500) {
                toolDev->setVisible(false);
            } else if (frameTime == 2400) {
                customReplay->setVisible(false);
            } else if (frameTime == 2000) {
                revEng->setVisible(false);
            } else if (frameTime == 1600) {
                tasAuthors->setVisible(false);
            }

            //Showing
            if (frameTime == 2300) {
                endingBody->setVisible(true);
            } else if (frameTime == 2100) {
                presenters->interpSpeed = 0.02f;
                presentersBody->interpSpeed = 0.02f;
                presenters->setVisible(true);
            } else if (frameTime == 1900) {
                payload->interpSpeed = 0.02f;
                payloadBody->interpSpeed = 0.02f;
                payload->setVisible(true);
            } else if (frameTime == 1600) {
                toolDev->interpSpeed = 0.02f;
                toolDevBody->interpSpeed = 0.02f;
                toolDev->setVisible(true);
            } else if (frameTime == 1350) {
                customReplay->interpSpeed = 0.02f;
                customReplayBody->interpSpeed = 0.02f;
                customReplay->setVisible(true);
            } else if (frameTime == 1000) {
                revEng->interpSpeed = 0.02f;
                revEngBody->interpSpeed = 0.02f;
                revEng->setVisible(true);
            } else if (frameTime == 800) {
                tasAuthors->interpSpeed = 0.02f;
                tasAuthorsBody->interpSpeed = 0.02f;
                tasAuthors->setVisible(true);
            }

            //GDQ/GDQ2 logo flickering from this if onwards
            if (frameTime == 1200) {
                //Delete both GDQ logo nodes
                std::vector<SceneNode*> &vec = scrollContainer->getChildren();
                vec.erase(std::remove(vec.begin(), vec.end(), gdqLogo), vec.end());
                delete gdqLogo;
                gdqLogo = nullptr;
                vec.erase(std::remove(vec.begin(), vec.end(), gdq2Logo), vec.end());
                delete gdq2Logo;
                gdq2Logo = nullptr;
            } else if (frameTime == 900) {
                //Remove the particle emitter after 5 iterations
                std::vector<SceneNode*> &vec = scrollContainer->getChildren();
                vec.erase(std::remove(vec.begin(), vec.end(), emitter), vec.end());
                delete emitter;
            } else if (frameTime == 136) {
                gdqLogo->setVisible(false);
                gdq2Logo->setVisible(true);

                gdq2Logo->getTransform().scl.x = 0.5f;
                gdq2Logo->getTransform().scl.y = 0.5f;
                gdq2Logo->getTransform().scl.z = 0.5f;
            } else if (frameTime == 128) {
                gdqLogo->setVisible(true);
                gdq2Logo->setVisible(false);
            } else if (frameTime == 120) {
                gdqLogo->setVisible(false);
                gdq2Logo->setVisible(true);
            } else if (frameTime == 108) {
                gdqLogo->setVisible(true);
                gdq2Logo->setVisible(false);
            } else if (frameTime == 100) {
                gdqLogo->setVisible(false);
                gdq2Logo->setVisible(true);
            } else if (frameTime == 68) {
                gdqLogo->setVisible(true);
                gdq2Logo->setVisible(false);
            } else if (frameTime == 60) {
                gdqLogo->setVisible(false);
                gdq2Logo->setVisible(true);
            }

            if (frameTime > 600 && frameTime< 3075) {
                //scrollContainer->getTransform().pos.y += 0.2f;
                scrollContainer->getTransform().pos.y += 0.3f;
            }

            RenderManager::draw(rootNode);

            PAD_Read(pads);
            if (pads[0].button & PAD_BUTTON_START) {
                //void (*reload)() = (void(*)()) 0x80001800;
                //reload();
                return 0;
            }

            if (frameTime == 300) frameTime = 600;
            if (frameTime >= 600 && frameTime % 4 == 0) frameTime++; //Yes increment it again - everything needs to go faster
            frameTime++;
        }
        return 0;
    }
}

