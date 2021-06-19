//
// Created by Matthew Good on 17/6/21.
//

#ifndef CRAFTER_WRAPPER_TRANSLATION_H
#define CRAFTER_WRAPPER_TRANSLATION_H

#include <Magnum/Magnum.h> // Magnum:: typedefs
#include <Magnum/Math/Matrix4.h> // Magnum::Matrix4

#define TRANSLATION_WRAPPER_HEADER virtual void saveTranslationX(); \
virtual void saveTranslationY(); \
virtual void saveTranslationZ(); \
virtual void saveTranslation(); \
virtual void restoreTranslationX(); \
virtual void restoreTranslationY(); \
virtual void restoreTranslationZ(); \
virtual void restoreTranslation(); \
virtual Magnum::Vector3 translationVector3() const; \
virtual void setTranslationX(const float &degrees); \
virtual void addTranslationX(const float &degrees); \
virtual void subTranslationX(const float &degrees); \
virtual void mulTranslationX(const float &degrees); \
virtual void divTranslationX(const float &degrees); \
virtual Magnum::Matrix4 translationX() const; \
virtual void setTranslationY(const float &degrees); \
virtual void addTranslationY(const float &degrees); \
virtual void subTranslationY(const float &degrees); \
virtual void mulTranslationY(const float &degrees); \
virtual void divTranslationY(const float &degrees); \
virtual Magnum::Matrix4 translationY() const; \
virtual void setTranslationZ(const float &degrees); \
virtual void addTranslationZ(const float &degrees); \
virtual void subTranslationZ(const float &degrees); \
virtual void mulTranslationZ(const float &degrees); \
virtual void divTranslationZ(const float &degrees); \
virtual Magnum::Matrix4 translationZ() const; \
virtual void setTranslation(const float &x, const float &y, const float &z); \
virtual void addTranslation(const float &x, const float &y, const float &z); \
virtual void subTranslation(const float &x, const float &y, const float &z); \
virtual void mulTranslation(const float &x, const float &y, const float &z); \
virtual void divTranslation(const float &x, const float &y, const float &z); \
virtual Magnum::Matrix4 translation() const; \
static Magnum::Matrix4 translationDistance(const Magnum::Matrix4 &A, const Magnum::Matrix4 &B);

#define TRANSLATION_WRAPPER_CPP(CLASS, var) void CLASS::saveTranslationX() { \
    var.saveTranslationX(); \
} \
void CLASS::saveTranslationY() { \
    var.saveTranslationY(); \
} \
void CLASS::saveTranslationZ() { \
    var.saveTranslationZ(); \
} \
void CLASS::saveTranslation() { \
    var.saveTranslation(); \
} \
void CLASS::restoreTranslationX() { \
    var.restoreTranslationX(); \
} \
void CLASS::restoreTranslationY() { \
    var.restoreTranslationY(); \
} \
void CLASS::restoreTranslationZ() { \
    var.restoreTranslationZ(); \
} \
void CLASS::restoreTranslation() { \
    var.restoreTranslation(); \
} \
Magnum::Vector3 CLASS::translationVector3() const { \
    return var.translationVector3(); \
} \
void CLASS::setTranslationX(const float &degrees) { \
    var.setTranslationX(degrees); \
} \
void CLASS::addTranslationX(const float &degrees) { \
    var.addTranslationX(degrees); \
} \
void CLASS::subTranslationX(const float &degrees) { \
    var.subTranslationX(degrees); \
} \
void CLASS::mulTranslationX(const float &degrees) { \
    var.mulTranslationX(degrees); \
} \
void CLASS::divTranslationX(const float &degrees) { \
    var.divTranslationX(degrees); \
} \
Magnum::Matrix4 CLASS::translationX() const { \
    return var.translationX(); \
} \
void CLASS::setTranslationY(const float &degrees) { \
    var.setTranslationY(degrees); \
} \
void CLASS::addTranslationY(const float &degrees) { \
    var.addTranslationY(degrees); \
} \
void CLASS::subTranslationY(const float &degrees) { \
    var.subTranslationY(degrees); \
} \
void CLASS::mulTranslationY(const float &degrees) { \
    var.mulTranslationY(degrees); \
} \
void CLASS::divTranslationY(const float &degrees) { \
    var.divTranslationY(degrees); \
} \
Magnum::Matrix4 CLASS::translationY() const { \
    return var.translationY(); \
} \
void CLASS::setTranslationZ(const float &degrees) { \
    var.setTranslationZ(degrees); \
} \
void CLASS::addTranslationZ(const float &degrees) { \
    var.addTranslationZ(degrees); \
} \
void CLASS::subTranslationZ(const float &degrees) { \
    var.subTranslationZ(degrees); \
} \
void CLASS::mulTranslationZ(const float &degrees) { \
    var.mulTranslationZ(degrees); \
} \
void CLASS::divTranslationZ(const float &degrees) { \
    var.divTranslationZ(degrees); \
} \
Magnum::Matrix4 CLASS::translationZ() const { \
    return var.translationZ(); \
} \
void CLASS::setTranslation(const float &x, const float &y, const float &z) { \
    var.setTranslation(x, y, z); \
} \
void CLASS::addTranslation(const float &x, const float &y, const float &z) { \
    var.addTranslation(x, y, z); \
} \
void CLASS::subTranslation(const float &x, const float &y, const float &z) { \
    var.subTranslation(x, y, z); \
} \
void CLASS::mulTranslation(const float &x, const float &y, const float &z) { \
    var.mulTranslation(x, y, z); \
} \
void CLASS::divTranslation(const float &x, const float &y, const float &z) { \
    var.divTranslation(x, y, z); \
} \
Magnum::Matrix4 CLASS::translation() const { \
    return var.translation(); \
} \
Magnum::Matrix4 CLASS::translationDistance(const Magnum::Matrix4 &A, const Magnum::Matrix4 &B) { \
    return Translation::translationDistance(A, B); \
}

