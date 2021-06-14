//
// Created by Matthew Good on 10/6/21.
//

#include <Magnum/Shaders/PhongGL.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/Math/Color.h>
#include <Crafter/Camera/Camera.h>

#ifndef CRAFTER_CubeWithCamera_H
#define CRAFTER_CubeWithCamera_H

namespace Crafter {
    namespace Demo {
        namespace Packages {
            class CubeWithCamera : public Crafter::Package {
            public:
                CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_HPP(CubeWithCamera);

                void setup() override;

                void drawEvent() override;

                void viewportEvent(ViewportEvent &event) override;

                void mousePressEvent(MouseEvent &event) override;

                void mouseReleaseEvent(MouseEvent &event) override;

                void mouseMoveEvent(MouseMoveEvent &event) override;

                Camera camera;
                Magnum::GL::Mesh _mesh;
                Magnum::Shaders::PhongGL _shader;
                Magnum::Color3 _color;
            };
        }
    }
}
#endif //CRAFTER_CubeWithCamera_H
