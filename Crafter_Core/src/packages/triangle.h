//
// Created by Matthew Good on 10/6/21.
//

#ifndef CRAFTER_TRIANGLE_H
#define CRAFTER_TRIANGLE_H
#include <Magnum/GL/Mesh.h>
#include <Magnum/Shaders/VertexColor.h>

namespace Crafter {
    namespace Packages {
        class Triangle : public Crafter::Package {
            Magnum::GL::Mesh _mesh;
            Magnum::Shaders::VertexColorGL2D _shader;
        public:
            CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_HPP(Triangle);

            void setup() override;

            void drawEvent() override;
        };
    }
}
#endif //CRAFTER_TRIANGLE_H
