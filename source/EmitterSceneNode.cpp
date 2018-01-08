#include "EmitterSceneNode.hpp"
#include <algorithm>
#include <cstdlib>

void EmitterSceneNode::tick() {
    framesElapsed++;

    std::vector<ParticleSceneNode*> toDelete;
    for (ParticleSceneNode *particle : particles) {
        if (particle->framesElapsed >= particle->lifetime) {
            //Remove from parent and delete it
            std::vector<SceneNode*> &vec = getChildren();
            vec.erase(std::remove(vec.begin(), vec.end(), particle), vec.end());
            particles.erase(std::remove(particles.begin(), particles.end(), particle), particles.end());
            toDelete.push_back(particle);
        }
    }

    for (ParticleSceneNode *node : toDelete) {
        delete node;
    }

    if (!(framesElapsed % 135 == 0)) return;

    for (int i = 0; i < 150; i++) {
        ParticleSceneNode *particle = new ParticleSceneNode(*particleMesh);

        particle->dragMultiplier = 0.95f;

        particle->velocity.x += ((rand() / (float) RAND_MAX) - 0.5f) * 10.0f;
        particle->velocity.y += ((rand() / (float) RAND_MAX) - 0.5f) * 10.0f;
        particle->velocity.z += ((rand() / (float) RAND_MAX) - 0.5f) * 10.0f;

        addChild(particle);
        particles.push_back(particle);
    }
}
