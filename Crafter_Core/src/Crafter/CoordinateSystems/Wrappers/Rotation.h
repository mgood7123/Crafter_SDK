//
// Created by Matthew Good on 17/6/21.
//

#ifndef CRAFTER_WRAPPER_ROTATION_H
#define CRAFTER_WRAPPER_ROTATION_H

#include <Magnum/Magnum.h> // Magnum:: typedefs
#include <Magnum/Math/Matrix4.h> // Magnum::Matrix4

#define ROTATION_WRAPPER_HEADER virtual void saveRotationX(); \
virtual void saveRotationY(); \
virtual void saveRotationZ(); \
virtual void saveRotation(); \
virtual void restoreRotationX(); \
virtual void restoreRotationY(); \
virtual void restoreRotationZ(); \
virtual void restoreRotation(); \
virtual Magnum::Vector3 rotationVector3() const; \
virtual void setRotationX(const float &degrees); \
virtual void addRotationX(const float &degrees); \
virtual void subRotationX(const float &degrees); \
virtual void mulRotationX(const float &degrees); \
virtual void divRotationX(const float &degrees); \
virtual Magnum::Matrix4 rotationX() const; \
virtual void setRotationY(const float &degrees); \
virtual void addRotationY(const float &degrees); \
virtual void subRotationY(const float &degrees); \
virtual void mulRotationY(const float &degrees); \
virtual void divRotationY(const float &degrees); \
virtual Magnum::Matrix4 rotationY() const; \
virtual void setRotationZ(const float &degrees); \
virtual void addRotationZ(const float &degrees); \
virtual void subRotationZ(const float &degrees); \
virtual void mulRotationZ(const float &degrees); \
virtual void divRotationZ(const float &degrees); \
virtual Magnum::Matrix4 rotationZ() const; \
virtual void setRotation(const float &x, const float &y, const float &z); \
virtual void addRotation(const float &x, const float &y, const float &z); \
virtual void subRotation(const float &x, const float &y, const float &z); \
virtual void mulRotation(const float &x, const float &y, const float &z); \
virtual void divRotation(const float &x, const float &y, const float &z); \
virtual Magnum::Matrix4 rotation() const;

#define ROTATION_WRAPPER_CPP(CLASS, var) void CLASS::saveRotationX() { \
    var.saveRotationX(); \
} \
void CLASS::saveRotationY() { \
    var.saveRotationY(); \
} \
void CLASS::saveRotationZ() { \
    var.saveRotationZ(); \
} \
void CLASS::saveRotation() { \
    var.saveRotation(); \
} \
void CLASS::restoreRotationX() { \
    var.restoreRotationX(); \
} \
void CLASS::restoreRotationY() { \
    var.restoreRotationY(); \
} \
void CLASS::restoreRotationZ() { \
    var.restoreRotationZ(); \
} \
void CLASS::restoreRotation() { \
    var.restoreRotation(); \
} \
Magnum::Vector3 CLASS::rotationVector3() const { \
    return var.rotationVector3(); \
} \
void CLASS::setRotationX(const float &degrees) { \
    var.setRotationX(degrees); \
} \
void CLASS::addRotationX(const float &degrees) { \
    var.addRotationX(degrees); \
} \
void CLASS::subRotationX(const float &degrees) { \
    var.subRotationX(degrees); \
} \
void CLASS::mulRotationX(const float &degrees) { \
    var.mulRotationX(degrees); \
} \
void CLASS::divRotationX(const float &degrees) { \
    var.divRotationX(degrees); \
} \
Magnum::Matrix4 CLASS::rotationX() const { \
    return var.rotationX(); \
} \
void CLASS::setRotationY(const float &degrees) { \
    var.setRotationY(degrees); \
} \
void CLASS::addRotationY(const float &degrees) { \
    var.addRotationY(degrees); \
} \
void CLASS::subRotationY(const float &degrees) { \
    var.subRotationY(degrees); \
} \
void CLASS::mulRotationY(const float &degrees) { \
    var.mulRotationY(degrees); \
} \
void CLASS::divRotationY(const float &degrees) { \
    var.divRotationY(degrees); \
} \
Magnum::Matrix4 CLASS::rotationY() const { \
    return var.rotationY(); \
} \
void CLASS::setRotationZ(const float &degrees) { \
    var.setRotationZ(degrees); \
} \
void CLASS::addRotationZ(const float &degrees) { \
    var.addRotationZ(degrees); \
} \
void CLASS::subRotationZ(const float &degrees) { \
    var.subRotationZ(degrees); \
} \
void CLASS::mulRotationZ(const float &degrees) { \
    var.mulRotationZ(degrees); \
} \
void CLASS::divRotationZ(const float &degrees) { \
    var.divRotationZ(degrees); \
} \
Magnum::Matrix4 CLASS::rotationZ() const { \
    return var.rotationZ(); \
} \
void CLASS::setRotation(const float &x, const float &y, const float &z) { \
    var.setRotation(x, y, z); \
} \
void CLASS::addRotation(const float &x, const float &y, const float &z) { \
    var.addRotation(x, y, z); \
} \
void CLASS::subRotation(const float &x, const float &y, const float &z) { \
    var.subRotation(x, y, z); \
} \
void CLASS::mulRotation(const float &x, const float &y, const float &z) { \
    var.mulRotation(x, y, z); \
} \
void CLASS::divRotation(const float &x, const float &y, const float &z) { \
    var.divRotation(x, y, z); \
} \
Magnum::Matrix4 CLASS::rotation() const { \
    return var.rotation(); \
}

