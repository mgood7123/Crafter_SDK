//
// Created by Matthew Good on 17/6/21.
//

#ifndef CRAFTER_WRAPPER_SCALE_H
#define CRAFTER_WRAPPER_SCALE_H

#include <Magnum/Magnum.h> // Magnum:: typedefs
#include <Magnum/Math/Matrix4.h> // Magnum::Matrix4

#define SCALE_WRAPPER_HEADER virtual void saveScaleX(); \
virtual void saveScaleY(); \
virtual void saveScaleZ(); \
virtual void saveScale(); \
virtual void restoreScaleX(); \
virtual void restoreScaleY(); \
virtual void restoreScaleZ(); \
virtual void restoreScale(); \
virtual Magnum::Vector3 scaleVector3() const; \
virtual void setScaleX(const float &degrees); \
virtual void addScaleX(const float &degrees); \
virtual void subScaleX(const float &degrees); \
virtual void mulScaleX(const float &degrees); \
virtual void divScaleX(const float &degrees); \
virtual Magnum::Matrix4 scaleX() const; \
virtual void setScaleY(const float &degrees); \
virtual void addScaleY(const float &degrees); \
virtual void subScaleY(const float &degrees); \
virtual void mulScaleY(const float &degrees); \
virtual void divScaleY(const float &degrees); \
virtual Magnum::Matrix4 scaleY() const; \
virtual void setScaleZ(const float &degrees); \
virtual void addScaleZ(const float &degrees); \
virtual void subScaleZ(const float &degrees); \
virtual void mulScaleZ(const float &degrees); \
virtual void divScaleZ(const float &degrees); \
virtual Magnum::Matrix4 scaleZ() const; \
virtual void setScale(const float &x, const float &y, const float &z); \
virtual void addScale(const float &x, const float &y, const float &z); \
virtual void subScale(const float &x, const float &y, const float &z); \
virtual void mulScale(const float &x, const float &y, const float &z); \
virtual void divScale(const float &x, const float &y, const float &z); \
virtual Magnum::Matrix4 scale() const;

#define SCALE_WRAPPER_CPP(CLASS, var) void CLASS::saveScaleX() { \
    var.saveScaleX(); \
} \
void CLASS::saveScaleY() { \
    var.saveScaleY(); \
} \
void CLASS::saveScaleZ() { \
    var.saveScaleZ(); \
} \
void CLASS::saveScale() { \
    var.saveScale(); \
} \
void CLASS::restoreScaleX() { \
    var.restoreScaleX(); \
} \
void CLASS::restoreScaleY() { \
    var.restoreScaleY(); \
} \
void CLASS::restoreScaleZ() { \
    var.restoreScaleZ(); \
} \
void CLASS::restoreScale() { \
    var.restoreScale(); \
} \
Magnum::Vector3 CLASS::scaleVector3() const { \
    return var.scaleVector3(); \
} \
void CLASS::setScaleX(const float &degrees) { \
    var.setScaleX(degrees); \
} \
void CLASS::addScaleX(const float &degrees) { \
    var.addScaleX(degrees); \
} \
void CLASS::subScaleX(const float &degrees) { \
    var.subScaleX(degrees); \
} \
void CLASS::mulScaleX(const float &degrees) { \
    var.mulScaleX(degrees); \
} \
void CLASS::divScaleX(const float &degrees) { \
    var.divScaleX(degrees); \
} \
Magnum::Matrix4 CLASS::scaleX() const { \
    return var.scaleX(); \
} \
void CLASS::setScaleY(const float &degrees) { \
    var.setScaleY(degrees); \
} \
void CLASS::addScaleY(const float &degrees) { \
    var.addScaleY(degrees); \
} \
void CLASS::subScaleY(const float &degrees) { \
    var.subScaleY(degrees); \
} \
void CLASS::mulScaleY(const float &degrees) { \
    var.mulScaleY(degrees); \
} \
void CLASS::divScaleY(const float &degrees) { \
    var.divScaleY(degrees); \
} \
Magnum::Matrix4 CLASS::scaleY() const { \
    return var.scaleY(); \
} \
void CLASS::setScaleZ(const float &degrees) { \
    var.setScaleZ(degrees); \
} \
void CLASS::addScaleZ(const float &degrees) { \
    var.addScaleZ(degrees); \
} \
void CLASS::subScaleZ(const float &degrees) { \
    var.subScaleZ(degrees); \
} \
void CLASS::mulScaleZ(const float &degrees) { \
    var.mulScaleZ(degrees); \
} \
void CLASS::divScaleZ(const float &degrees) { \
    var.divScaleZ(degrees); \
} \
Magnum::Matrix4 CLASS::scaleZ() const { \
    return var.scaleZ(); \
} \
void CLASS::setScale(const float &x, const float &y, const float &z) { \
    var.setScale(x, y, z); \
} \
void CLASS::addScale(const float &x, const float &y, const float &z) { \
    var.addScale(x, y, z); \
} \
void CLASS::subScale(const float &x, const float &y, const float &z) { \
    var.subScale(x, y, z); \
} \
void CLASS::mulScale(const float &x, const float &y, const float &z) { \
    var.mulScale(x, y, z); \
} \
void CLASS::divScale(const float &x, const float &y, const float &z) { \
    var.divScale(x, y, z); \
} \
Magnum::Matrix4 CLASS::scale() const { \
    return var.scale(); \
}

