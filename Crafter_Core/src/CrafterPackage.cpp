//
// Created by Matthew Good on 6/6/21.
//

#include "CrafterPackage.h"

Crafter::Package::Package(
        const Arguments &arguments
#ifdef CORRADE_TARGET_ANDROID
        , JNIEnv *jenv, jobject classInstance, jstring name, jstring signature
#endif
)
:
#ifdef CORRADE_TARGET_ANDROID
WindowlessAndroidApplication(
        jenv,
        classInstance,
        name,
        signature
),
#else
Sdl2Application(
        arguments,
        Configuration{}
            .setWindowFlags(Configuration::WindowFlag::Resizable)
),
#endif
applicationArguments{arguments}
{
    // unused
}

void Crafter::Package::setup() {}
