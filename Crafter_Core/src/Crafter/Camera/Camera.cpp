//
// Created by Matthew Good on 14/6/21.
//

#include "Camera.h"

void Crafter::Camera::setRotationX_(const float &x) {
    _rotationX = Magnum::Matrix4::rotationX(Magnum::Deg(x));
}

void Crafter::Camera::setRotationY_(const float &y) {
    _rotationY = Magnum::Matrix4::rotationY(Magnum::Deg(y));
}

void Crafter::Camera::setRotationZ_(const float &z) {
    _rotationZ = Magnum::Matrix4::rotationZ(Magnum::Deg(z));
}

void Crafter::Camera::setTranslationX_(const float &x) {
    _translationX = Magnum::Matrix4::translation(Magnum::Vector3::xAxis(x));
}

void Crafter::Camera::setTranslationY_(const float &y) {
    _translationY = Magnum::Matrix4::translation(Magnum::Vector3::yAxis(y));
}

void Crafter::Camera::setTranslationZ_(const float &z) {
    _translationZ = Magnum::Matrix4::translation(Magnum::Vector3::zAxis(z));
}

const Magnum::Matrix4 &Crafter::Camera::modelView() const {
    return _modelView;
}

const Magnum::Matrix4 &Crafter::Camera::perspectiveProjection() const {
    return _perspectiveProjection;
}

void Crafter::Camera::setRotationX(const float &x) {
    r_x = x;
    setRotationX_(r_x);
}

void Crafter::Camera::addRotationX(const float &x) {
    r_x += x;
    setRotationX_(r_x);
}

void Crafter::Camera::subRotationX(const float &x) {
    r_x -= x;
    setRotationX_(r_x);
}

void Crafter::Camera::mulRotationX(const float &x) {
    r_x *= x;
    setRotationX_(r_x);
}

void Crafter::Camera::divRotationX(const float &x) {
    r_x /= x;
    setRotationX_(r_x);
}

Magnum::Matrix4 Crafter::Camera::rotationX() {
    return _rotationX;
}

void Crafter::Camera::setRotationY(const float &y) {
    r_y = y;
    setRotationY_(r_y);
}

void Crafter::Camera::addRotationY(const float &y) {
    r_y += y;
    setRotationY_(r_y);
}

void Crafter::Camera::subRotationY(const float &y) {
    r_y -= y;
    setRotationY_(r_y);
}

void Crafter::Camera::mulRotationY(const float &y) {
    r_y *= y;
    setRotationY_(r_y);
}

void Crafter::Camera::divRotationY(const float &y) {
    r_y /= y;
    setRotationY_(r_y);
}

Magnum::Matrix4 Crafter::Camera::rotationY() {
    return _rotationY;
}

void Crafter::Camera::setRotationZ(const float &z) {
    r_z = z;
    setRotationZ_(r_z);
}

void Crafter::Camera::addRotationZ(const float &z) {
    r_z += z;
    setRotationZ_(r_z);
}

void Crafter::Camera::subRotationZ(const float &z) {
    r_z -= z;
    setRotationZ_(r_z);
}

void Crafter::Camera::mulRotationZ(const float &z) {
    r_z *= z;
    setRotationZ_(r_z);
}

void Crafter::Camera::divRotationZ(const float &z) {
    r_z /= z;
    setRotationZ_(r_z);
}

Magnum::Matrix4 Crafter::Camera::rotationZ() {
    return _rotationZ;
}

void Crafter::Camera::setRotation(const float &x, const float &y, const float &z) {
    setRotationX(x);
    setRotationY(y);
    setRotationZ(z);
}

void Crafter::Camera::addRotation(const float &x, const float &y, const float &z) {
    addRotationX(x);
    addRotationY(y);
    addRotationZ(z);
}

void Crafter::Camera::subRotation(const float &x, const float &y, const float &z) {
    subRotationX(x);
    subRotationY(y);
    subRotationZ(z);
}

void Crafter::Camera::mulRotation(const float &x, const float &y, const float &z) {
    mulRotationX(x);
    mulRotationY(y);
    mulRotationZ(z);
}

void Crafter::Camera::divRotation(const float &x, const float &y, const float &z) {
    divRotationX(x);
    divRotationY(y);
    divRotationZ(z);
}

Magnum::Matrix4 Crafter::Camera::rotation() {
    return rotationX() * rotationY() * rotationZ();
}

void Crafter::Camera::setTranslationX(const float &x) {
    t_x = x;
    setTranslationX_(t_x);
}

void Crafter::Camera::addTranslationX(const float &x) {
    t_x += x;
    setTranslationX_(t_x);
}

void Crafter::Camera::subTranslationX(const float &x) {
    t_x -= x;
    setTranslationX_(t_x);
}

void Crafter::Camera::mulTranslationX(const float &x) {
    t_x *= x;
    setTranslationX_(t_x);
}

void Crafter::Camera::divTranslationX(const float &x) {
    t_x /= x;
    setTranslationX_(t_x);
}

Magnum::Matrix4 Crafter::Camera::translationX() {
    return _translationX;
}

void Crafter::Camera::setTranslationY(const float &y) {
    t_y = y;
    setTranslationY_(t_y);
}

void Crafter::Camera::addTranslationY(const float &y) {
    t_y += y;
    setTranslationY_(t_y);
}

void Crafter::Camera::subTranslationY(const float &y) {
    t_y -= y;
    setTranslationY_(t_y);
}

void Crafter::Camera::mulTranslationY(const float &y) {
    t_y *= y;
    setTranslationY_(t_y);
}

void Crafter::Camera::divTranslationY(const float &y) {
    t_y /= y;
    setTranslationY_(t_y);
}

Magnum::Matrix4 Crafter::Camera::translationY() {
    return _translationY;
}

void Crafter::Camera::setTranslationZ(const float &z) {
    t_z = z;
    setTranslationZ_(t_z);
}

void Crafter::Camera::addTranslationZ(const float &z) {
    t_z += z;
    setTranslationZ_(t_z);
}

void Crafter::Camera::subTranslationZ(const float &z) {
    t_z -= z;
    setTranslationZ_(t_z);
}

void Crafter::Camera::mulTranslationZ(const float &z) {
    t_z *= z;
    setTranslationZ_(t_z);
}

void Crafter::Camera::divTranslationZ(const float &z) {
    t_z /= z;
    setTranslationZ_(t_z);
}

Magnum::Matrix4 Crafter::Camera::translationZ() {
    return _translationZ;
}

void Crafter::Camera::setTranslation(const float &x, const float &y, const float &z) {
    setTranslationX(x);
    setTranslationY(y);
    setTranslationZ(z);
}

void Crafter::Camera::addTranslation(const float &x, const float &y, const float &z) {
    addTranslationX(x);
    addTranslationY(y);
    addTranslationZ(z);
}

void Crafter::Camera::subTranslation(const float &x, const float &y, const float &z) {
    subTranslationX(x);
    subTranslationY(y);
    subTranslationZ(z);
}

void Crafter::Camera::mulTranslation(const float &x, const float &y, const float &z) {
    mulTranslationX(x);
    mulTranslationY(y);
    mulTranslationZ(z);
}

void Crafter::Camera::divTranslation(const float &x, const float &y, const float &z) {
    divTranslationX(x);
    divTranslationY(y);
    divTranslationZ(z);
}

Magnum::Matrix4 Crafter::Camera::translation() {
    return translationX() * translationY() * translationZ();
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
    _modelView = _perspectiveProjection * (_translationX * _translationY * _translationZ);
}
