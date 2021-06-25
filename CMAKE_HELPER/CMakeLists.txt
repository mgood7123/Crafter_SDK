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
    if(NOT COMMAND testBuilder_set_current_working_directory_to_default_binary_directory)
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
        set(WITH_MAGNUMFONT ON CACHE BOOL "" FORCE)
        set(WITH_TEXT ON CACHE BOOL "" FORCE)
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

        # add UI extra

        set(WITH_UI ON CACHE BOOL "" FORCE)
        add_subdirectory(${Crafter_SDK_ROOT}/Crafter_Magnum/magnum-extras EXCLUDE_FROM_ALL ${CMAKE_CURRENT_BINARY_DIR}/magnum-extras)

        # add font plugins

        add_subdirectory(${Crafter_SDK_ROOT}/Crafter_Magnum/freetype-cmake ${CMAKE_CURRENT_BINARY_DIR}/freetype-cmake)
        freetype_cmake_include_freetype(${Crafter_SDK_ROOT}/Crafter_Magnum/freetype-cmake)

        set(WITH_STBTRUETYPEFONT ON CACHE BOOL "" FORCE)
        set(WITH_FREETYPEFONT ON CACHE BOOL "" FORCE)
        add_subdirectory(${Crafter_SDK_ROOT}/Crafter_Magnum/magnum-plugins EXCLUDE_FROM_ALL ${CMAKE_CURRENT_BINARY_DIR}/magnum-plugins)
        include_directories(${CMAKE_CURRENT_BINARY_DIR}/magnum-plugins/src)
        include_directories(${Crafter_SDK_ROOT}/Crafter_Magnum/magnum-plugins/src)

        find_package(MagnumPlugins REQUIRED FreeTypeFont)
        find_package(MagnumPlugins REQUIRED StbTrueTypeFont)

        if(CORRADE_TARGET_ANDROID)
            find_package(Magnum REQUIRED GL WindowlessAndroidApplication)
        else()
            find_package(Magnum REQUIRED GL Sdl2Application)
        endif()

        import_test_builder()

        add_library(Crafter_Magnum SHARED ${Crafter_SDK_ROOT}/Crafter_Magnum/empty.cpp)
        add_dependencies(FreeTypeFont FREETYPE_CMAKE_LIB_FREETYPE)
        add_dependencies(StbTrueTypeFont FreeTypeFont)
        add_dependencies(MagnumFont StbTrueTypeFont)
        add_dependencies(Crafter_Magnum MagnumFont)
        add_dependencies(MagnumUi MagnumFont)
        if(NOT CORRADE_TARGET_ANDROID)
            set(PLATFORM_LIBS Magnum::Application)
        else()
            set(PLATFORM_LIBS Magnum::EglContext Magnum::WindowlessAndroidApplication android log EGL GLESv3)
        endif()
        target_link_libraries(Crafter_Magnum
                FREETYPE_CMAKE_LIB_FREETYPE
                MagnumExtras::Ui
                Magnum::Text
                Magnum::DebugTools
                Magnum::GL
                Magnum::Magnum
                Magnum::MeshTools
                Magnum::Primitives
                Magnum::SceneGraph
                Magnum::Shaders
                Magnum::TextureTools
                Magnum::Trade
                ${PLATFORM_LIBS}
        )
        set(CRAFTER_IMPORTED_MAGNUM 1)
    endif()
endmacro()

macro(import_project__Crafter_Core)
    if (NOT CRAFTER_IMPORTED_MAGNUM)
        import_project__Crafter_Magnum()
    endif()
    if (NOT CRAFTER_IMPORTED_CORE)
        set(CRAFTER_SRC ${Crafter_SDK_ROOT}/Crafter_Core/src)
        include_directories(${CRAFTER_SRC})
        add_subdirectory(${CRAFTER_SRC}/Crafter/WorldEngine/WINAPI_KERNEL ${CMAKE_CURRENT_BINARY_DIR}/WINAPI_KERNEL)
        add_library(Crafter_Core SHARED
                ${CRAFTER_SRC}/Crafter/Blueprint/Blueprint.cpp
                ${CRAFTER_SRC}/Crafter/Camera/Camera.cpp
                ${CRAFTER_SRC}/Crafter/CoordinateSystems/Translation.cpp
                ${CRAFTER_SRC}/Crafter/CoordinateSystems/Scale.cpp
                ${CRAFTER_SRC}/Crafter/CoordinateSystems/Rotation.cpp
                ${CRAFTER_SRC}/Crafter/CoordinateSystems/WorldSpace.cpp
                ${CRAFTER_SRC}/Crafter/CoordinateSystems/ViewSpace.cpp
                ${CRAFTER_SRC}/Crafter/CoordinateSystems/ClipSpace.cpp
                ${CRAFTER_SRC}/Crafter/Demo/Demo.cpp
                ${CRAFTER_SRC}/Crafter/Package/Package.cpp
                ${CRAFTER_SRC}/Crafter/WorldEngine/MeshGenerator.cpp
                ${CRAFTER_SRC}/Crafter/WorldEngine/WorldEngine.cpp
                ${CRAFTER_SRC}/Crafter/WorldEdit/WorldEdit.cpp
        )
        target_link_libraries(Crafter_Core
                Crafter_Magnum
                WINAPI::KERNEL
        )
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