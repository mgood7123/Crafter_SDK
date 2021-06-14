//
// Created by Matthew Good on 6/6/21.
//

#ifndef CRAFTER_PACKAGE_H
#define CRAFTER_PACKAGE_H

#include <Corrade/Corrade.h>

#ifdef CORRADE_TARGET_ANDROID
#include <Magnum/Platform/WindowlessAndroidApplication.h>
#else
#include <Magnum/Platform/Sdl2Application.h>
#endif

namespace Crafter {
    class Package : public
#ifdef CORRADE_TARGET_ANDROID
        Magnum::Platform::WindowlessAndroidApplication
#else
        Magnum::Platform::Sdl2Application
#endif
    {
#ifdef CORRADE_TARGET_ANDROID
    public:
        /** @brief Application arguments */
        struct Arguments {
            /** @brief Constructor */
            /*implicit*/ constexpr Arguments(int& argc, char** argv) noexcept: argc{argc}, argv{argv} {}

            int& argc;      /**< @brief Argument count */
            char** argv;    /**< @brief Argument values */
        };
        // On android, we provide a callback to call the
        // Java side eglSwapBuffers(EGLDisplay, EGLSurface)
        //
        // This allows magnum to draw correctly on android
        // and prevents flickering due to double buffering
        explicit Package(const Arguments &arguments, JNIEnv *jenv, jobject classInstance, jstring name, jstring signature);
#else
    public:
        typedef Magnum::Platform::Sdl2Application::Arguments Arguments;
        explicit Package(const Arguments &arguments);
#endif
        Arguments applicationArguments;

        virtual void setup();
    };
}

#ifdef CORRADE_TARGET_ANDROID

#define switchIfNeeded \
if ( \
        Magnum::Platform::GLContext::hasCurrent() && \
        &Magnum::Platform::GLContext::current() != &magnum_context->context->current() \
) { \
    Magnum::Debug{} << "switching contexts"; \
    Magnum::Platform::GLContext::makeCurrent(&magnum_context->context->current()); \
}

/**
 * JAVA methods provided:
 * <li> native long createNativeInstance();
 * <li> native void onDraw(long instance);
 * <li> native boolean onTouchEvent(long instance, float[] motionEvent);
 * <li> native void onEglSetup(long instance, String name, String signature);
 * <li> native void surfaceChanged(long instance, int w, int h);
 * <li> native void onEglTearDown(long instance);
 */
#define CRAFTER_PACKAGE_MAIN(jniPackage, className, argc, argv) \
class jniPackage##_ANDROID_DEFERRED_CREATION {                               \
public:                                                            \
    Magnum::Platform::WindowlessAndroidApplication::ContextContainer * magnum_context = nullptr; \
    Crafter::Package::Arguments applicationArguments; \
    className * clazz = nullptr; \
    explicit jniPackage##_ANDROID_DEFERRED_CREATION(const Crafter::Package::Arguments &arguments) \
    : applicationArguments(arguments) {} \
    void onDraw() {                                             \
        if (clazz != nullptr) { \
            switchIfNeeded; \
            clazz->onDraw(); \
        } \
    } \
    bool onTouchEvent(JNIEnv *jenv, jfloatArray motionEventData) { \
        if (clazz != nullptr) { \
            switchIfNeeded; \
            return clazz->onTouchEvent(jenv, motionEventData);  \
        }                                                       \
        return false;                                           \
    }                                                           \
    void onEglSetup(JNIEnv *jenv, jobject classInstance, jstring name, jstring signature) { \
        magnum_context = new Magnum::Platform::WindowlessAndroidApplication::ContextContainer(); \
        if (Magnum::Platform::GLContext::hasCurrent()) {        \
            Magnum::Platform::GLContext::makeCurrent(nullptr); \
        } \
        if (!magnum_context->context->tryCreate()) { \
            Magnum::Error{ Corrade::Utility::Error::Flags::Type::NoSpace}<< #jniPackage << "_ANDROID_DEFERRED_CREATION::"<<"onEglSetup"<<"(): " << "failed to create magnum context"; \
        } else { \
            Magnum::Debug{ Corrade::Utility::Debug::Flags::Type::NoSpace}<< #jniPackage << "_ANDROID_DEFERRED_CREATION::"<<"onEglSetup"<<"(): " << "created magnum context"; \
            clazz = new className{applicationArguments, jenv, classInstance, name, signature};        \
            clazz->magnum_context = magnum_context;             \
            Magnum::Debug{ Corrade::Utility::Debug::Flags::Type::NoSpace}<< #jniPackage << "_ANDROID_DEFERRED_CREATION::"<<"onEglSetup"<<"(): " << "created APP"; \
            clazz->setup(); \
            clazz->redraw(); \
        } \
    } \
    void surfaceChanged(int w, int h) { \
        if (clazz != nullptr) { \
            switchIfNeeded; \
            clazz->surfaceChanged(w, h); \
        } \
    } \
    void onEglTearDown() {                                   \
        if (magnum_context != nullptr) {                        \
            switchIfNeeded; \
            Magnum::Debug{ Corrade::Utility::Debug::Flags::Type::NoSpace}<< #jniPackage << "_ANDROID_DEFERRED_CREATION::"<<"onEglTearDown"<<"(): " << "destroying APP"; \
            delete clazz; \
            clazz->magnum_context = nullptr;                    \
            Magnum::Platform::GLContext::makeCurrent(nullptr); \
            Magnum::Debug{ Corrade::Utility::Debug::Flags::Type::NoSpace}<< #jniPackage << "_ANDROID_DEFERRED_CREATION::"<<"onEglTearDown"<<"(): " << "set context as nullptr"; \
            delete magnum_context; \
            magnum_context = nullptr; \
            Magnum::Debug{ Corrade::Utility::Debug::Flags::Type::NoSpace}<< #jniPackage << "_ANDROID_DEFERRED_CREATION::"<<"onEglTearDown"<<"(): " << "destroyed magnum context"; \
        } \
    } \
}; \
extern "C" \
JNIEXPORT jlong JNICALL \
jniPackage##_createNativeInstance(JNIEnv *jenv, jobject type) { \
    return reinterpret_cast<jlong>(\
        new jniPackage##_ANDROID_DEFERRED_CREATION(\
            {argc, argv} \
        )\
    ); \
} \
 \
