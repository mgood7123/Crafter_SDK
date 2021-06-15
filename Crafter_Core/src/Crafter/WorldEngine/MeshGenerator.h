//
// Created by Matthew Good on 14/6/21.
//

#ifndef CRAFTER_MESHGENERATOR_H
#define CRAFTER_MESHGENERATOR_H

#include <Magnum/Magnum.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Math/Vector2.h>
#include <Magnum/Math/Vector3.h>

namespace Crafter {
    namespace WorldEngine {
        class MeshGenerator {
            struct VertexWireframe2D {
                Magnum::Vector2 position;
            };

            struct Vertex2D {
                Magnum::Vector2 position;
                Magnum::Vector2 textureCoordinates;
            };

            struct VertexWireframe3D {
                Magnum::Vector3 position;
            };

            struct Vertex3D {
                Magnum::Vector3 position;
                Magnum::Vector3 textureCoordinates;
            };

        public:
            static Magnum::GL::Mesh
            triangleWireframe2D(const Magnum::Vector2 &left, const Magnum::Vector2 &right,
                                         const Magnum::Vector2 &top);
            static Magnum::GL::Mesh
            triangle2D(const Magnum::Vector2 &left, const Magnum::Vector2 &right,
                                    const Magnum::Vector2 &top);

            static Magnum::GL::Mesh
            planeWireframe2D(const Magnum::Vector2 &topLeft, const Magnum::Vector2 &topRight,
                             const Magnum::Vector2 &bottomRight, const Magnum::Vector2 &bottomLeft);

            static Magnum::GL::Mesh
            plane2D(const Magnum::Vector2 &topLeft, const Magnum::Vector2 &topRight,
                    const Magnum::Vector2 &bottomRight, const Magnum::Vector2 &bottomLeft);

            static Magnum::GL::Mesh triangle3D();
        };
    }
}

#endif //CRAFTER_MESHGENERATOR_H
