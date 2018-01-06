#ifndef GDQ_RENDER_SCENENODE_HPP
#define GDQ_RENDER_SCENENODE_HPP

#include "Transform.hpp"
#include <gccore.h>
#include <vector>

class SceneNode {
    protected:
        Transform transform;
        std::vector<SceneNode*> children;

    public:
        virtual ~SceneNode();

        Transform& getTransform();
        std::vector<SceneNode*>& getChildren();
        void addChild(SceneNode *child);
};

#endif

