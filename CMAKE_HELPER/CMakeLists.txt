cmake_minimum_required(VERSION 3.4.1)

# empty macro, for checking import of cmake file
macro(Crafter_SDK_CMAKE_HELPER)
endmacro()

macro(print_variable_Crafter_SDK variable)
    message(STATUS "${variable} = ${${variable}}")
endmacro()

macro(set_Crafter_SDK_ROOT Crafter_SDK)
    set(Crafter_SDK_ROOT ${Crafter_SDK})
    set(PREFIX_PARENT_Crafter_SDK EXPORTED_LIBRARIES)
    set(LIBRARY_PATH_Crafter_SDK ${PREFIX_PARENT_Crafter_SDK}/${CMAKE_ANDROID_ARCH_ABI})
#    print_variable_Crafter_SDK(Crafter_SDK_ROOT)
#    print_variable_Crafter_SDK(PREFIX_PARENT_Crafter_SDK)
#    print_variable_Crafter_SDK(LIBRARY_PATH_Crafter_SDK)
endmacro()

macro(set_module_name_Crafter_SDK module_name)
    set(Crafter_SDK_MODULE_NAME ${module_name})
    set(Crafter_SDK_MODULE_NAME_ROOT ${Crafter_SDK_ROOT}/${Crafter_SDK_MODULE_NAME})
    set(Crafter_SDK_LIBRARY_EXPORT_PREFIX ${Crafter_SDK_MODULE_NAME_ROOT}/${LIBRARY_PATH_Crafter_SDK})
    set(Crafter_SDK_MODULE_TARGET Crafter_${Crafter_SDK_MODULE_NAME})
endmacro()

macro(Crafter_SDK_CMAKE_HELPER_import_header SDK)
    include_directories(${Crafter_SDK_ROOT}/${SDK}/include)
endmacro()

macro(Crafter_SDK_CMAKE_HELPER_import_library SDK)
    add_library(Crafter_${SDK} SHARED IMPORTED)
    set_target_properties(Crafter_${SDK}
            PROPERTIES IMPORTED_LOCATION
            ${Crafter_SDK_ROOT}/${SDK}/${LIBRARY_PATH_Crafter_SDK}/libCrafter_${SDK}.so
    )
endmacro()

macro(import_test_builder)
    if(NOT COMMAND testBuilder_build)
        add_subdirectory(${Crafter_SDK_ROOT}/testBuilder ${CMAKE_CURRENT_BINARY_DIR}/testBuilder)
        testBuilder_set_current_working_directory_to_default_binary_directory()
    endif()
endmacro()

