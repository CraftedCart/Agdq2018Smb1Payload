#ifndef GDQ_RENDER_EMITTERSCENENODE_HPP
#define GDQ_RENDER_EMITTERSCENENODE_HPP

#include "ParticleSceneNode.hpp"

class EmitterSceneNode : public SceneNode {
    protected:
        std::vector<ParticleSceneNode*> particles;

    public:
        ParticleSceneNode *particleMesh;
        u32 framesElapsed = 0;

    public:
        virtual void tick() override;
};

#endif

