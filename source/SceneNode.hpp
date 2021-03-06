#ifndef GDQ_RENDER_SCENENODE_HPP
#define GDQ_RENDER_SCENENODE_HPP

#include "Transform.hpp"
#include <gccore.h>
#include <vector>

class SceneNode {
    protected:
        Transform transform;
        bool visible = true;
        std::vector<SceneNode*> children;

    public:
        //I'm too lazy to make setters/getters
        float interpSpeed = 0.0f;
        Transform interpTargetTransform;

    public:
        virtual ~SceneNode();

        /**
         * @brief Called every frame, before rendering
         */
        virtual void tick();

        Transform& getTransform();
        void setVisible(bool visible);
        bool isVisible();
        std::vector<SceneNode*>& getChildren();
        void addChild(SceneNode *child);
};

#endif

