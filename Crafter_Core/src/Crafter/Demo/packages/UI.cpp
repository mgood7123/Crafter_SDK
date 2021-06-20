//
// Created by Matthew Good on 10/6/21.
//

#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/Ui/Plane.h>
#include <Magnum/Ui/Anchor.h>
#include <Magnum/Ui/Button.h>

CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_CPP(Crafter::Demo::Packages::UI, UI)

void Crafter::Demo::Packages::UI::setup() {
    ui.relayout(
            Math::clamp(
                    {640.0f, 360.0f},
                    {1920.0f, 1080.0f},
                    Vector2{windowSize()}/dpiScaling()
            ),
            windowSize(),
            framebufferSize()
   );
}

namespace {
    using namespace Magnum;

    struct BaseUiPlane : Ui::Plane {
        explicit BaseUiPlane(Ui::UserInterface &ui) :
                Ui::Plane{ui, Ui::Snap::Top | Ui::Snap::Bottom | Ui::Snap::Left | Ui::Snap::Right,
                          0, 50, 640},
                buttonDefault{*this, {Ui::Snap::Top|Ui::Snap::Left, Range2D::fromSize(Vector2::yAxis(-36.0f),
                                                                                      {100, 100})},
                              "Default", Ui::Style::Default}
        {}
        Ui::Button buttonDefault;
    };
}

void Crafter::Demo::Packages::UI::drawEvent() {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);
    BaseUiPlane baseUiPlane(ui);
    ui.draw();
    swapBuffers();
}
