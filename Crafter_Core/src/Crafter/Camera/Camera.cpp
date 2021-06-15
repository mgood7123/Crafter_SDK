//
// Created by Matthew Good on 14/6/21.
//

#include "Camera.h"

const Magnum::Matrix4 &Crafter::Camera::modelView() const {
    return _modelView;
}

const Magnum::Matrix4 &Crafter::Camera::perspectiveProjection() const {
    return _perspectiveProjection;
}

void
Crafter::Camera::setPerspectiveProjection(const Magnum::Vector2 &size, const float near,
                                          const float far) {
    _perspectiveProjection = Magnum::Matrix4::perspectiveProjection(size, near, far);
    hasPerspectiveProjection = true;
}

void Crafter::Camera::setPerspectiveProjection(Magnum::Rad fov, float aspectRatio, float near,
                                               float far) {
    _perspectiveProjection = Magnum::Matrix4::perspectiveProjection(fov, aspectRatio, near, far);
    hasPerspectiveProjection = true;
}

void Crafter::Camera::setPerspectiveProjection(const Magnum::Vector2 &bottomLeft,
                                               const Magnum::Vector2 &topRight, float near,
                                               float far) {
    _perspectiveProjection = Magnum::Matrix4::perspectiveProjection(bottomLeft, topRight, near, far);
    hasPerspectiveProjection = true;
}

void Crafter::Camera::updateCamera() {
    _modelView = _perspectiveProjection * (translationX() * translationZ() * translationY());
}
