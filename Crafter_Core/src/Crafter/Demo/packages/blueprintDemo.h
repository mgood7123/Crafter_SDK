//
// Created by Matthew Good on 10/6/21.
//

#include <Magnum/Shaders/PhongGL.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/Math/Color.h>
#include <Crafter/Camera/Camera.h>
#include <Crafter/Blueprint/Blueprint.h>

#ifndef CRAFTER_Blueprint_H
#define CRAFTER_Blueprint_H

namespace Crafter {
    namespace Demo {
        namespace Packages {
            class BlueprintDemo : public Crafter::Package {
            public:
                CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_HPP(BlueprintDemo);

                void setup() override;

                void drawEvent() override;

                void viewportEvent(ViewportEvent &event) override;

                void mousePressEvent(MouseEvent &event) override;

                void mouseReleaseEvent(MouseEvent &event) override;

                void mouseMoveEvent(MouseMoveEvent &event) override;

                Blueprint blueprint;
                Camera camera;
            };
        }
    }
}
#endif //CRAFTER_Blueprint_H
