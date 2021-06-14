//
// Created by Matthew Good on 10/6/21.
//

#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Buffer.h>

CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_CPP(Crafter::Demo::Packages::Polygon, Polygon)

void Crafter::Demo::Packages::Polygon::setup() {
    blueprint.setPolygonResolution(8);
}

void Crafter::Demo::Packages::Polygon::drawEvent() {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);
    blueprint.draw();
    swapBuffers();
}
