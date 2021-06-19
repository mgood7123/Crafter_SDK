//
// Created by Matthew Good on 10/6/21.
//

#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/Trade/MeshData.h>

CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_CPP(Crafter::Demo::Packages::BlueprintDemo, BlueprintDemo)

void Crafter::Demo::Packages::BlueprintDemo::setup() {
    blueprint.setup();
//    blueprint.attachToCamera(camera);
    blueprint.updateAspectRatio(windowSize(), Vector2{windowSize()}.aspectRatio());
}

void Crafter::Demo::Packages::BlueprintDemo::drawEvent() {
    GL::defaultFramebuffer.clear(
            GL::FramebufferClear::Color|GL::FramebufferClear::Depth);

    blueprint.draw();

    swapBuffers();
    redraw();
}

void Crafter::Demo::Packages::BlueprintDemo::viewportEvent(ViewportEvent &event) {
    GL::defaultFramebuffer.setViewport({{}, event.framebufferSize()});

    auto size = GL::defaultFramebuffer.viewport().size();

    blueprint.updateAspectRatio(size, Vector2{size}.aspectRatio());
}

void Crafter::Demo::Packages::BlueprintDemo::mousePressEvent(MouseEvent& event) {
    if(event.button() != MouseEvent::Button::Left) return;
    event.setAccepted();
}

void Crafter::Demo::Packages::BlueprintDemo::mouseReleaseEvent(MouseEvent& event) {
    event.setAccepted();
    redraw();
}

void Crafter::Demo::Packages::BlueprintDemo::mouseMoveEvent(MouseMoveEvent& event) {
    if(!(event.buttons() & MouseMoveEvent::Button::Left)) return;

    Vector2 delta = 3.0f*Vector2{event.relativePosition()}/Vector2{windowSize()};

    blueprint.rotateRelative(delta);

    event.setAccepted();
    redraw();
}