extern "C" \
JNIEXPORT void JNICALL \
jniPackage##_onDraw(JNIEnv *jenv, jobject type, jlong instance) { \
    reinterpret_cast<jniPackage##_ANDROID_DEFERRED_CREATION*>(instance)->onDraw(); \
} \
 \
extern "C" \
JNIEXPORT jboolean JNICALL \
jniPackage##_onTouchEvent(JNIEnv *jenv, jobject type, jlong instance, jfloatArray motionEventData) { \
    return reinterpret_cast<jniPackage##_ANDROID_DEFERRED_CREATION*>(instance)->onTouchEvent(jenv, motionEventData); \
} \
 \
extern "C" \
JNIEXPORT void JNICALL \
jniPackage##_onEglSetup(JNIEnv *jenv, jobject type, jlong instance, jobject classInstance, jstring name, jstring signature) { \
    reinterpret_cast<jniPackage##_ANDROID_DEFERRED_CREATION*>(instance)->onEglSetup(jenv, classInstance, name, signature); \
} \
 \
extern "C" \
JNIEXPORT void JNICALL \
jniPackage##_surfaceChanged(JNIEnv *jenv, jobject type, jlong instance, jint w, jint h) { \
    reinterpret_cast<jniPackage##_ANDROID_DEFERRED_CREATION*>(instance)->surfaceChanged(w, h); \
} \
 \
extern "C" \
JNIEXPORT void JNICALL \
jniPackage##_onEglTearDown(JNIEnv *jenv, jobject type, jlong instance) { \
    reinterpret_cast<jniPackage##_ANDROID_DEFERRED_CREATION*>(instance)->onEglTearDown(); \
}
#else

/* rely on header def guards */

#ifdef Magnum_Platform_GlxApplication_h
#define CRAFTER_PACKAGE_MAIN(jniPackage, className, argc_, argv_) \
    int main(int argc, char** argv) {                   \
        className app({argc_, argv_});                  \
        app.setup();                                    \
        return app.exec();                              \
    }
#else

#ifdef Magnum_Platform_AndroidApplication_h
#define CRAFTER_PACKAGE_MAIN(jniPackage, className, argc_, argv_) \
    extern "C" CORRADE_VISIBILITY_EXPORT void android_main(android_app* state); \
    extern "C" void android_main(android_app* state) {            \
        Magnum::Platform::AndroidApplication::instancer & i = Magnum::Platform::AndroidApplication::instancer<className>{argc_, argv_}; \
        i.instance.setup();                                                          \
        Magnum::Platform::AndroidApplication::exec(state, i);    \
    }
