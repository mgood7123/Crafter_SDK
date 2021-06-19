//
// Created by Matthew Good on 14/6/21.
//

#include "Blueprint.h"

void Crafter::Blueprint::setup() {
    engine.setup();
}

void Crafter::Blueprint::attachToCamera(Magnum::SceneGraph::Camera3D *camera) {
    engine.attachToCamera(camera);
}

void Crafter::Blueprint::updateAspectRatio(const Magnum::Vector2i & viewport, float aspectRatio) {
    engine.updateAspectRatio(viewport, aspectRatio);
}

void Crafter::Blueprint::rotateRelative(Magnum::Vector2 relative) {
    engine.rotateRelative(relative);
}

void Crafter::Blueprint::draw() {
    engine.draw();
}
