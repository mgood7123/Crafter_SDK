//
// Created by Matthew Good on 17/6/21.
//

#include "ClipSpace.h"

const Magnum::Matrix4 &Crafter::ClipSpace::perspectiveProjection() const {
    return _perspectiveProjection;
}

void
Crafter::ClipSpace::setPerspectiveProjection(const Magnum::Vector2 &size, const float near,
                                               const float far) {
    _perspectiveProjection = Magnum::Matrix4::perspectiveProjection(size, near, far);
    hasPerspectiveProjection = true;
}

void Crafter::ClipSpace::setPerspectiveProjection(float fov, float aspectRatio, float near,
                                                    float far) {
    setPerspectiveProjection(Magnum::Deg(fov), aspectRatio, near, far);
}

void Crafter::ClipSpace::setPerspectiveProjection(Magnum::Rad fov, float aspectRatio, float near,
                                                    float far) {
    _perspectiveProjection = Magnum::Matrix4::perspectiveProjection(fov, aspectRatio, near, far);
    hasPerspectiveProjection = true;
}

void Crafter::ClipSpace::setPerspectiveProjection(const Magnum::Vector2 &bottomLeft,
                                                    const Magnum::Vector2 &topRight, float near,
                                                    float far) {
    _perspectiveProjection = Magnum::Matrix4::perspectiveProjection(bottomLeft, topRight, near, far);
    hasPerspectiveProjection = true;
}