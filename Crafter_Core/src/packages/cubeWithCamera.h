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
    private:
        Matrix4 _modelView, _perspectiveProjection,
                _rotationX, _rotationY, _rotationZ,
                _translationX, _translationY, _translationZ;

        float r_x, r_y, r_z;
        float t_x, t_y, t_z;

        bool hasPerspectiveProjection = false;

    public:

        const Matrix4 &modelView() const {
            return _modelView;
        }

        const Matrix4 &perspectiveProjection() const {
            return _perspectiveProjection;
        }

        void setRotationX_(const float &x = 0.0f) {
            _rotationX = Matrix4::rotationX(Deg(x));
        }

        void setRotationY_(const float &y = 0.0f) {
            _rotationY = Matrix4::rotationY(Deg(y));
        }

        void setRotationZ_(const float &z = 0.0f) {
            _rotationZ = Matrix4::rotationZ(Deg(z));
        }

        void setRotationX(const float &x = 0.0f) {
            r_x = x;
            setRotationX_(r_x);
        }

        void addRotationX(const float &x = 0.0f) {
            r_x += x;
            setRotationX_(r_x);
        }

        void subRotationX(const float &x = 0.0f) {
            r_x -= x;
            setRotationX_(r_x);
        }

        void mulRotationX(const float &x = 0.0f) {
            r_x *= x;
            setRotationX_(r_x);
        }

        void divRotationX(const float &x = 0.0f) {
            r_x /= x;
            setRotationX_(r_x);
        }

        Matrix4 rotationX() {
            return _rotationX;
        }

        void setRotationY(const float &y = 0.0f) {
            r_y = y;
            setRotationY_(r_y);
        }

        void addRotationY(const float &y = 0.0f) {
            r_y += y;
            setRotationY_(r_y);
        }

        void subRotationY(const float &y = 0.0f) {
            r_y -= y;
            setRotationY_(r_y);
        }

        void mulRotationY(const float &y = 0.0f) {
            r_y *= y;
            setRotationY_(r_y);
        }

        void divRotationY(const float &y = 0.0f) {
            r_y /= y;
            setRotationY_(r_y);
        }

        Matrix4 rotationY() {
            return _rotationY;
        }

        void setRotationZ(const float &z = 0.0f) {
            r_z = z;
            setRotationZ_(r_z);
        }

        void addRotationZ(const float &z = 0.0f) {
            r_z += z;
            setRotationZ_(r_z);
        }

        void subRotationZ(const float &z = 0.0f) {
            r_z -= z;
            setRotationZ_(r_z);
        }

        void mulRotationZ(const float &z = 0.0f) {
            r_z *= z;
            setRotationZ_(r_z);
        }

        void divRotationZ(const float &z = 0.0f) {
            r_z /= z;
            setRotationZ_(r_z);
        }

        Matrix4 rotationZ() {
            return _rotationZ;
        }

        void setRotation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f) {
            setRotationX(x);
            setRotationY(y);
            setRotationZ(z);
        }

        void addRotation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f) {
            addRotationX(x);
            addRotationY(y);
            addRotationZ(z);
        }

        void subRotation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f) {
            subRotationX(x);
            subRotationY(y);
            subRotationZ(z);
        }

        void mulRotation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f) {
            mulRotationX(x);
            mulRotationY(y);
            mulRotationZ(z);
        }

        void divRotation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f) {
            divRotationX(x);
            divRotationY(y);
            divRotationZ(z);
        }

        Matrix4 rotation() {
            return rotationX() * rotationY() * rotationZ();
        }

        void setTranslationX_(const float &x = 0.0f) {
            _translationX = Matrix4::translation(Vector3::xAxis(x));
        }

        void setTranslationY_(const float &y = 0.0f) {
            _translationY = Matrix4::translation(Vector3::yAxis(y));
        }

        void setTranslationZ_(const float &z = 0.0f) {
            _translationZ = Matrix4::translation(Vector3::zAxis(z));
        }

        void setTranslationX(const float &x = 0.0f) {
            t_x = x;
            setTranslationX_(t_x);
        }

        void addTranslationX(const float &x = 0.0f) {
            t_x += x;
            setTranslationX_(t_x);
        }

        void subTranslationX(const float &x = 0.0f) {
            t_x -= x;
            setTranslationX_(t_x);
        }

        void mulTranslationX(const float &x = 0.0f) {
            t_x *= x;
            setTranslationX_(t_x);
        }

        void divTranslationX(const float &x = 0.0f) {
            t_x /= x;
            setTranslationX_(t_x);
        }

        Matrix4 translationX() {
            return _translationX;
        }

        void setTranslationY(const float &y = 0.0f) {
            t_y = y;
            setTranslationY_(t_y);
        }

        void addTranslationY(const float &y = 0.0f) {
            t_y += y;
            setTranslationY_(t_y);
        }

        void subTranslationY(const float &y = 0.0f) {
            t_y -= y;
            setTranslationY_(t_y);
        }

        void mulTranslationY(const float &y = 0.0f) {
            t_y *= y;
            setTranslationY_(t_y);
        }

        void divTranslationY(const float &y = 0.0f) {
            t_y /= y;
            setTranslationY_(t_y);
        }

        Matrix4 translationY() {
            return _translationY;
        }

        void setTranslationZ(const float &z = 0.0f) {
            t_z = z;
            setTranslationZ_(t_z);
        }

        void addTranslationZ(const float &z = 0.0f) {
            t_z += z;
            setTranslationZ_(t_z);
        }

        void subTranslationZ(const float &z = 0.0f) {
            t_z -= z;
            setTranslationZ_(t_z);
        }

        void mulTranslationZ(const float &z = 0.0f) {
            t_z *= z;
            setTranslationZ_(t_z);
        }

        void divTranslationZ(const float &z = 0.0f) {
            t_z /= z;
            setTranslationZ_(t_z);
        }

        Matrix4 translationZ() {
            return _translationZ;
        }

        void setTranslation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f) {
            setTranslationX(x);
            setTranslationY(y);
            setTranslationZ(z);
        }

        void addTranslation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f) {
            addTranslationX(x);
            addTranslationY(y);
            addTranslationZ(z);
        }

        void subTranslation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f) {
            subTranslationX(x);
            subTranslationY(y);
            subTranslationZ(z);
        }

        void mulTranslation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f) {
            mulTranslationX(x);
            mulTranslationY(y);
            mulTranslationZ(z);
        }

        void divTranslation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f) {
            divTranslationX(x);
            divTranslationY(y);
            divTranslationZ(z);
        }

        Matrix4 translation() {
            return translationX() * translationY() * translationZ();
        }

        void setPerspectiveProjection(const Vector2 & size, const float near, const float far) {
            _perspectiveProjection = Matrix4::perspectiveProjection(size, near, far);
            hasPerspectiveProjection = true;
        }

        void setPerspectiveProjection(Rad fov, float aspectRatio, float near, float far) {
            _perspectiveProjection = Matrix4::perspectiveProjection(fov, aspectRatio, near, far);
            hasPerspectiveProjection = true;
        }

        void setPerspectiveProjection(const Vector2 & bottomLeft, const Vector2 & topRight, float near, float far) {
            _perspectiveProjection = Matrix4::perspectiveProjection(bottomLeft, topRight, near, far);
            hasPerspectiveProjection = true;
        }

        void updateCamera() {
            _modelView = _perspectiveProjection * (_translationX * _translationY * _translationZ);
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
