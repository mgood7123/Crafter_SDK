//
// Created by Matthew Good on 14/6/21.
//

#include <Magnum/GL/Renderer.h>
#include "DrawableObjects/Cube.h"
#include "DrawableObjects/GridWireframe.h"
#include "WorldEngine.h"

void Crafter::WorldEngine::WorldEngine::setup() {
    Magnum::GL::Renderer::enable(Magnum::GL::Renderer::Feature::DepthTest);
    Magnum::GL::Renderer::enable(Magnum::GL::Renderer::Feature::FaceCulling);
    Magnum::GL::Renderer::setClearColor(0x0_rgbaf);

    profiler.setup(
            DebugTools::FrameProfilerGL::Value::FrameTime|
            DebugTools::FrameProfilerGL::Value::GpuDuration|
            DebugTools::FrameProfilerGL::Value::CpuDuration,
            50
    );

    _freeformCamera = new FreeformCamera3D(_scene);
    _freeformCamera->move(-10.0f);

    /* TODO: Prepare your objects here and add them to the scene */
}

void Crafter::WorldEngine::WorldEngine::attachToCamera(Magnum::SceneGraph::Camera3D * camera) {
}

void Crafter::WorldEngine::WorldEngine::rotateRelative(Magnum::Vector2 relative) {
    // rotate camera up, down, left, right
    auto yaw = relative.x()*100;
    auto pitch = relative.y()*100;
    _freeformCamera->rotate(
            -yaw,
            pitch,
            0.002
    );
}

void Crafter::WorldEngine::WorldEngine::updateAspectRatio(const Magnum::Vector2i & viewport, float aspectRatio) {
    if (viewport.isZero()) {
        !Magnum::Error{} << "updateAspectRatio called with zero size viewport, skipping call";
        return;
    }
    _freeformCamera->camera()->setProjectionMatrix(Magnum::Matrix4::perspectiveProjection(Deg(35), aspectRatio, 0.01, 100));
    _freeformCamera->camera()->setViewport(viewport);
}

void Crafter::WorldEngine::WorldEngine::draw() {
    profiler.beginFrame();

    // these must be cleaned up at scope end
    DrawableObjects::Cube * cube = new DrawableObjects::Cube{&_scene, &_drawables};
    DrawableObjects::GridWireframe * grid = new DrawableObjects::GridWireframe{ &_scene, &_drawables };

    // init
    cube->init();
    cube->setColor(0xFF00FF);
    cube->rotateX(Deg(45));
    cube->rotateY(Deg(22.5));
    cube->translate({0,0,-20});

    grid->init(0x00ff00_rgbf);
    grid->translate({0,-1,0});

//    DrawableObjects::Triangle * s = new DrawableObjects::Triangle{&_scene, &_drawables};
//    s->init(Magnum::Math::Literals::operator""_rgbf(0xff0000));
//    s.addTranslationZ(-50);
//    s.addTranslationX(-2);
//    s.addRotationX(42.5);

    _freeformCamera->camera()->draw(_drawables);

    // clean up
    delete cube;
    delete grid;
    profiler.endFrame();
//    profiler.printStatistics(1);
}