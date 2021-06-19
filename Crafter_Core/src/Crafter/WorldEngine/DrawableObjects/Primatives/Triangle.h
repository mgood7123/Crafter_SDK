//
// Created by Matthew Good on 16/6/21.
//

#ifndef CRAFTER_DRAWABLE_OBJECTS_PRIMITIVES_TRIANGLE_H
#define CRAFTER_DRAWABLE_OBJECTS_PRIMITIVES_TRIANGLE_H

#include "../../DrawableObject.h"

namespace Crafter {
    namespace WorldEngine {
        namespace DrawableObjects {
            namespace Primitives {
                class Triangle : public DrawableObject {
                public:
                    DRAWABLE_OBJECT_CONSTRUCTOR_HPP(Triangle)

                    VertexWithColor data[3];

                    void init(
                            const Magnum::Vector3 &left,
                            const Magnum::Vector3 &right,
                            const Magnum::Vector3 &top,
                            const Magnum::Color3 color
                    ) {
                        data[0] = {left, color};
                        data[1] = {right, color};
                        data[2] = {top, color};
                        updateMesh();
                    }

                    void updateMesh() override {
                        Magnum::GL::Buffer buffer;
                        buffer.setData(data, Magnum::GL::BufferUsage::StaticDraw);
                        mesh.setCount(3).addVertexBuffer(
                                std::move(buffer), 0,
                                Magnum::Shaders::FlatGL3D::Position{},
                                Magnum::Shaders::FlatGL3D::Color3{}
                        );
                    }

                    void draw(const Matrix4 &transformationMatrix, Camera3D &camera) override {
                        shader
                                .setTransformationProjectionMatrix(
                                        camera.projectionMatrix()*transformationMatrix
                                ).draw(mesh);
                    }
                };
            }
        }
    }
}

#endif //CRAFTER_DRAWABLE_OBJECTS_PRIMITIVES_TRIANGLE_H
