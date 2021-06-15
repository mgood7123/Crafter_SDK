//
// Created by Matthew Good on 15/6/21.
//

#ifndef CRAFTER_ROTATION_H
#define CRAFTER_ROTATION_H

#include <Magnum/Magnum.h> // Magnum:: typedefs
#include <Magnum/Math/Matrix4.h> // Magnum::Matrix4

namespace Crafter {
    class Rotation {
    protected:
        Magnum::Matrix4 _rotationX, _rotationY, _rotationZ;

        void setRotationX_(const float &x);

        void setRotationY_(const float &y);

        void setRotationZ_(const float &z);

        float r_x = 0;
        float r_y = 0;
        float r_z = 0;
    public:

        virtual void setRotationX(const float &degrees);

        virtual void addRotationX(const float &degrees);

        virtual void subRotationX(const float &degrees);

        virtual void mulRotationX(const float &degrees);

        virtual void divRotationX(const float &degrees);

        virtual Magnum::Matrix4 rotationX();

        virtual void setRotationY(const float &degrees);

        virtual void addRotationY(const float &degrees);

        virtual void subRotationY(const float &degrees);

        virtual void mulRotationY(const float &degrees);

        virtual void divRotationY(const float &degrees);

        virtual Magnum::Matrix4 rotationY();

        virtual void setRotationZ(const float &degrees);

        virtual void addRotationZ(const float &degrees);

        virtual void subRotationZ(const float &degrees);

        virtual void mulRotationZ(const float &degrees);

        virtual void divRotationZ(const float &degrees);

        virtual Magnum::Matrix4 rotationZ();

        virtual void setRotation(const float &x, const float &y, const float &z);

        virtual void addRotation(const float &x, const float &y, const float &z);

        virtual void subRotation(const float &x, const float &y, const float &z);

        virtual void mulRotation(const float &x, const float &y, const float &z);

        virtual void divRotation(const float &x, const float &y, const float &z);

        virtual Magnum::Matrix4 rotation();
    };
}

#endif //CRAFTER_ROTATION_H
