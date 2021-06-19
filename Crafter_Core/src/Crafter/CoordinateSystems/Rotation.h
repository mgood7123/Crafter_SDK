//
// Created by Matthew Good on 15/6/21.
//

#ifndef CRAFTER_ROTATION_H
#define CRAFTER_ROTATION_H

#include <Magnum/Magnum.h> // Magnum:: typedefs
#include <Magnum/Math/Matrix4.h> // Magnum::Matrix4
#include <stack>

namespace Crafter {
    class Rotation {
    protected:
        std::stack<std::pair<float, Magnum::Matrix4>>
        _rotation_stackX, _rotation_stackY, _rotation_stackZ;
        Magnum::Matrix4 _rotationX, _rotationY, _rotationZ;

        void setRotationX_(const float &x);

        void setRotationY_(const float &y);

        void setRotationZ_(const float &z);

    public:
        // not to be edited directly
        float r_x = 0;
        // not to be edited directly
        float r_y = 0;
        // not to be edited directly
        float r_z = 0;

        virtual void saveRotationX();
        virtual void saveRotationY();
        virtual void saveRotationZ();
        virtual void saveRotation();

        virtual void restoreRotationX();
        virtual void restoreRotationY();
        virtual void restoreRotationZ();
        virtual void restoreRotation();

        virtual Magnum::Vector3 rotationVector3() const;

        virtual void setRotationX(const float &degrees);

        virtual void addRotationX(const float &degrees);

        virtual void subRotationX(const float &degrees);

        virtual void mulRotationX(const float &degrees);

        virtual void divRotationX(const float &degrees);

        virtual Magnum::Matrix4 rotationX() const;

        virtual void setRotationY(const float &degrees);

        virtual void addRotationY(const float &degrees);

        virtual void subRotationY(const float &degrees);

        virtual void mulRotationY(const float &degrees);

        virtual void divRotationY(const float &degrees);

        virtual Magnum::Matrix4 rotationY() const;

        virtual void setRotationZ(const float &degrees);

        virtual void addRotationZ(const float &degrees);

        virtual void subRotationZ(const float &degrees);

        virtual void mulRotationZ(const float &degrees);

        virtual void divRotationZ(const float &degrees);

        virtual Magnum::Matrix4 rotationZ() const;

        virtual void setRotation(const float &x, const float &y, const float &z);

        virtual void addRotation(const float &x, const float &y, const float &z);

        virtual void subRotation(const float &x, const float &y, const float &z);

        virtual void mulRotation(const float &x, const float &y, const float &z);

        virtual void divRotation(const float &x, const float &y, const float &z);

        virtual Magnum::Matrix4 rotation() const;
    };
}

#endif //CRAFTER_ROTATION_H
