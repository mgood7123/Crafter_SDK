//
// Created by Matthew Good on 19/6/21.
//

#ifndef CRAFTER_GRIDWIREFRAME_H
#define CRAFTER_GRIDWIREFRAME_H

#include "../DrawableObject.h"
#include <Magnum/Primitives/Grid.h>
#include <Magnum/Trade/MeshData3D.h>
#include <Magnum/MeshTools/Transform.h>

namespace Crafter {
    namespace WorldEngine {
        namespace DrawableObjects {
            class GridWireframe : public DrawableObject {
            public:
                DRAWABLE_OBJECT_CONSTRUCTOR_HPP(GridWireframe)

                void init(const Magnum::Color3 &color) {
                    Magnum::Trade::MeshData3D instMeshData = Magnum::Primitives::grid3DWireframe(
                            {50, 50});
                    Matrix4 scalingMatrix = Matrix4::scaling(Magnum::Vector3{50, 50, 0});
                    Magnum::MeshTools::transformPointsInPlace(scalingMatrix,
                                                              instMeshData.positions(0));

                    mesh = Magnum::MeshTools::compile(instMeshData);
                    shader = Magnum::Shaders::FlatGL3D{};
                    shader.setColor(color);
                    rotateX(Magnum::Deg(90));
                }

                void draw(const Matrix4 &transformationMatrix, Camera3D &camera) {
                    shader.setTransformationProjectionMatrix(
                            camera.projectionMatrix() * (transformationMatrix)
                        ).draw(mesh);
                };
            };
        }
    }
}


#endif //CRAFTER_GRIDWIREFRAME_H