#define TRANSLATION_WRAPPER__CPP(var) void saveTranslationX() { \
    var.saveTranslationX(); \
} \
void saveTranslationY() { \
    var.saveTranslationY(); \
} \
void saveTranslationZ() { \
    var.saveTranslationZ(); \
} \
void saveTranslation() { \
    var.saveTranslation(); \
} \
void restoreTranslationX() { \
    var.restoreTranslationX(); \
} \
void restoreTranslationY() { \
    var.restoreTranslationY(); \
} \
void restoreTranslationZ() { \
    var.restoreTranslationZ(); \
} \
void restoreTranslation() { \
    var.restoreTranslation(); \
} \
void setTranslationX(const float &degrees) { \
    var.setTranslationX(degrees); \
} \
void addTranslationX(const float &degrees) { \
    var.addTranslationX(degrees); \
} \
void subTranslationX(const float &degrees) { \
    var.subTranslationX(degrees); \
} \
void mulTranslationX(const float &degrees) { \
    var.mulTranslationX(degrees); \
} \
void divTranslationX(const float &degrees) { \
    var.divTranslationX(degrees); \
} \
Magnum::Matrix4 translationX() const { \
    return var.translationX(); \
} \
Magnum::Vector3 translationVector3() const { \
    return var.translationVector3(); \
} \
void setTranslationY(const float &degrees) { \
    var.setTranslationY(degrees); \
} \
void addTranslationY(const float &degrees) { \
    var.addTranslationY(degrees); \
} \
void subTranslationY(const float &degrees) { \
    var.subTranslationY(degrees); \
} \
void mulTranslationY(const float &degrees) { \
    var.mulTranslationY(degrees); \
} \
void divTranslationY(const float &degrees) { \
    var.divTranslationY(degrees); \
} \
Magnum::Matrix4 translationY() const { \
    return var.translationY(); \
} \
void setTranslationZ(const float &degrees) { \
    var.setTranslationZ(degrees); \
} \
void addTranslationZ(const float &degrees) { \
    var.addTranslationZ(degrees); \
} \
void subTranslationZ(const float &degrees) { \
    var.subTranslationZ(degrees); \
} \
void mulTranslationZ(const float &degrees) { \
    var.mulTranslationZ(degrees); \
} \
void divTranslationZ(const float &degrees) { \
    var.divTranslationZ(degrees); \
} \
Magnum::Matrix4 translationZ() const { \
    return var.translationZ(); \
} \
void setTranslation(const float &x, const float &y, const float &z) { \
    var.setTranslation(x, y, z); \
} \
void addTranslation(const float &x, const float &y, const float &z) { \
    var.addTranslation(x, y, z); \
} \
void subTranslation(const float &x, const float &y, const float &z) { \
    var.subTranslation(x, y, z); \
} \
void mulTranslation(const float &x, const float &y, const float &z) { \
    var.mulTranslation(x, y, z); \
} \
void divTranslation(const float &x, const float &y, const float &z) { \
    var.divTranslation(x, y, z); \
} \
Magnum::Matrix4 translation() const { \
    return var.translation(); \
} \
static Magnum::Matrix4 translationDistance(const Magnum::Matrix4 &A, const Magnum::Matrix4 &B) { \
    return Translation::translationDistance(A, B); \
}

#endif //CRAFTER_WRAPPER_TRANSLATION_H