#else

#ifdef Magnum_Platform_EmscriptenApplication_h
#define CRAFTER_PACKAGE_MAIN(jniPackage, className, argc_, argv_) \
    namespace { Corrade::Containers::Pointer<className> emscriptenApplicationInstance ; } \
    int main(int argc, char** argv) {                             \
        emscriptenApplicationInstance.reset(new className{{argc_, argv_}});   \
        emscriptenApplicationInstance->setup();                   \
        return emscriptenApplicationInstance->exec();             \
    }
#else

#ifdef Magnum_Platform_GlfwApplication_h
#define CRAFTER_PACKAGE_MAIN(jniPackage, className, argc_, argv_) \
    int main(int argc, char** argv) {                             \
        className app({argc_, argv_});                            \
        app.setup();                                              \
        return app.exec();                                        \
    }
#else

#ifdef Magnum_Platform_Sdl2Application_h
#ifndef CORRADE_TARGET_WINDOWS_RT
#define CRAFTER_PACKAGE_MAIN(jniPackage, className, argc_, argv_) \
    int main(int argc, char** argv) {                             \
        className app({argc_, argv_});                            \
        app.setup();                                              \
        return app.exec();                                        \
    }
#else
#define CRAFTER_PACKAGE_MAIN(jniPackage, className, argc_, argv_) \
    int main(int argc, char** argv) {                             \
        className app({argc_, argv_});                            \
        app.setup();                                              \
        return app.exec();                                        \
    }                                                             \
    __pragma(warning(push))                                       \
    __pragma(warning(disable: 4447))                              \
    int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {      \
        if(FAILED(Windows::Foundation::Initialize(RO_INIT_MULTITHREADED)))  \
            return 1;                                             \
        return SDL_WinRTRunApp(main, nullptr);                    \
    }                                                             \
    __pragma(warning(pop))
#endif
#else

#ifdef Magnum_Platform_WindowlessCglApplication_h
#define CRAFTER_PACKAGE_MAIN(jniPackage, className, argc_, argv_) \
    int main(int argc, char** argv) {                             \
        className app({argc_, argv_});                            \
        app.setup();                                              \
        return app.exec();                                        \
    }
#else

#ifdef Magnum_Platform_WindowlessEglApplication_h
#define CRAFTER_PACKAGE_MAIN(jniPackage, className, argc_, argv_) \
    int main(int argc, char** argv) {                             \
        className app({argc_, argv_});                            \
        app.setup();                                              \
        return app.exec();                                        \
    }
#else

#ifdef Magnum_Platform_WindowlessGlxApplication_h
#define CRAFTER_PACKAGE_MAIN(jniPackage, className, argc_, argv_) \
    int main(int argc, char** argv) {                             \
        className app({argc_, argv_});                            \
        app.setup();                                              \
        return app.exec();                                        \
    }
#else

#ifdef Magnum_Platform_WindowlessIosApplication_h
#define CRAFTER_PACKAGE_MAIN(jniPackage, className, argc_, argv_) \
    int main(int argc, char** argv) {                             \
        className app({argc_, argv_});                            \
        app.setup();                                              \
        return app.exec();                                        \
    }
#else

#ifdef Magnum_Platform_WindowlessWglApplication_h
#define CRAFTER_PACKAGE_MAIN(jniPackage, className, argc_, argv_) \
    int main(int argc, char** argv) {                             \
        className app({argc_, argv_});                            \
        app.setup();                                              \
        return app.exec();                                        \
    }
#else

#ifdef Magnum_Platform_WindowlessWindowsEglApplication_h
#define CRAFTER_PACKAGE_MAIN(jniPackage, className, argc_, argv_) \
    int main(int argc, char** argv) {                             \
        className app({argc_, argv_});                            \
        app.setup();                                              \
        return app.exec();                                        \
    }
#else

#ifdef Magnum_Platform_XEglApplication_h
#define CRAFTER_PACKAGE_MAIN(jniPackage, className, argc_, argv_) \
    int main(int argc, char** argv) {                             \
        className app({argc_, argv_});                            \
        app.setup();                                              \
        return app.exec();                                        \
    }
#else
#error unknown package implementation for current platform
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#endif //CRAFTER_PACKAGE_H
