//
// Created by Matthew Good on 15/6/21.
//

#include "Scale.h"

void Crafter::Scale::saveScaleX() {
    _scale_stackX.push({s_x, _scaleX});
}

void Crafter::Scale::saveScaleY() {
    _scale_stackY.push({s_y, _scaleY});
}

void Crafter::Scale::saveScaleZ() {
    _scale_stackZ.push({s_z, _scaleZ});
}

void Crafter::Scale::saveScale() {
    saveScaleX();
    saveScaleY();
    saveScaleZ();
}

void Crafter::Scale::restoreScaleX() {
    if (_scale_stackX.empty()) return;
    auto val = _scale_stackX.top();
    s_x = val.first;
    _scaleX = val.second;
    _scale_stackX.pop();
}

void Crafter::Scale::restoreScaleY() {
    if (_scale_stackY.empty()) return;
    auto val = _scale_stackY.top();
    s_y = val.first;
    _scaleY = val.second;
    _scale_stackY.pop();
}

void Crafter::Scale::restoreScaleZ() {
    if (_scale_stackZ.empty()) return;
    auto val = _scale_stackZ.top();
    s_z = val.first;
    _scaleZ = val.second;
    _scale_stackZ.pop();
}

void Crafter::Scale::restoreScale() {
    restoreScaleX();
    restoreScaleY();
    restoreScaleZ();
}

Magnum::Vector3 Crafter::Scale::scaleVector3() const {
    return {s_x, s_y, s_z};
}

void Crafter::Scale::setScaleX_(const float &x) {
    _scaleX = Magnum::Matrix4::scaling(Magnum::Vector3::xAxis(x));
}

void Crafter::Scale::setScaleY_(const float &y) {
    _scaleY = Magnum::Matrix4::scaling(Magnum::Vector3::yAxis(y));
}

void Crafter::Scale::setScaleZ_(const float &z) {
    _scaleZ = Magnum::Matrix4::scaling(Magnum::Vector3::zAxis(z));
}

void Crafter::Scale::setScaleX(const float &x) {
    s_x = x;
    setScaleX_(s_x);
}

void Crafter::Scale::addScaleX(const float &x) {
    s_x += x;
    setScaleX_(s_x);
}

void Crafter::Scale::subScaleX(const float &x) {
    s_x -= x;
    setScaleX_(s_x);
}

void Crafter::Scale::mulScaleX(const float &x) {
    s_x *= x;
    setScaleX_(s_x);
}

void Crafter::Scale::divScaleX(const float &x) {
    s_x /= x;
    setScaleX_(s_x);
}

Magnum::Matrix4 Crafter::Scale::scaleX() const {
    return _scaleX;
}

void Crafter::Scale::setScaleY(const float &y) {
    s_y = y;
    setScaleY_(s_y);
}

void Crafter::Scale::addScaleY(const float &y) {
    s_y += y;
    setScaleY_(s_y);
}

void Crafter::Scale::subScaleY(const float &y) {
    s_y -= y;
    setScaleY_(s_y);
}

void Crafter::Scale::mulScaleY(const float &y) {
    s_y *= y;
    setScaleY_(s_y);
}

void Crafter::Scale::divScaleY(const float &y) {
    s_y /= y;
    setScaleY_(s_y);
}

Magnum::Matrix4 Crafter::Scale::scaleY() const {
    return _scaleY;
}

void Crafter::Scale::setScaleZ(const float &z) {
    s_z = z;
    setScaleZ_(s_z);
}

void Crafter::Scale::addScaleZ(const float &z) {
    s_z += z;
    setScaleZ_(s_z);
}

void Crafter::Scale::subScaleZ(const float &z) {
    s_z -= z;
    setScaleZ_(s_z);
}

void Crafter::Scale::mulScaleZ(const float &z) {
    s_z *= z;
    setScaleZ_(s_z);
}

void Crafter::Scale::divScaleZ(const float &z) {
    s_z /= z;
    setScaleZ_(s_z);
}

Magnum::Matrix4 Crafter::Scale::scaleZ() const {
    return _scaleZ;
}

void Crafter::Scale::setScale(const float &x, const float &y, const float &z) {
    setScaleX(x);
    setScaleY(y);
    setScaleZ(z);
}

void Crafter::Scale::addScale(const float &x, const float &y, const float &z) {
    addScaleX(x);
    addScaleY(y);
    addScaleZ(z);
}

void Crafter::Scale::subScale(const float &x, const float &y, const float &z) {
    subScaleX(x);
    subScaleY(y);
    subScaleZ(z);
}

void Crafter::Scale::mulScale(const float &x, const float &y, const float &z) {
    mulScaleX(x);
    mulScaleY(y);
    mulScaleZ(z);
}

void Crafter::Scale::divScale(const float &x, const float &y, const float &z) {
    divScaleX(x);
    divScaleY(y);
    divScaleZ(z);
}

Magnum::Matrix4 Crafter::Scale::scale() const {
    return scaleX() * scaleY() * scaleZ();
}
