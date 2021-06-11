#include "WindowlessAndroidApplicationBETA.h"


#include <android/native_window.h>
#include <pthread.h>
#include <Magnum/GL/DefaultFramebuffer.h>

#include "Magnum/GL/Version.h"

#include "Magnum/Platform/Implementation/Egl.h"

#define M_LOG(TYPE, func_name) TYPE{Corrade::Utility::TYPE::Flags::Type::NoSpace} << "Platform::WindowlessAndroidApplication::" << #func_name << "(): "
#define CHECK_EGL(name, func_name) \
{ \
    EGLint e = eglGetError(); \
    if (e == EGL_SUCCESS) { \
        M_LOG(Debug, func_name) << name << " succeeded"; \
    } else { \
        M_LOG(Error, func_name) << "cannot create EGL context: " << name << \
        " returned error: " << Magnum::Platform::Implementation::eglErrorString(e); \
    } \
}
#define CHECK_PTR(ptr) (ptr == 0 ? "(nullptr)" : ptr)

namespace Magnum { namespace Platform {

enum class WindowlessAndroidApplicationBETA::Flag: UnsignedByte {
    Redraw = 1 << 0
};

bool WindowlessAndroidApplicationBETA::acquireWindow(JNIEnv* jenv, jobject jniSurface) {
    if (jniSurface != nullptr) {
        if (egl_native_window != 0) {
            M_LOG(Error, acquireWindow)
            << "attempting to acquire a window without first releasing the previous window, "
            << "please call releaseWindow() before calling acquireWindow()";
            return false;
        }
        egl_native_window = ANativeWindow_fromSurface(jenv, jniSurface);
        return true;
    }
    M_LOG(Error, acquireWindow) << "attempting to acquire a window without a valid java surface";
    return false;
}

EGLNativeWindowType WindowlessAndroidApplicationBETA::nativeWindow() {
    return egl_native_window;
}

void WindowlessAndroidApplicationBETA::releaseWindow() {
    if (egl_native_window == 0) {
        M_LOG(Warning, releaseWindow) << "attempting to release a window that has already been released. "
                << "Ignoring call";
        return;
    }
    ANativeWindow_release(egl_native_window);
    egl_native_window = 0;
}

WindowlessAndroidApplicationBETA::WindowlessAndroidApplicationBETA() {}

bool WindowlessAndroidApplicationBETA::tryCreate(const Configuration& configuration) {
    return tryCreate(configuration, GLConfiguration{});
}

bool WindowlessAndroidApplicationBETA::tryCreate(const Configuration& configuration, const GLConfiguration& glConfiguration) {
    if (egl_init_EGL) {
        M_LOG(Error, tryCreate) << "context already exists";
        return false;
    }

    // init attributes for on screen rendering
    {
        egl_configuration_attributes = new EGLint[3]{
#ifdef MAGNUM_TARGET_GLES2
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
#elif defined(MAGNUM_TARGET_GLES3)
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
            #else
            #error Android with desktop OpenGL? Wow, that is a new thing.
#endif
                EGL_NONE
        };
        egl_configuration_attributes_list = new EGLint[3]{
#ifdef MAGNUM_TARGET_GLES2
                EGL_CONTEXT_CLIENT_VERSION, 2,
#elif defined(MAGNUM_TARGET_GLES3)
                EGL_CONTEXT_CLIENT_VERSION, 3,
            #else
            #error Android with desktop OpenGL? Wow, that is a new thing.
#endif
                EGL_NONE
        };

        egl_surface_attributes = new EGLint[15]{
#ifdef MAGNUM_TARGET_GLES2
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
#elif defined(MAGNUM_TARGET_GLES3)
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
            #else
            #error Android with desktop OpenGL? Wow, that is a new thing.
#endif
                EGL_BLUE_SIZE, glConfiguration.colorBufferSize().r(),
                EGL_GREEN_SIZE, glConfiguration.colorBufferSize().g(),
                EGL_RED_SIZE, glConfiguration.colorBufferSize().b(),
                EGL_ALPHA_SIZE, glConfiguration.colorBufferSize().a(),
                EGL_DEPTH_SIZE, glConfiguration.depthBufferSize(),
                EGL_STENCIL_SIZE, glConfiguration.stencilBufferSize(),
                EGL_NONE};
        egl_surface_type = EGL_WINDOW_BIT;
    }

    // initialize
    {
        M_LOG(Debug, tryCreate) << "initializing";

        // bind api
        {
            EGLBoolean r = eglBindAPI(EGL_OPENGL_ES_API);
            CHECK_EGL("eglBindAPI", tryCreate);
            if (r == EGL_FALSE) {
                M_LOG(Debug, tryCreate) << "failed to bind egl api";
                destroy();
                return false;
            }
        }

        // initialize display
        {
            egl_display = eglGetDisplay(egl_display_id);
            CHECK_EGL("eglGetDisplay", tryCreate);
            if (egl_display == EGL_NO_DISPLAY) {
                M_LOG(Debug, tryCreate) << "failed to obtain display from egl";
                destroy();
                return false;
            }

            egl_init_eglGetDisplay = true;

            // initialize egl with display
            {
                EGLBoolean r = eglInitialize(egl_display, &egl_eglMajVers, &egl_eglMinVers);
                CHECK_EGL("eglInitialize", tryCreate);
                if (r == EGL_FALSE) {
                    M_LOG(Debug, tryCreate) << "failed to initialize egl with target display";
                    destroy();
                    return false;
                }
                egl_init_eglInitialize = true;
            }
            M_LOG(Debug, tryCreate)
                    << "EGL initialized with version " << egl_eglMajVers << "."
                    << egl_eglMinVers;

            // print information about the display
            {
                M_LOG(Debug, tryCreate) << "EGL_CLIENT_APIS: "
                                        << CHECK_PTR(eglQueryString(
                                                egl_display,
                                                EGL_CLIENT_APIS));
                M_LOG(Debug, tryCreate) << "EGL_VENDOR: "
                                        << CHECK_PTR(eglQueryString(
                                                egl_display,
                                                EGL_VENDOR));
                M_LOG(Debug, tryCreate) << "EGL_VERSION: "
                                        << CHECK_PTR(eglQueryString(
                                                egl_display,
                                                EGL_VERSION));
                M_LOG(Debug, tryCreate) << "EGL_EXTENSIONS: "
                                        << CHECK_PTR(eglQueryString(
                                                egl_display,
                                                EGL_EXTENSIONS));
            }
            M_LOG(Debug, tryCreate) << "initialized display";
        }

        // aqcuire configuration for context
        {
            M_LOG(Debug, tryCreate)
                    << "initializing configuration";
            EGLBoolean r = eglChooseConfig(egl_display, egl_configuration_attributes,
                                           &egl_configuration, 1, &egl_number_of_configurations);
            CHECK_EGL("eglChooseConfig", tryCreate);
            if (r == EGL_FALSE) {
                M_LOG(Debug, tryCreate) << "failed to choose configuration from egl";
                destroy();
                return false;
            }
            egl_init_eglChooseConfig = true;
            M_LOG(Debug, tryCreate)
                    << "initialized configuration";
        }

        // obtain buffer format
        {
            /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
             * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
             * As soon as we picked a EGLConfig, we can safely reconfigure the
             * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
            EGLBoolean r = eglGetConfigAttrib(egl_display, egl_configuration, EGL_NATIVE_VISUAL_ID,
                                              &egl_format);
            CHECK_EGL("eglGetConfigAttrib", tryCreate);
            if (r == EGL_FALSE) {
                M_LOG(Debug, tryCreate) << "failed to obtain EGL_NATIVE_VISUAL_ID from egl config";
                destroy();
                return false;
            }
        }

        // set native buffer geometry
        {
            width = ANativeWindow_getWidth(egl_native_window);
            height = ANativeWindow_getHeight(egl_native_window);
            Vector2i v = configuration.size();
            if (v.isZero()) {
                bufferGeometryWidth = 0;
                bufferGeometryHeight = 0;
            } else {
                bufferGeometryWidth = v.x();
                bufferGeometryHeight = v.y();
            }
            int32_t r = ANativeWindow_setBuffersGeometry(egl_native_window, bufferGeometryWidth,
                                                         bufferGeometryHeight, egl_format);
            if (r != 0) {
                M_LOG(Error, tryCreate) << "failed to set native window buffer geometry";
                destroy();
                return false;
            }
        }

        // initialize surface
        {
            if (egl_surface_type == EGL_WINDOW_BIT) {
                egl_surface = eglCreateWindowSurface(egl_display, egl_configuration,
                                                     egl_native_window,
                                                     nullptr);
                CHECK_EGL("eglCreateWindowSurface", tryCreate);
                if (egl_surface == EGL_NO_SURFACE) {
                    M_LOG(Debug, tryCreate) << "failed to create egl window surface";
                    destroy();
                    return false;
                }
                egl_init_eglCreateWindowSurface = true;
            } else {
                M_LOG(Debug, tryCreate) << "failed to create egl window surface";
                destroy();
                return false;
            }
        }

        // initialize context
        {
            egl_context = eglCreateContext(egl_display, egl_configuration, egl_shared_context,
                                           egl_configuration_attributes_list);
            CHECK_EGL("eglCreateContext", tryCreate);
            if (egl_context == EGL_NO_CONTEXT) {
                M_LOG(Debug, tryCreate) << "failed to create egl context";
                destroy();
                return false;
            }
            egl_init_eglCreateContext = true;
        }

        // switch to context
        {
            EGLBoolean r = eglMakeCurrent(egl_display, egl_surface, egl_surface, egl_context);
            CHECK_EGL("eglMakeCurrent", tryCreate);
            if (r == EGL_FALSE) {
                M_LOG(Debug, tryCreate) << "failed to switch to egl context";
                destroy();
                return false;
            }
            egl_init_eglMakeCurrent = true;

            // print information about the current context
            {
                M_LOG(Debug, tryCreate) << "GL_VENDOR: "
                                        << CHECK_PTR((const char *) glGetString(
                                                GL_VENDOR));
                M_LOG(Debug, tryCreate) << "GL_RENDERER: "
                                        << CHECK_PTR((const char *) glGetString(
                                                GL_RENDERER));
                M_LOG(Debug, tryCreate) << "GL_VERSION: "
                                        << CHECK_PTR((const char *) glGetString(
                                                GL_VERSION));
                M_LOG(Debug, tryCreate)
                        << "GL_SHADING_LANGUAGE_VERSION: "
                        << CHECK_PTR((const char *) glGetString(GL_SHADING_LANGUAGE_VERSION));
                M_LOG(Debug, tryCreate) << "GL_EXTENSIONS: "
                                        << CHECK_PTR((const char *) glGetString(
                                                GL_EXTENSIONS));
            }
        }

        egl_init_EGL = true;
    }

    M_LOG(Debug, tryCreate) << "initialized EGL";

    // create magnum context
    bool ret;
    {
        magnum_context.reset(new ContextContainer());
        ret = magnum_context->context->tryCreate();
    }

    if (ret) {
        M_LOG(Debug, tryCreate) << "created magnum context";

        M_LOG(Debug, tryCreate) << "main thread: Magnum::GL::Context::hasCurrent() returns: " << Magnum::GL::Context::hasCurrent();

        // draw something
        {
            GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);
            eglSwapBuffers(egl_display, egl_surface);
        }
    } else {
        M_LOG(Debug, tryCreate) << "failed to create magnum context";
    }
    return ret;
}

void WindowlessAndroidApplicationBETA::onDraw() {
    if(_flags & Flag::Redraw) {
        _flags &= ~Flag::Redraw;
        drawEvent();
    }
}

void WindowlessAndroidApplicationBETA::destroy() {
    /* destroy everything */
    {
        /* Return early if EGL is not initialized */
        if (!egl_init_EGL) return;

        /* Destroy Magnum context first (if it exists) to avoid it potentially accessing the
           now-destroyed GL context after */
        if (magnum_context != nullptr) {
            delete magnum_context.operator->();
            magnum_context.reset(nullptr);
        }

        if (egl_init_eglMakeCurrent) {
            eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
            CHECK_EGL("eglMakeCurrent", destroy);
            egl_init_eglMakeCurrent = false;
        }
        if (egl_init_eglCreateContext) {
            eglDestroyContext(egl_display, egl_context);
            CHECK_EGL("eglDestroyContext", destroy);
            egl_context = EGL_NO_CONTEXT;
            egl_shared_context = EGL_NO_CONTEXT;
            egl_init_eglCreateContext = false;
        }
        if (egl_init_eglCreateWindowSurface || egl_init_eglCreatePbufferSurface) {
            eglDestroySurface(egl_display, egl_surface);
            CHECK_EGL("eglDestroySurface", destroy);
            egl_surface = EGL_NO_SURFACE;
            egl_init_eglCreateWindowSurface = false;
            egl_init_eglCreatePbufferSurface = false;
        }
        if (egl_init_eglInitialize) {
            eglTerminate(egl_display);
            CHECK_EGL("eglTerminate", destroy);
            egl_init_eglInitialize = false;
        }
        if (egl_init_eglGetDisplay) {
            egl_display = EGL_NO_DISPLAY;
            egl_init_eglGetDisplay = false;
        }
        if (egl_configuration_attributes != nullptr) delete[] egl_configuration_attributes;
        if (egl_configuration_attributes_list != nullptr)
            delete[] egl_configuration_attributes_list;
        if (egl_surface_attributes != nullptr) delete[] egl_surface_attributes;
        egl_init_EGL = false;
    }
}

WindowlessAndroidApplicationBETA::~WindowlessAndroidApplicationBETA() {
    destroy();
    releaseWindow();
}

void WindowlessAndroidApplicationBETA::setSurface(JNIEnv* jenv, jobject jniSurface) {
    if (acquireWindow(jenv, jniSurface)) {
        tryCreate(Configuration{}, GLConfiguration{});
    } else {
        destroy();
        releaseWindow();
    }
}

WindowlessAndroidApplicationBETA::GLConfiguration::GLConfiguration():
    _colorBufferSize{8, 8, 8, 8}, _depthBufferSize{24}, _stencilBufferSize{0} {}

Vector2i WindowlessAndroidApplicationBETA::framebufferSize() const {
    return {width,height};
}

void WindowlessAndroidApplicationBETA::swapBuffers() {
    eglSwapBuffers(egl_display, egl_surface);
}

void WindowlessAndroidApplicationBETA::redraw() {
    _flags |= Flag::Redraw;
}

void WindowlessAndroidApplicationBETA::viewportEvent(ViewportEvent& event) {
    static_cast<void>(event);
}

void WindowlessAndroidApplicationBETA::mousePressEvent(MouseEvent&) {}
void WindowlessAndroidApplicationBETA::mouseReleaseEvent(MouseEvent&) {}
void WindowlessAndroidApplicationBETA::mouseMoveEvent(MouseMoveEvent&) {}

}}