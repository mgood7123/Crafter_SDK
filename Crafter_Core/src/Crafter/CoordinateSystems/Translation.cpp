//
// Created by Matthew Good on 15/6/21.
//

#include "Translation.h"

void Crafter::Translation::saveTranslationX() {
    _translation_stackX.push({t_x, _translationX});
}

void Crafter::Translation::saveTranslationY() {
    _translation_stackY.push({t_y, _translationY});
}

void Crafter::Translation::saveTranslationZ() {
    _translation_stackZ.push({t_z, _translationZ});
}

void Crafter::Translation::saveTranslation() {
    saveTranslationX();
    saveTranslationY();
    saveTranslationZ();
}

void Crafter::Translation::restoreTranslationX() {
    if (_translation_stackX.empty()) return;
    auto val = _translation_stackX.top();
    t_x = val.first;
    _translationX = val.second;
    _translation_stackX.pop();
}

void Crafter::Translation::restoreTranslationY() {
    if (_translation_stackY.empty()) return;
    auto val = _translation_stackY.top();
    t_y = val.first;
    _translationY = val.second;
    _translation_stackY.pop();
}

void Crafter::Translation::restoreTranslationZ() {
    if (_translation_stackZ.empty()) return;
    auto val = _translation_stackZ.top();
    t_z = val.first;
    _translationZ = val.second;
    _translation_stackZ.pop();
}

void Crafter::Translation::restoreTranslation() {
    restoreTranslationX();
    restoreTranslationY();
    restoreTranslationZ();
}

Magnum::Vector3 Crafter::Translation::translationVector3() const {
    return {t_x, t_y, t_z};
}

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

Magnum::Matrix4 Crafter::Translation::translationX() const {
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

Magnum::Matrix4 Crafter::Translation::translationY() const {
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

Magnum::Matrix4 Crafter::Translation::translationZ() const {
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

Magnum::Matrix4 Crafter::Translation::translation() const {
    return translationX() * translationY() * translationZ();
}

Magnum::Matrix4
Crafter::Translation::translationDistance(const Magnum::Matrix4 &A, const Magnum::Matrix4 &B) {
    return Magnum::Matrix4::translation(B.translation() - A.translation());
}
