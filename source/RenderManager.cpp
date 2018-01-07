#include "RenderManager.hpp"
#include <malloc.h>
#include <cstring>

#define FIFO_SIZE (256 * 1024)

namespace RenderManager {
    GXRModeObj *screenMode;
    void *frameBuffer;
    vu8 readyForCopy;
    Mtx viewMatrix;
    Mtx projectionMatrix;
    guVector camera = {0.0f, 0.0f, 50.0f};
    guVector up = {0.0f, 1.0f, 0.0F};
    guVector look = {0.0f, 0.0f, -1.0f};
    GXColor backgroundColor = {33, 33, 33, 255};
    void *fifoBuffer = NULL;

    void init() {
        VIDEO_Init();

        screenMode = VIDEO_GetPreferredMode(NULL);

        PAD_Init();
        frameBuffer = MEM_K0_TO_K1(SYS_AllocateFramebuffer(screenMode));

        VIDEO_Configure(screenMode);
        VIDEO_SetNextFramebuffer(frameBuffer);
        VIDEO_SetPostRetraceCallback(RenderManager::copyBuffers);
        VIDEO_SetBlack(FALSE);
        VIDEO_Flush();

        //FIFO stores the graphics processor command buffer
        fifoBuffer = MEM_K0_TO_K1(memalign(32, FIFO_SIZE));
        memset(fifoBuffer, 0, FIFO_SIZE);

        GX_Init(fifoBuffer, FIFO_SIZE);
        GX_SetCopyClear(backgroundColor, 0x00FFFFFF);
        GX_SetViewport(0, 0, screenMode->fbWidth, screenMode->efbHeight, 0, 1);
        GX_SetDispCopyYScale((f32) screenMode->xfbHeight / (f32) screenMode->efbHeight);
        GX_SetScissor(0, 0, screenMode->fbWidth, screenMode->efbHeight);
        GX_SetDispCopySrc(0, 0, screenMode->fbWidth, screenMode->efbHeight);
        GX_SetDispCopyDst(screenMode->fbWidth, screenMode->xfbHeight);
        GX_SetCopyFilter(screenMode->aa, screenMode->sample_pattern, GX_TRUE, screenMode->vfilter);
        GX_SetFieldMode(screenMode->field_rendering, ((screenMode->viHeight == 2 * screenMode->xfbHeight) ? GX_ENABLE : GX_DISABLE));

        GX_SetCullMode(GX_CULL_NONE);
        GX_CopyDisp(frameBuffer,GX_TRUE);
        GX_SetDispCopyGamma(GX_GM_1_0);

        guPerspective(projectionMatrix, 60, 1.33f, 10.0f, 3000.0f);
        GX_LoadProjectionMtx(projectionMatrix, GX_PERSPECTIVE);

        GX_SetNumChans(1);
        GX_SetNumTexGens(0);
        GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORDNULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    }

    void draw(SceneNode *rootNode) {
        guLookAt(viewMatrix, &camera, &up, &look);
        GX_SetViewport(0, 0, screenMode->fbWidth, screenMode->efbHeight, 0, 1);
        GX_InvVtxCache();
        GX_InvalidateTexAll();

        Mtx modelView;
        guMtxIdentity(modelView);
        drawSceneGraph(rootNode, modelView);
    }

    void drawSceneGraph(SceneNode *node, Mtx transformMatrix) {
        for (SceneNode *child : node->getChildren()) {
            Transform transform = child->getTransform();
            Mtx childMatrix;
            memcpy(childMatrix, transformMatrix, sizeof(Mtx));

            guMtxTransApply(childMatrix, childMatrix, transform.pos.x, transform.pos.y, transform.pos.z);

            Mtx rotZ;
            Mtx rotY;
            Mtx rotX;
            guMtxRotRad(rotZ, 'z', transform.rot.z);
            guMtxRotRad(rotY, 'y', transform.rot.y);
            guMtxRotRad(rotX, 'x', transform.rot.x);
            guMtxConcat(childMatrix, rotZ, childMatrix);
            guMtxConcat(childMatrix, rotY, childMatrix);
            guMtxConcat(childMatrix, rotX, childMatrix);

            guMtxScaleApply(childMatrix, childMatrix, transform.scl.x, transform.scl.y, transform.scl.z);

            if (MeshSceneNode *mesh = dynamic_cast<MeshSceneNode*>(child)) drawMeshNode(mesh, childMatrix);
            drawSceneGraph(child, childMatrix);
        }
    }

