#include "SceneNode.hpp"

SceneNode::~SceneNode() {
    for (SceneNode *node : children) {
        delete node;
    }
}

void SceneNode::setVisible(bool visible) {
    this->visible = visible;
}

bool SceneNode::isVisible() {
    return visible;
}

Transform& SceneNode::getTransform() {
    return transform;
}

std::vector<SceneNode*>& SceneNode::getChildren() {
    return children;
}

void SceneNode::addChild(SceneNode *child) {
    children.push_back(child);
}