#define ROTATION_WRAPPER__CPP(var) void saveRotationX() { \
    var.saveRotationX(); \
} \
void saveRotationY() { \
    var.saveRotationY(); \
} \
void saveRotationZ() { \
    var.saveRotationZ(); \
} \
void saveRotation() { \
    var.saveRotation(); \
} \
void restoreRotationX() { \
    var.restoreRotationX(); \
} \
void restoreRotationY() { \
    var.restoreRotationY(); \
} \
void restoreRotationZ() { \
    var.restoreRotationZ(); \
} \
void restoreRotation() { \
    var.restoreRotation(); \
} \
Magnum::Vector3 rotationVector3() const { \
    return var.rotationVector3(); \
} \
void setRotationX(const float &degrees) { \
    var.setRotationX(degrees); \
} \
void addRotationX(const float &degrees) { \
    var.addRotationX(degrees); \
} \
void subRotationX(const float &degrees) { \
    var.subRotationX(degrees); \
} \
void mulRotationX(const float &degrees) { \
    var.mulRotationX(degrees); \
} \
void divRotationX(const float &degrees) { \
    var.divRotationX(degrees); \
} \
Magnum::Matrix4 rotationX() const { \
    return var.rotationX(); \
} \
void setRotationY(const float &degrees) { \
    var.setRotationY(degrees); \
} \
void addRotationY(const float &degrees) { \
    var.addRotationY(degrees); \
} \
void subRotationY(const float &degrees) { \
    var.subRotationY(degrees); \
} \
void mulRotationY(const float &degrees) { \
    var.mulRotationY(degrees); \
} \
void divRotationY(const float &degrees) { \
    var.divRotationY(degrees); \
} \
Magnum::Matrix4 rotationY() const { \
    return var.rotationY(); \
} \
void setRotationZ(const float &degrees) { \
    var.setRotationZ(degrees); \
} \
void addRotationZ(const float &degrees) { \
    var.addRotationZ(degrees); \
} \
void subRotationZ(const float &degrees) { \
    var.subRotationZ(degrees); \
} \
void mulRotationZ(const float &degrees) { \
    var.mulRotationZ(degrees); \
} \
void divRotationZ(const float &degrees) { \
    var.divRotationZ(degrees); \
} \
Magnum::Matrix4 rotationZ() const { \
    return var.rotationZ(); \
} \
void setRotation(const float &x, const float &y, const float &z) { \
    var.setRotation(x, y, z); \
} \
void addRotation(const float &x, const float &y, const float &z) { \
    var.addRotation(x, y, z); \
} \
void subRotation(const float &x, const float &y, const float &z) { \
    var.subRotation(x, y, z); \
} \
void mulRotation(const float &x, const float &y, const float &z) { \
    var.mulRotation(x, y, z); \
} \
void divRotation(const float &x, const float &y, const float &z) { \
    var.divRotation(x, y, z); \
} \
Magnum::Matrix4 rotation() const { \
    return var.rotation(); \
}

#endif //CRAFTER_WRAPPER_ROTATION_H
