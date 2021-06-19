//
// Created by Matthew Good on 16/6/21.
//

#ifndef CRAFTER_DRAWABLE_OBJECTS_PRIMITIVES_PLANEWIREFRAME_H
#define CRAFTER_DRAWABLE_OBJECTS_PRIMITIVES_PLANEWIREFRAME_H

#include "../../DrawableObject.h"

namespace Crafter {
    namespace WorldEngine {
        namespace DrawableObjects {
            namespace Primitives {
                static constexpr struct VertexWireframe {
                    Magnum::Vector3 position;
                } VerticesWireframe[]{
                        {{-1.0f, -1.0f, 0.0f}},
                        {{ 1.0f, -1.0f, 0.0f}},
                        {{ 1.0f, -1.0f, 0.0f}},
                        {{ 1.0f,  1.0f, 0.0f}},
                        {{ 1.0f,  1.0f, 0.0f}},
                        {{-1.0f,  1.0f, 0.0f}},
                        {{-1.0f,  1.0f, 0.0f}},
                        {{-1.0f, -1.0f, 0.0f}}
                };

                static constexpr Magnum::Trade::MeshAttributeData AttributesWireframe[]{
                        Magnum::Trade::MeshAttributeData{Magnum::Trade::MeshAttribute::Position,
                                                         Magnum::Containers::stridedArrayView(VerticesWireframe, &VerticesWireframe[0].position,
                                                                                              Magnum::Containers::arraySize(VerticesWireframe), sizeof(VertexWireframe))}
                };
                class PlaneWireframe: public Crafter::WorldEngine::DrawableObject {

                    Magnum::Trade::MeshData planeWireframe() {
                        return Magnum::Trade::MeshData{Magnum::MeshPrimitive::Lines,
                                                       {}, VerticesWireframe,
                                                       Magnum::Trade::meshAttributeDataNonOwningArray(AttributesWireframe)};
                    }
                public:

                    DRAWABLE_OBJECT_CONSTRUCTOR_HPP(PlaneWireframe)
                    void init() {
                        mesh = Magnum::MeshTools::compile(planeWireframe());
                        shader = std::move(Magnum::Shaders::FlatGL3D{});
                        setColor(0xA1A1A1);
                    }

                    void draw(const Matrix4 &transformationMatrix, Camera3D &camera) override {
                        addTranslationZ(-5);
                        addTranslationY(-1);
                        addRotationX(-90);
                        shader.setTransformationProjectionMatrix(camera.projectionMatrix()*transformationMatrix)
                                .draw(mesh);
                        setTranslationX(-2);
                        shader.setTransformationProjectionMatrix(camera.projectionMatrix()*transformationMatrix)
                                .draw(mesh);
                        addTranslationZ(-2);
                        shader.setTransformationProjectionMatrix(camera.projectionMatrix()*transformationMatrix)
                                .draw(mesh);
                        setTranslationX(0);
                        shader.setTransformationProjectionMatrix(camera.projectionMatrix()*transformationMatrix)
                                .draw(mesh);
                    }
                };
            }
        }
    }
}

#endif //CRAFTER_DRAWABLE_OBJECTS_PRIMITIVES_PLANEWIREFRAME_H
