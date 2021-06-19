//
// Created by Matthew Good on 16/6/21.
//

#ifndef CRAFTER_DRAWABLEOBJECT_H
#define CRAFTER_DRAWABLEOBJECT_H

#include <Magnum/GL/Mesh.h>
#include <Magnum/Math/Color.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Shaders/FlatGL.h>
#include <Magnum/Trade/MeshData.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/SceneGraph/Camera.h>
#include "WorldEngineBase.h"

namespace Crafter {
    namespace WorldEngine {
        typedef WorldEngineBase::Object3D Object3D;
        typedef WorldEngineBase::Scene3D Scene3D;
        typedef Magnum::Matrix4 Matrix4;
        typedef Magnum::SceneGraph::Camera3D Camera3D;
        typedef Magnum::SceneGraph::Drawable3D Drawable3D;
        typedef Magnum::SceneGraph::DrawableGroup3D DrawableGroup3D;

        using namespace Magnum::Math::Literals;

#define DRAWABLE_OBJECT_CONSTRUCTOR_HPP(name) name(Object3D* parent, DrawableGroup3D* group) : DrawableObject(parent, group) {};

        class DrawableObject : public Object3D, public Drawable3D {
        public:
            explicit DrawableObject(Object3D* parent, Magnum::SceneGraph::DrawableGroup3D* group) :
            Object3D{parent}, Magnum::SceneGraph::Drawable3D{*this, group}
            {}

        protected:

            struct VertexWithColor {
                Magnum::Vector3 position;
                Magnum::Color3 color;
            };

            Magnum::GL::Mesh mesh;
            Magnum::Shaders::FlatGL3D shader{Magnum::Shaders::FlatGL3D::Flag::VertexColor};

        public:

            virtual void updateMesh() {};

            virtual void draw(const Matrix4 &transformationMatrix, Camera3D &camera) override {};

            virtual void setColor(unsigned long long color) {
                setColor(Magnum::Math::Literals::operator ""_rgbf(color));
            }

            virtual void setColor(Magnum::Color3 color) {
                shader.setColor(color);
            }

//            // PROJECTION
//            // the order of matrix multiplication is reversed
//
//            Magnum::Matrix4
//            projection_Type_OBJECT_TRANSLATION_IS_RELATIVE_TO_CAMERA(
//                    const ClipSpace & clipSpace,
//                    const ViewSpace & viewSpace,
//                    const WorldSpace & worldSpace
//            ) {
//                return
//                        clipSpace.perspectiveProjection()
//                        * translationDistance(
//                                viewSpace.translation(),
//                                worldSpace.translation()
//                        )
//                        * viewSpace.rotation()
//                        * worldSpace.rotation();
//            }
//
//            static Magnum::Matrix4
//            projection_Type_OBJECT_ORBITS_CAMERA(
//                    const ClipSpace & clipSpace,
//                    const ViewSpace & viewSpace,
//                    const WorldSpace & worldSpace
//            ) {
//                using namespace Magnum;
//                return
//                        clipSpace.perspectiveProjection()
//                        * viewSpace.translation()
//                        * viewSpace.rotation()
//                        * worldSpace.translation()
//                        * worldSpace.rotation()
////                        * viewSpace.calculate_lookAt_matrix(viewSpace.translationVector3(), worldSpace.translationVector3(), {0,1,0})
////                        * viewSpace.rotation()
////                        * worldSpace.rotation()
//                        ;
//            }
//
//            static Magnum::Matrix4
//            projection_Type_OBJECT_TRANSLATION_IS_STATIC(
//                    const ClipSpace & clipSpace,
//                    const ViewSpace & viewSpace,
//                    const WorldSpace & worldSpace
//            ) {
//                return
//                        clipSpace.perspectiveProjection()
//                        * viewSpace.translation()
//                        * viewSpace.rotation()
//                        * worldSpace.translation()
//                        * worldSpace.rotation();
//            }
//
//            // END PROJECTION
        };
    }
}
#endif //CRAFTER_DRAWABLEOBJECT_H
