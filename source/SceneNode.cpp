#include "SceneNode.hpp"

float lerp(float a, float b, float f) {
    return a + f * (b - a);
}

SceneNode::~SceneNode() {
    for (SceneNode *node : children) {
        delete node;
    }
}

void SceneNode::tick() {
    if (interpSpeed != 0.0f) {
        transform.pos.x = lerp(transform.pos.x, interpTargetTransform.pos.x, interpSpeed);
        transform.pos.y = lerp(transform.pos.y, interpTargetTransform.pos.y, interpSpeed);
        transform.pos.z = lerp(transform.pos.z, interpTargetTransform.pos.z, interpSpeed);
        transform.rot.x = lerp(transform.rot.x, interpTargetTransform.rot.x, interpSpeed);
        transform.rot.y = lerp(transform.rot.y, interpTargetTransform.rot.y, interpSpeed);
        transform.rot.z = lerp(transform.rot.z, interpTargetTransform.rot.z, interpSpeed);
        transform.scl.x = lerp(transform.scl.x, interpTargetTransform.scl.x, interpSpeed);
        transform.scl.y = lerp(transform.scl.y, interpTargetTransform.scl.y, interpSpeed);
        transform.scl.z = lerp(transform.scl.z, interpTargetTransform.scl.z, interpSpeed);
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

