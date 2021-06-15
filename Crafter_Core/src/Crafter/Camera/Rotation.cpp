//
// Created by Matthew Good on 15/6/21.
//

#include "Rotation.h"

void Crafter::Rotation::setRotationX_(const float &degrees) {
    _rotationX = Magnum::Matrix4::rotationX(Magnum::Deg(degrees));
}

void Crafter::Rotation::setRotationY_(const float &degrees) {
    _rotationY = Magnum::Matrix4::rotationY(Magnum::Deg(degrees));
}

void Crafter::Rotation::setRotationZ_(const float &degrees) {
    _rotationZ = Magnum::Matrix4::rotationZ(Magnum::Deg(degrees));
}

void Crafter::Rotation::setRotationX(const float &degrees) {
    r_x = degrees;
    setRotationX_(r_x);
}

void Crafter::Rotation::addRotationX(const float &degrees) {
    r_x += degrees;
    setRotationX_(r_x);
}

void Crafter::Rotation::subRotationX(const float &degrees) {
    r_x -= degrees;
    setRotationX_(r_x);
}

void Crafter::Rotation::mulRotationX(const float &degrees) {
    r_x *= degrees;
    setRotationX_(r_x);
}

void Crafter::Rotation::divRotationX(const float &degrees) {
    r_x /= degrees;
    setRotationX_(r_x);
}

Magnum::Matrix4 Crafter::Rotation::rotationX() {
    return _rotationX;
}

void Crafter::Rotation::setRotationY(const float &degrees) {
    r_y = degrees;
    setRotationY_(r_y);
}

void Crafter::Rotation::addRotationY(const float &degrees) {
    r_y += degrees;
    setRotationY_(r_y);
}

void Crafter::Rotation::subRotationY(const float &degrees) {
    r_y -= degrees;
    setRotationY_(r_y);
}

void Crafter::Rotation::mulRotationY(const float &degrees) {
    r_y *= degrees;
    setRotationY_(r_y);
}

void Crafter::Rotation::divRotationY(const float &degrees) {
    r_y /= degrees;
    setRotationY_(r_y);
}

Magnum::Matrix4 Crafter::Rotation::rotationY() {
    return _rotationY;
}

void Crafter::Rotation::setRotationZ(const float &degrees) {
    r_z = degrees;
    setRotationZ_(r_z);
}

void Crafter::Rotation::addRotationZ(const float &degrees) {
    r_z += degrees;
    setRotationZ_(r_z);
}

void Crafter::Rotation::subRotationZ(const float &degrees) {
    r_z -= degrees;
    setRotationZ_(r_z);
}

void Crafter::Rotation::mulRotationZ(const float &degrees) {
    r_z *= degrees;
    setRotationZ_(r_z);
}

void Crafter::Rotation::divRotationZ(const float &degrees) {
    r_z /= degrees;
    setRotationZ_(r_z);
}

Magnum::Matrix4 Crafter::Rotation::rotationZ() {
    return _rotationZ;
}

void Crafter::Rotation::setRotation(const float &x, const float &y, const float &z) {
    setRotationX(x);
    setRotationY(y);
    setRotationZ(z);
}

void Crafter::Rotation::addRotation(const float &x, const float &y, const float &z) {
    addRotationX(x);
    addRotationY(y);
    addRotationZ(z);
}

void Crafter::Rotation::subRotation(const float &x, const float &y, const float &z) {
    subRotationX(x);
    subRotationY(y);
    subRotationZ(z);
}

void Crafter::Rotation::mulRotation(const float &x, const float &y, const float &z) {
    mulRotationX(x);
    mulRotationY(y);
    mulRotationZ(z);
}

void Crafter::Rotation::divRotation(const float &x, const float &y, const float &z) {
    divRotationX(x);
    divRotationY(y);
    divRotationZ(z);
}

Magnum::Matrix4 Crafter::Rotation::rotation() {
    return rotationX() * rotationY() * rotationZ();
}
