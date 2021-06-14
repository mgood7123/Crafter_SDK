//
// Created by Matthew Good on 14/6/21.
//

#ifndef CRAFTER_CAMERA_H
#define CRAFTER_CAMERA_H

#include <Magnum/Magnum.h> // Magnum:: typedefs
#include <Magnum/Math/Matrix4.h> // Magnum::Matrix4

namespace Crafter {
    class Camera {
    private:
        Magnum::Matrix4 _modelView, _perspectiveProjection,
                _rotationX, _rotationY, _rotationZ,
                _translationX, _translationY, _translationZ;

        float r_x, r_y, r_z;
        float t_x, t_y, t_z;

        bool hasPerspectiveProjection = false;

        void setRotationX_(const float &x = 0.0f);

        void setRotationY_(const float &y = 0.0f);

        void setRotationZ_(const float &z = 0.0f);

        void setTranslationX_(const float &x = 0.0f);

        void setTranslationY_(const float &y = 0.0f);

        void setTranslationZ_(const float &z = 0.0f);

    public:

        const Magnum::Matrix4 &modelView() const;

        const Magnum::Matrix4 &perspectiveProjection() const;

        void setRotationX(const float &x = 0.0f);

        void addRotationX(const float &x = 0.0f);

        void subRotationX(const float &x = 0.0f);

        void mulRotationX(const float &x = 0.0f);

        void divRotationX(const float &x = 0.0f);

        Magnum::Matrix4 rotationX();

        void setRotationY(const float &y = 0.0f);

        void addRotationY(const float &y = 0.0f);

        void subRotationY(const float &y = 0.0f);

        void mulRotationY(const float &y = 0.0f);

        void divRotationY(const float &y = 0.0f);

        Magnum::Matrix4 rotationY();

        void setRotationZ(const float &z = 0.0f);

        void addRotationZ(const float &z = 0.0f);

        void subRotationZ(const float &z = 0.0f);

        void mulRotationZ(const float &z = 0.0f);

        void divRotationZ(const float &z = 0.0f);

        Magnum::Matrix4 rotationZ();

        void setRotation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f);

        void addRotation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f);

        void subRotation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f);

        void mulRotation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f);

        void divRotation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f);

        Magnum::Matrix4 rotation();

        void setTranslationX(const float &x = 0.0f);

        void addTranslationX(const float &x = 0.0f);

        void subTranslationX(const float &x = 0.0f);

        void mulTranslationX(const float &x = 0.0f);

        void divTranslationX(const float &x = 0.0f);

        Magnum::Matrix4 translationX();

        void setTranslationY(const float &y = 0.0f);

        void addTranslationY(const float &y = 0.0f);

        void subTranslationY(const float &y = 0.0f);

        void mulTranslationY(const float &y = 0.0f);

        void divTranslationY(const float &y = 0.0f);

        Magnum::Matrix4 translationY();

        void setTranslationZ(const float &z = 0.0f);

        void addTranslationZ(const float &z = 0.0f);

        void subTranslationZ(const float &z = 0.0f);

        void mulTranslationZ(const float &z = 0.0f);

        void divTranslationZ(const float &z = 0.0f);

        Magnum::Matrix4 translationZ();

        void setTranslation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f);

        void addTranslation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f);

        void subTranslation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f);

        void mulTranslation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f);

        void divTranslation(const float &x = 0.0f, const float &y = 0.0f, const float &z = 0.0f);

        Magnum::Matrix4 translation();

        void setPerspectiveProjection(const Magnum::Vector2 & size, const float near, const float far);

        void setPerspectiveProjection(Magnum::Rad fov, float aspectRatio, float near, float far);

        void setPerspectiveProjection(const Magnum::Vector2 & bottomLeft, const Magnum::Vector2 & topRight, float near, float far);

        void updateCamera();
    };
}


#endif //CRAFTER_CAMERA_H
