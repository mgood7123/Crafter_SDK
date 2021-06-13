//
// Created by Matthew Good on 10/6/21.
//

#include <Magnum/Shaders/PhongGL.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/Math/Color.h>

#ifndef CRAFTER_CubeWithCamera_H
#define CRAFTER_CubeWithCamera_H

namespace Magnum {
    class Camera {
    public:
        Matrix4 _transformation, _projection,
                _perspectiveProjection,
                _rotationX, _rotationY, _rotationZ,
                _translation,
                _translationX, _translationY, _translationZ;

        void setRotationX(float x) {
            _rotationX = Matrix4::rotationX(Deg(x));
        }

        void setRotationX(const Deg & x) {
            _rotationX = Matrix4::rotationX(x);
        }

        void setRotationY(float y) {
            _rotationY = Matrix4::rotationY(Deg(y));
        }

        void setRotationY(const Deg & y) {
            _rotationY = Matrix4::rotationY(y);
        }

        void setRotationZ(float z) {
            _rotationZ = Matrix4::rotationZ(Deg(z));
        }

        void setRotationZ(const Deg & z) {
            _rotationZ = Matrix4::rotationZ(z);
        }

        void updateTransformation() {
            _transformation = _rotationX * _rotationY * _rotationZ;
        }

        void setTranslationX(float x) {
            _translationX = Matrix4::translation(Vector3::xAxis(x));
        }

        void setTranslationY(float y) {
            _translationY = Matrix4::translation(Vector3::yAxis(y));
        }

        void setTranslationZ(float z) {
            _translationZ = Matrix4::translation(Vector3::zAxis(z));
        }

        void updateTranslation() {
            _translation = _translationX * _translationY * _translationZ;
        }

        void setPerspectiveProjection(const Vector2 & size, const float near, const float far) {
            _perspectiveProjection = Matrix4::perspectiveProjection(size, near, far);
        }

        void setPerspectiveProjection(Rad fov, float aspectRatio, float near, float far) {
            _perspectiveProjection = Matrix4::perspectiveProjection(fov, aspectRatio, near, far);
        }

        void setPerspectiveProjection(const Vector2 & bottomLeft, const Vector2 & topRight, float near, float far) {
            _perspectiveProjection = Matrix4::perspectiveProjection(bottomLeft, topRight, near, far);
        }

        void combinePerspectiveProjectionWithTranslation() {
            _projection = _perspectiveProjection * _translation;
        }

        void combineProjectionWithTranslationY() {
            _projection = _projection * _translationY;
        }
    };
}

namespace Crafter {
    namespace Packages {
        class CubeWithCamera : public Crafter::Package {
        public:
            CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_HPP(CubeWithCamera);

            void setup() override;

            void drawEvent() override;

            void viewportEvent(ViewportEvent &event) override;

            void mousePressEvent(MouseEvent &event) override;

            void mouseReleaseEvent(MouseEvent &event) override;

            void mouseMoveEvent(MouseMoveEvent &event) override;

            Magnum::Camera camera;
            Magnum::GL::Mesh _mesh;
            Magnum::Shaders::PhongGL _shader;
            Magnum::Color3 _color;
        };
    }
}
#endif //CRAFTER_CubeWithCamera_H
