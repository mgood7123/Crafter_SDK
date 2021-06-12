//
// Created by Matthew Good on 10/6/21.
//

#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Buffer.h>

CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_CPP(Crafter::Packages::Polygon, Polygon)

void Crafter::Packages::Polygon::setup() {
    blueprint.setPolygonResolution(8);
}

void Crafter::Packages::Polygon::drawEvent() {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);
    blueprint.draw();
    swapBuffers();
}
