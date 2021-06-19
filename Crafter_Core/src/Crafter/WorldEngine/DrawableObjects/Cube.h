//
// Created by Matthew Good on 16/6/21.
//

#ifndef CRAFTER_DRAWABLE_OBJECTS_CUBE_H
#define CRAFTER_DRAWABLE_OBJECTS_CUBE_H

#include "../DrawableObject.h"

// TODO: figure out how to apply rotation to Normalized Device Coordinates
//18:34 AndroidDAW: hmmm i think i understand how a cube is drawn now https://arm-software.github.io/opengl-es-sdk-for-android/simple_cube.html#simpleCubeExampleCreatingCube
//18:36 AndroidDAW: the Z index is the vertex depth, how far away it is, when drawing a 2d the Z is normally zero, but when 3d, the vector will be drawn from one point to another point, with respect for Z
//18:37 AndroidDAW: eg if a point from -1, -1, -1 to -1, -1, 1, then a point is drawn from X -1 to X -1, from Y -1 to Y -1, from Z -1 to Z 1, essentially drawing it at a 90 degree angle
//18:39 AndroidDAW: as if it is being drawn from X -1 to X 1, from Y -1 to Y -1, from Z 0 to Z 0. and then rotated by 90 degrees via the model matrix's rotation

namespace Crafter {
    namespace WorldEngine {
        namespace DrawableObjects {
            /* not 8-bit because GPUs (and Vulkan) don't like it nowadays */
            constexpr Magnum::UnsignedShort IndicesSolid[]{
                    0, 1, 2, 0, 2, 3, /* +Z */
                    4, 5, 6, 4, 6, 7, /* +X */
                    8, 9, 10, 8, 10, 11, /* +Y */
                    12, 13, 14, 12, 14, 15, /* -Z */
                    16, 17, 18, 16, 18, 19, /* -Y */
                    20, 21, 22, 20, 22, 23  /* -X */
            };
            constexpr struct VertexSolid {
                Magnum::Vector3 position;
                Magnum::Vector3 normal;
            } VerticesSolid[]{
                    {{-1.0f, -1.0f, 1.0f},  {0.0f,  0.0f,  1.0f}},
                    {{1.0f,  -1.0f, 1.0f},  {0.0f,  0.0f,  1.0f}},
                    {{1.0f,  1.0f,  1.0f},  {0.0f,  0.0f,  1.0f}}, /* +Z */
                    {{-1.0f, 1.0f,  1.0f},  {0.0f,  0.0f,  1.0f}},

                    {{1.0f,  -1.0f, 1.0f},  {1.0f,  0.0f,  0.0f}},
                    {{1.0f,  -1.0f, -1.0f}, {1.0f,  0.0f,  0.0f}},
                    {{1.0f,  1.0f,  -1.0f}, {1.0f,  0.0f,  0.0f}}, /* +X */
                    {{1.0f,  1.0f,  1.0f},  {1.0f,  0.0f,  0.0f}},

                    {{-1.0f, 1.0f,  1.0f},  {0.0f,  1.0f,  0.0f}},
                    {{1.0f,  1.0f,  1.0f},  {0.0f,  1.0f,  0.0f}},
                    {{1.0f,  1.0f,  -1.0f}, {0.0f,  1.0f,  0.0f}}, /* +Y */
                    {{-1.0f, 1.0f,  -1.0f}, {0.0f,  1.0f,  0.0f}},

                    {{1.0f,  -1.0f, -1.0f}, {0.0f,  0.0f,  -1.0f}},
                    {{-1.0f, -1.0f, -1.0f}, {0.0f,  0.0f,  -1.0f}},
                    {{-1.0f, 1.0f,  -1.0f}, {0.0f,  0.0f,  -1.0f}}, /* -Z */
                    {{1.0f,  1.0f,  -1.0f}, {0.0f,  0.0f,  -1.0f}},

                    {{-1.0f, -1.0f, -1.0f}, {0.0f,  -1.0f, 0.0f}},
                    {{1.0f,  -1.0f, -1.0f}, {0.0f,  -1.0f, 0.0f}},
                    {{1.0f,  -1.0f, 1.0f},  {0.0f,  -1.0f, 0.0f}}, /* -Y */
                    {{-1.0f, -1.0f, 1.0f},  {0.0f,  -1.0f, 0.0f}},

                    {{-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f,  0.0f}},
                    {{-1.0f, -1.0f, 1.0f},  {-1.0f, 0.0f,  0.0f}},
                    {{-1.0f, 1.0f,  1.0f},  {-1.0f, 0.0f,  0.0f}}, /* -X */
                    {{-1.0f, 1.0f,  -1.0f}, {-1.0f, 0.0f,  0.0f}}
            };
            constexpr Magnum::Trade::MeshAttributeData AttributesSolid[]{
                    Magnum::Trade::MeshAttributeData{Magnum::Trade::MeshAttribute::Position,
                                                     Magnum::Containers::stridedArrayView(
                                                             VerticesSolid,
                                                             &VerticesSolid[0].position,
                                                             Magnum::Containers::arraySize(
                                                                     VerticesSolid),
                                                             sizeof(VertexSolid))},
                    Magnum::Trade::MeshAttributeData{Magnum::Trade::MeshAttribute::Normal,
                                                     Magnum::Containers::stridedArrayView(
                                                             VerticesSolid,
                                                             &VerticesSolid[0].normal,
                                                             Magnum::Containers::arraySize(
                                                                     VerticesSolid),
                                                             sizeof(VertexSolid))}
            };

            static Magnum::Trade::MeshData cubeSolid() {
                return Magnum::Trade::MeshData{Magnum::MeshPrimitive::Triangles,
                                               {}, IndicesSolid,
                                               Magnum::Trade::MeshIndexData{IndicesSolid},
                                               {}, VerticesSolid,
                                               Magnum::Trade::meshAttributeDataNonOwningArray(
                                                       AttributesSolid)};
            }

            class Cube : public DrawableObject {
            public:
                DRAWABLE_OBJECT_CONSTRUCTOR_HPP(Cube)
                void init() {
                    mesh = Magnum::MeshTools::compile(cubeSolid());
                    shader = std::move(Magnum::Shaders::FlatGL3D{});
                }

                void draw(const Matrix4 &transformationMatrix, Camera3D &camera) override {
                    shader.setTransformationProjectionMatrix(camera.projectionMatrix()*transformationMatrix)
                            .draw(mesh);
                }
            };
        }
    }
}


#endif //CRAFTER_DRAWABLE_OBJECTS_CUBE_H
