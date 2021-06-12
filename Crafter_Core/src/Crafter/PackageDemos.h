//
// Created by Matthew Good on 6/6/21.
//

#ifndef CRAFTER_PACKAGEDEMOS_H
#define CRAFTER_PACKAGEDEMOS_H

#include "CrafterPackage.h"

#ifdef CORRADE_TARGET_ANDROID
#define CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_HPP(class_) explicit class_(const Arguments &arguments, JNIEnv *jenv, jobject classInstance, jstring name, jstring signature)
#define CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_CPP(class_, className) class_::className(const Arguments &arguments, JNIEnv *jenv, jobject classInstance, jstring name, jstring signature) : Crafter::Package{arguments, jenv, classInstance, name, signature} {}
#else
#define CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_HPP(class_) explicit class_(const Arguments &arguments)
#define CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_CPP(class_, className) class_::className(const Arguments &arguments) : Crafter::Package{arguments} {}
#endif

#include "../packages/triangle.h"
#include "../packages/cube.h"
#include "../packages/egl_cube.h"
#include "../packages/polygonBlueprint.h"

#endif //CRAFTER_PACKAGEDEMOS_H
