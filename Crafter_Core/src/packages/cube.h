//
// Created by Matthew Good on 10/6/21.
//

#include <Magnum/Shaders/PhongGL.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/Math/Color.h>

#ifndef CRAFTER_CUBE_H
#define CRAFTER_CUBE_H

namespace Crafter {
    namespace Packages {
        class Cube : public Crafter::Package {
        public:
            CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_HPP(Cube);

            void setup() override;

            void drawEvent() override;

            void viewportEvent(ViewportEvent &event) override;

            void mousePressEvent(MouseEvent &event) override;

            void mouseReleaseEvent(MouseEvent &event) override;

            void mouseMoveEvent(MouseMoveEvent &event) override;

            Magnum::GL::Mesh _mesh;
            Magnum::Shaders::PhongGL _shader;

            Magnum::Matrix4 _transformation, _projection;
            Magnum::Color3 _color;
        };
    }
}
#endif //CRAFTER_CUBE_H
