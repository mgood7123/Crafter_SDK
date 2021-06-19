//
// Created by Matthew Good on 15/6/21.
//

#ifndef CRAFTER_TRANSLATION_H
#define CRAFTER_TRANSLATION_H

#include <Magnum/Magnum.h> // Magnum:: typedefs
#include <Magnum/Math/Matrix4.h> // Magnum::Matrix4
#include <stack>

namespace Crafter {
    class Translation {
    protected:
        std::stack<std::pair<float, Magnum::Matrix4>>
        _translation_stackX, _translation_stackY, _translation_stackZ;
        Magnum::Matrix4 _translationX, _translationY, _translationZ;

        void setTranslationX_(const float &x);

        void setTranslationY_(const float &y);

        void setTranslationZ_(const float &z);


    public:

        // not to be edited directly
        float t_x = 0;
        // not to be edited directly
        float t_y = 0;
        // not to be edited directly
        float t_z = 0;

        virtual void saveTranslationX();
        virtual void saveTranslationY();
        virtual void saveTranslationZ();
        virtual void saveTranslation();

        virtual void restoreTranslationX();
        virtual void restoreTranslationY();
        virtual void restoreTranslationZ();
        virtual void restoreTranslation();

        virtual Magnum::Vector3 translationVector3() const;

        virtual void setTranslationX(const float &x);

        virtual void addTranslationX(const float &x);

        virtual void subTranslationX(const float &x);

        virtual void mulTranslationX(const float &x);

        virtual void divTranslationX(const float &x);

        virtual Magnum::Matrix4 translationX() const;

        virtual void setTranslationY(const float &y);

        virtual void addTranslationY(const float &y);

        virtual void subTranslationY(const float &y);

        virtual void mulTranslationY(const float &y);

        virtual void divTranslationY(const float &y);

        virtual Magnum::Matrix4 translationY() const;

        virtual void setTranslationZ(const float &z);

        virtual void addTranslationZ(const float &z);

        virtual void subTranslationZ(const float &z);

        virtual void mulTranslationZ(const float &z);

        virtual void divTranslationZ(const float &z);

        virtual Magnum::Matrix4 translationZ() const;

        virtual void setTranslation(const float &x, const float &y, const float &z);

        virtual void addTranslation(const float &x, const float &y, const float &z);

        virtual void subTranslation(const float &x, const float &y, const float &z);

        virtual void mulTranslation(const float &x, const float &y, const float &z);

        virtual void divTranslation(const float &x, const float &y, const float &z);

        virtual Magnum::Matrix4 translation() const;

        static Magnum::Matrix4 translationDistance(const Magnum::Matrix4 & A, const Magnum::Matrix4 & B);
    };
}

#endif //CRAFTER_TRANSLATION_H
