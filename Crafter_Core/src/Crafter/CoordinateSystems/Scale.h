//
// Created by Matthew Good on 15/6/21.
//

#ifndef CRAFTER_SCALE_H
#define CRAFTER_SCALE_H

#include <Magnum/Magnum.h> // Magnum:: typedefs
#include <Magnum/Math/Matrix4.h> // Magnum::Matrix4
#include <stack>

namespace Crafter {
    class Scale {
    protected:
        std::stack<std::pair<float, Magnum::Matrix4>>
        _scale_stackX, _scale_stackY, _scale_stackZ;
        Magnum::Matrix4 _scaleX, _scaleY, _scaleZ;

        void setScaleX_(const float &x);

        void setScaleY_(const float &y);

        void setScaleZ_(const float &z);


    public:

        // not to be edited directly
        float s_x = 0;
        // not to be edited directly
        float s_y = 0;
        // not to be edited directly
        float s_z = 0;

        virtual void saveScaleX();
        virtual void saveScaleY();
        virtual void saveScaleZ();
        virtual void saveScale();

        virtual void restoreScaleX();
        virtual void restoreScaleY();
        virtual void restoreScaleZ();
        virtual void restoreScale();

        virtual Magnum::Vector3 scaleVector3() const;

        virtual void setScaleX(const float &x);

        virtual void addScaleX(const float &x);

        virtual void subScaleX(const float &x);

        virtual void mulScaleX(const float &x);

        virtual void divScaleX(const float &x);

        virtual Magnum::Matrix4 scaleX() const;

        virtual void setScaleY(const float &y);

        virtual void addScaleY(const float &y);

        virtual void subScaleY(const float &y);

        virtual void mulScaleY(const float &y);

        virtual void divScaleY(const float &y);

        virtual Magnum::Matrix4 scaleY() const;

        virtual void setScaleZ(const float &z);

        virtual void addScaleZ(const float &z);

        virtual void subScaleZ(const float &z);

        virtual void mulScaleZ(const float &z);

        virtual void divScaleZ(const float &z);

        virtual Magnum::Matrix4 scaleZ() const;

        virtual void setScale(const float &x, const float &y, const float &z);

        virtual void addScale(const float &x, const float &y, const float &z);

        virtual void subScale(const float &x, const float &y, const float &z);

        virtual void mulScale(const float &x, const float &y, const float &z);

        virtual void divScale(const float &x, const float &y, const float &z);

        virtual Magnum::Matrix4 scale() const;
    };
}

#endif //CRAFTER_SCALE_H
