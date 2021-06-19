//
// Created by Matthew Good on 16/6/21.
//

#ifndef CRAFTER_DRAWABLE_OBJECTS_PRIMITIVES_LINE_H
#define CRAFTER_DRAWABLE_OBJECTS_PRIMITIVES_LINE_H

#include "../../DrawableObject.h"

namespace Crafter {
    namespace WorldEngine {
        namespace DrawableObjects {
            namespace Primitives {
                static constexpr struct VertexLine {
                    Magnum::Vector3 position;
                } VerticesLine[]{
                        {{-1.0f, -1.0f, 0.0f}},
                        {{1.0f,  -1.0f, 0.0f}}
                };
                static constexpr Magnum::Trade::MeshAttributeData AttributesLine[]{
                        Magnum::Trade::MeshAttributeData{Magnum::Trade::MeshAttribute::Position,
                                                         Magnum::Containers::stridedArrayView(
                                                                 VerticesLine,
                                                                 &VerticesLine[0].position,
                                                                 Magnum::Containers::arraySize(
                                                                         VerticesLine),
                                                                 sizeof(VertexLine))}
                };

                static Magnum::Trade::MeshData line() {
                    return Magnum::Trade::MeshData{Magnum::MeshPrimitive::Lines,
                                                   {}, VerticesLine,
                                                   Magnum::Trade::meshAttributeDataNonOwningArray(
                                                           AttributesLine)};
                }

                class Line : public DrawableObject {
                public:
                    DRAWABLE_OBJECT_CONSTRUCTOR_HPP(Line)
                    void init() {
                        mesh = Magnum::MeshTools::compile(line());
                        shader = std::move(Magnum::Shaders::FlatGL3D{});
                    }

                    void draw(const Matrix4 &transformationMatrix, Camera3D &camera) override {
                        shader.setTransformationProjectionMatrix(
                                        camera.projectionMatrix()*transformationMatrix)
                                .draw(mesh);
                    }
                };
            }
        }
    }
}


#endif //CRAFTER_DRAWABLE_OBJECTS_PRIMITIVES_LINE_H
