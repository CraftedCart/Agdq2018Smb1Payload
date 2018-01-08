#ifndef GDQ_RENDER_PARTICLESCENENODE_HPP
#define GDQ_RENDER_PARTICLESCENENODE_HPP

#include "MeshSceneNode.hpp"

class ParticleSceneNode : public MeshSceneNode {
    public:
        guVector velocity;
        guVector acceleration;
        float dragMultiplier = 1.0f;
        float scaleMultiplier = 1.0f;
        u32 lifetime;
        u32 framesElapsed = 0;

    public:
        virtual void tick() override;
};

#endif

