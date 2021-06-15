//
// Created by Matthew Good on 15/6/21.
//

#include "Translation.h"

void Crafter::Translation::setTranslationX_(const float &x) {
    _translationX = Magnum::Matrix4::translation(Magnum::Vector3::xAxis(x));
}

void Crafter::Translation::setTranslationY_(const float &y) {
    _translationY = Magnum::Matrix4::translation(Magnum::Vector3::yAxis(y));
}

void Crafter::Translation::setTranslationZ_(const float &z) {
    _translationZ = Magnum::Matrix4::translation(Magnum::Vector3::zAxis(z));
}

void Crafter::Translation::setTranslationX(const float &x) {
    t_x = x;
    setTranslationX_(t_x);
}

void Crafter::Translation::addTranslationX(const float &x) {
    t_x += x;
    setTranslationX_(t_x);
}

void Crafter::Translation::subTranslationX(const float &x) {
    t_x -= x;
    setTranslationX_(t_x);
}

void Crafter::Translation::mulTranslationX(const float &x) {
    t_x *= x;
    setTranslationX_(t_x);
}

void Crafter::Translation::divTranslationX(const float &x) {
    t_x /= x;
    setTranslationX_(t_x);
}

Magnum::Matrix4 Crafter::Translation::translationX() {
    return _translationX;
}

void Crafter::Translation::setTranslationY(const float &y) {
    t_y = y;
    setTranslationY_(t_y);
}

void Crafter::Translation::addTranslationY(const float &y) {
    t_y += y;
    setTranslationY_(t_y);
}

void Crafter::Translation::subTranslationY(const float &y) {
    t_y -= y;
    setTranslationY_(t_y);
}

void Crafter::Translation::mulTranslationY(const float &y) {
    t_y *= y;
    setTranslationY_(t_y);
}

void Crafter::Translation::divTranslationY(const float &y) {
    t_y /= y;
    setTranslationY_(t_y);
}

Magnum::Matrix4 Crafter::Translation::translationY() {
    return _translationY;
}

void Crafter::Translation::setTranslationZ(const float &z) {
    t_z = z;
    setTranslationZ_(t_z);
}

void Crafter::Translation::addTranslationZ(const float &z) {
    t_z += z;
    setTranslationZ_(t_z);
}

void Crafter::Translation::subTranslationZ(const float &z) {
    t_z -= z;
    setTranslationZ_(t_z);
}

void Crafter::Translation::mulTranslationZ(const float &z) {
    t_z *= z;
    setTranslationZ_(t_z);
}

void Crafter::Translation::divTranslationZ(const float &z) {
    t_z /= z;
    setTranslationZ_(t_z);
}

Magnum::Matrix4 Crafter::Translation::translationZ() {
    return _translationZ;
}

void Crafter::Translation::setTranslation(const float &x, const float &y, const float &z) {
    setTranslationX(x);
    setTranslationY(y);
    setTranslationZ(z);
}

void Crafter::Translation::addTranslation(const float &x, const float &y, const float &z) {
    addTranslationX(x);
    addTranslationY(y);
    addTranslationZ(z);
}

void Crafter::Translation::subTranslation(const float &x, const float &y, const float &z) {
    subTranslationX(x);
    subTranslationY(y);
    subTranslationZ(z);
}

void Crafter::Translation::mulTranslation(const float &x, const float &y, const float &z) {
    mulTranslationX(x);
    mulTranslationY(y);
    mulTranslationZ(z);
}

void Crafter::Translation::divTranslation(const float &x, const float &y, const float &z) {
    divTranslationX(x);
    divTranslationY(y);
    divTranslationZ(z);
}

Magnum::Matrix4 Crafter::Translation::translation() {
    return translationX() * translationY() * translationZ();
}

Magnum::Matrix4
Crafter::Translation::translationDistance(const Magnum::Matrix4 &A, const Magnum::Matrix4 &B) {
    Magnum::Vector3 a = A.translation();
    Magnum::Vector3 b = B.translation();
    Magnum::Vector3 c = b - a;
    return Magnum::Matrix4::translation(c);
}