macro(import_project__Crafter_Magnum)
    if (NOT CRAFTER_IMPORTED_MAGNUM)
        set(CMAKE_MODULE_PATH "${Crafter_SDK_ROOT}/Crafter_Magnum/modules/" ${CMAKE_MODULE_PATH})

        if(CMAKE_SYSTEM_NAME STREQUAL Emscripten)
            set(CORRADE_TARGET_EMSCRIPTEN 1)
        elseif(UNIX)
            # Both APPLE and UNIX are defined on OSX
            if(APPLE)
                set(CORRADE_TARGET_APPLE 1)

                if(CMAKE_OSX_SYSROOT MATCHES "/iPhoneOS[0-9.]*\\.sdk")
                    set(CORRADE_TARGET_IOS 1)
                elseif(CMAKE_OSX_SYSROOT MATCHES "/iPhoneSimulator[0-9.]*\\.sdk")
                    set(CORRADE_TARGET_IOS 1)
                    set(CORRADE_TARGET_IOS_SIMULATOR 1)
                endif()
            endif()

            # UNIX is also defined on Android
            if(CMAKE_SYSTEM_NAME STREQUAL Android)
                set(CORRADE_TARGET_ANDROID 1)
            endif()

            # Emscripten is Unix too, this selects only the other ones
            set(CORRADE_TARGET_UNIX 1)
        elseif(WIN32)
            set(CORRADE_TARGET_WINDOWS 1)

            if(WINDOWS_PHONE OR WINDOWS_STORE)
                set(CORRADE_TARGET_WINDOWS_RT 1)
            endif()
        endif()

        if(CORRADE_TARGET_ANDROID)
            message(STATUS "compiling corrade-rc for host")
            execute_process(COMMAND mkdir ${Crafter_SDK_ROOT}/Crafter_Magnum/corrade_BUILD_HOST)
            execute_process(
                    WORKING_DIRECTORY ${Crafter_SDK_ROOT}/Crafter_Magnum/corrade_BUILD_HOST
                    COMMAND cmake ${Crafter_SDK_ROOT}/Crafter_Magnum/corrade
            )
            execute_process(
                    WORKING_DIRECTORY ${Crafter_SDK_ROOT}/Crafter_Magnum/corrade_BUILD_HOST
                    COMMAND make install
            )
            execute_process(COMMAND rm -rf ${Crafter_SDK_ROOT}/Crafter_Magnum/corrade_BUILD_HOST)
        endif()

        add_subdirectory(${Crafter_SDK_ROOT}/Crafter_Magnum/corrade EXCLUDE_FROM_ALL ${CMAKE_CURRENT_BINARY_DIR}/corrade)

        # Add Magnum as a subproject
        set(WITH_GL ON CACHE BOOL "" FORCE)
        set(TARGET_GL ON CACHE BOOL "" FORCE)
        if(CORRADE_TARGET_ANDROID)
            set(WITH_WINDOWLESSANDROIDAPPLICATION ON CACHE BOOL "" FORCE)
            set(TARGET_GLES ON CACHE BOOL "" FORCE)
            set(TARGET_GLES2 OFF CACHE BOOL "" FORCE)
            set(WITH_EGLCONTEXT ON CACHE BOOL "" FORCE)
        else()
           set(WITH_SDL2APPLICATION ON CACHE BOOL "" FORCE)
        endif()

        add_subdirectory(${Crafter_SDK_ROOT}/Crafter_Magnum/magnum EXCLUDE_FROM_ALL ${CMAKE_CURRENT_BINARY_DIR}/magnum)

        if(CORRADE_TARGET_ANDROID)
            find_package(Magnum REQUIRED GL WindowlessAndroidApplication)
        else()
            find_package(Magnum REQUIRED GL Sdl2Application)
        endif()

        import_test_builder()

        testBuilder_add_source(Crafter_Magnum ${Crafter_SDK_ROOT}/Crafter_Magnum/empty.cpp)
        testBuilder_add_library(Crafter_Magnum Magnum::DebugTools)
        testBuilder_add_library(Crafter_Magnum Magnum::GL)
        testBuilder_add_library(Crafter_Magnum Magnum::Magnum)
        testBuilder_add_library(Crafter_Magnum Magnum::MeshTools)
        testBuilder_add_library(Crafter_Magnum Magnum::Primitives)
        testBuilder_add_library(Crafter_Magnum Magnum::SceneGraph)
        testBuilder_add_library(Crafter_Magnum Magnum::Shaders)
        testBuilder_add_library(Crafter_Magnum Magnum::TextureTools)
        testBuilder_add_library(Crafter_Magnum Magnum::Trade)
        if(NOT CORRADE_TARGET_ANDROID)
            testBuilder_add_library(Crafter_Magnum Magnum::Application)
        else()
            testBuilder_add_library(Crafter_Magnum Magnum::EglContext)
            testBuilder_add_library(Crafter_Magnum Magnum::WindowlessAndroidApplication)
            testBuilder_add_library(Crafter_Magnum android)
            testBuilder_add_library(Crafter_Magnum log)
            testBuilder_add_library(Crafter_Magnum EGL)
            testBuilder_add_library(Crafter_Magnum GLESv3)
        endif()
        testBuilder_build_static_library(Crafter_Magnum)
        set(CRAFTER_IMPORTED_MAGNUM 1)
    endif()
endmacro()

macro(import_project__Crafter_Core)
    if (NOT CRAFTER_IMPORTED_MAGNUM)
        import_project__Crafter_Magnum()
    endif()
    if (NOT CRAFTER_IMPORTED_CORE)
        include_directories(${Crafter_SDK_ROOT}/Crafter_Core/src)
        testBuilder_add_source(Crafter_Core ${Crafter_SDK_ROOT}/Crafter_Core/src/Crafter/PackageDemos.cpp)
        testBuilder_add_source(Crafter_Core ${Crafter_SDK_ROOT}/Crafter_Core/src/Crafter/CrafterPackage.cpp)
        testBuilder_add_library(Crafter_Core Crafter_Magnum)
        testBuilder_build_static_library(Crafter_Core)
        set(CRAFTER_IMPORTED_CORE 1)
    endif()
endmacro()

macro(export_library_Crafter_SDK)
    add_custom_command(
            TARGET ${Crafter_SDK_MODULE_TARGET}
            POST_BUILD
            COMMAND mkdir ${Crafter_SDK_MODULE_NAME_ROOT}/${PREFIX_PARENT_Crafter_SDK} || true
    )

    add_custom_command(
            TARGET ${Crafter_SDK_MODULE_TARGET}
            POST_BUILD
            COMMAND mkdir ${Crafter_SDK_LIBRARY_EXPORT_PREFIX} || true
    )
    add_custom_command(
            TARGET ${Crafter_SDK_MODULE_TARGET}
            POST_BUILD
            COMMAND cp -v $<TARGET_FILE:${Crafter_SDK_MODULE_TARGET}> ${Crafter_SDK_LIBRARY_EXPORT_PREFIX}
    )
endmacro()