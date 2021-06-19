//
// Created by Matthew Good on 14/6/21.
//

#include "Camera.h"

const Magnum::Matrix4 &Crafter::Camera::modelView() const {
    return _modelView;
}

void Crafter::Camera::updateCamera() {
    _modelView = _perspectiveProjection * (translationX() * translationZ() * translationY());
}