#define SCALE_WRAPPER__CPP(var) void saveScaleX() { \
    var.saveScaleX(); \
} \
void saveScaleY() { \
    var.saveScaleY(); \
} \
void saveScaleZ() { \
    var.saveScaleZ(); \
} \
void saveScale() { \
    var.saveScale(); \
} \
void restoreScaleX() { \
    var.restoreScaleX(); \
} \
void restoreScaleY() { \
    var.restoreScaleY(); \
} \
void restoreScaleZ() { \
    var.restoreScaleZ(); \
} \
void restoreScale() { \
    var.restoreScale(); \
} \
Magnum::Vector3 scaleVector3() const { \
    return var.scaleVector3(); \
} \
void setScaleX(const float &degrees) { \
    var.setScaleX(degrees); \
} \
void addScaleX(const float &degrees) { \
    var.addScaleX(degrees); \
} \
void subScaleX(const float &degrees) { \
    var.subScaleX(degrees); \
} \
void mulScaleX(const float &degrees) { \
    var.mulScaleX(degrees); \
} \
void divScaleX(const float &degrees) { \
    var.divScaleX(degrees); \
} \
Magnum::Matrix4 scaleX() const { \
    return var.scaleX(); \
} \
void setScaleY(const float &degrees) { \
    var.setScaleY(degrees); \
} \
void addScaleY(const float &degrees) { \
    var.addScaleY(degrees); \
} \
void subScaleY(const float &degrees) { \
    var.subScaleY(degrees); \
} \
void mulScaleY(const float &degrees) { \
    var.mulScaleY(degrees); \
} \
void divScaleY(const float &degrees) { \
    var.divScaleY(degrees); \
} \
Magnum::Matrix4 scaleY() const { \
    return var.scaleY(); \
} \
void setScaleZ(const float &degrees) { \
    var.setScaleZ(degrees); \
} \
void addScaleZ(const float &degrees) { \
    var.addScaleZ(degrees); \
} \
void subScaleZ(const float &degrees) { \
    var.subScaleZ(degrees); \
} \
void mulScaleZ(const float &degrees) { \
    var.mulScaleZ(degrees); \
} \
void divScaleZ(const float &degrees) { \
    var.divScaleZ(degrees); \
} \
Magnum::Matrix4 scaleZ() const { \
    return var.scaleZ(); \
} \
void setScale(const float &x, const float &y, const float &z) { \
    var.setScale(x, y, z); \
} \
void addScale(const float &x, const float &y, const float &z) { \
    var.addScale(x, y, z); \
} \
void subScale(const float &x, const float &y, const float &z) { \
    var.subScale(x, y, z); \
} \
void mulScale(const float &x, const float &y, const float &z) { \
    var.mulScale(x, y, z); \
} \
void divScale(const float &x, const float &y, const float &z) { \
    var.divScale(x, y, z); \
} \
Magnum::Matrix4 scale() const { \
    return var.scale(); \
}

#endif //CRAFTER_WRAPPER_SCALE_H
