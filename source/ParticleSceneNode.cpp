#include "ParticleSceneNode.hpp"

void ParticleSceneNode::tick() {
    velocity.x += acceleration.x;
    velocity.y += acceleration.y;
    velocity.z += acceleration.z;

    velocity.x *= dragMultiplier;
    velocity.y *= dragMultiplier;
    velocity.z *= dragMultiplier;

    getTransform().pos.x += velocity.x;
    getTransform().pos.y += velocity.y;
    getTransform().pos.z += velocity.z;

    getTransform().scl.x *= scaleMultiplier;
    getTransform().scl.y *= scaleMultiplier;
    getTransform().scl.z *= scaleMultiplier;

    framesElapsed++;
}