    void drawMeshNode(MeshSceneNode *node, Mtx transformMatrix) {
        static GXColor litColors[] = {
            {0xFF, 0xFF, 0xFF, 0xFF}, //Light color 1
            {0x12, 0x12, 0x12, 0xFF}, //Ambient 1
            {0xFF, 0xFF, 0xFF, 0xFF}  //Material 1
        };
        guVector lightPos = {0.0f, 0.0f, 5000.0f};
        setLight(viewMatrix, lightPos, litColors[0], litColors[1], litColors[2]); //Intentionally not using the transformMatrix

        Mtx modelView;
        memcpy(modelView, transformMatrix, sizeof(Mtx));

        bool colored = node->useVertexColoring;

        bool textured = false;
        if (node->texture != nullptr) {
            GX_LoadTexObj(node->texture, GX_TEXMAP0);
            GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
            GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            textured = true;
        } else {
            GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORDNULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        }

        GX_ClearVtxDesc();

        GX_SetVtxDesc(GX_VA_POS, GX_INDEX16);
        GX_SetVtxDesc(GX_VA_NRM, GX_INDEX16);
        if (colored) GX_SetVtxDesc(GX_VA_CLR0, GX_INDEX16);
        if (textured) GX_SetVtxDesc(GX_VA_TEX0, GX_INDEX16);

        GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
        if (colored) GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        if (textured) GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

        GX_SetArray(GX_VA_POS, node->meshVertices, 3 * sizeof(f32));
        GX_SetArray(GX_VA_NRM, node->meshNormals, 3 * sizeof(f32));
        if (colored) GX_SetArray(GX_VA_CLR0, node->meshColors, 4 * sizeof(u8));
        if (textured) GX_SetArray(GX_VA_TEX0, node->meshUvs, 2 * sizeof(f32));

        guMtxConcat(viewMatrix, modelView, modelView);

        GX_LoadPosMtxImm(modelView, GX_PNMTX0);

        //Draw all tris
        GX_Begin(GX_TRIANGLES, GX_VTXFMT0, node->triangleCount * 3);

        for (u16 i = 0; i < node->triangleCount * 3; i += 3) {
            GX_Position1x16(i);
            GX_Normal1x16(i);
            if (colored) GX_Color1x16(i);
            if (textured) GX_TexCoord1x16(i);
            GX_Position1x16(i + 1);
            GX_Normal1x16(i + 1);
            if (colored) GX_Color1x16(i + 1);
            if (textured) GX_TexCoord1x16(i + 1);
            GX_Position1x16(i + 2);
            GX_Normal1x16(i + 2);
            if (colored) GX_Color1x16(i + 2);
            if (textured) GX_TexCoord1x16(i + 2);
        }

        GX_End();

        GX_DrawDone();
        RenderManager::readyForCopy = GX_TRUE;

        VIDEO_WaitVSync();
    }

    void setLight(Mtx view, guVector lightPos, GXColor litCol, GXColor ambCol, GXColor matCol) {
        GXLightObj lightObj;

        guVecMultiply(view, &lightPos, &lightPos); //Light pos needs to me multiplied by the view matrix

        GX_InitLightPos(&lightObj, lightPos.x, lightPos.y, lightPos.z);
        GX_InitLightColor(&lightObj, litCol);
        GX_LoadLightObj(&lightObj, GX_LIGHT0);

        //Set number of rasterized color channels
        GX_SetNumChans(1);
        GX_SetChanCtrl(GX_COLOR0, GX_ENABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT0, GX_DF_CLAMP, GX_AF_NONE);

        GX_SetChanAmbColor(GX_COLOR0, ambCol);
        GX_SetChanMatColor(GX_COLOR0, matCol);
    }

    GXTexObj loadTplTextureFromMemory(const u8 tpl[], const u32 length, const s32 textureId) {
        TPLFile file;
        GXTexObj texture;

        GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
        GX_SetNumTexGens(1);
        TPL_OpenTPLFromMemory(&file, (void*) tpl, length);
        TPL_GetTexture(&file, textureId, &texture);

        return texture;
    }

    void copyBuffers(u32 count __attribute__ ((unused))) {
        if (readyForCopy == GX_TRUE) {
            GX_SetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
            GX_SetColorUpdate(GX_TRUE);
            GX_CopyDisp(frameBuffer, GX_TRUE);
            GX_Flush();
            readyForCopy = GX_FALSE;
        }
    }
}

