//
// Created by Matthew Good on 14/6/21.
//

#ifndef CRAFTER_WORLDENGINE_H
#define CRAFTER_WORLDENGINE_H

#include <Crafter/Camera/Camera.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Shaders/FlatGL.h>
#include <Magnum/Math/Color.h>
#include "MeshGenerator.h"

namespace Crafter {
    namespace WorldEngine {
        class WorldEngine {
            Magnum::GL::Mesh _mesh;
            Magnum::Shaders::FlatGL3D _shader{Magnum::Shaders::FlatGL3D::Flag::VertexColor};
            Magnum::Color3 _color;
            Crafter::Camera *camera = nullptr;

        public:
            void setup();

            void attachToCamera(Crafter::Camera &camera);

            void updateAspectRatio(float aspectRatio);

            void rotateRelative(Magnum::Vector2 relative);

            void draw();
        };
    }
}

#endif //CRAFTER_WORLDENGINE_H
