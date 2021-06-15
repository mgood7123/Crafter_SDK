//
// Created by Matthew Good on 15/6/21.
//

#ifndef CRAFTER_TRANSLATION_H
#define CRAFTER_TRANSLATION_H

#include <Magnum/Magnum.h> // Magnum:: typedefs
#include <Magnum/Math/Matrix4.h> // Magnum::Matrix4

namespace Crafter {
    class Translation {
    protected:
        Magnum::Matrix4 _translationX, _translationY, _translationZ;

        void setTranslationX_(const float &x);

        void setTranslationY_(const float &y);

        void setTranslationZ_(const float &z);

        float t_x = 0;
        float t_y = 0;
        float t_z = 0;

    public:

        virtual void setTranslationX(const float &x);

        virtual void addTranslationX(const float &x);

        virtual void subTranslationX(const float &x);

        virtual void mulTranslationX(const float &x);

        virtual void divTranslationX(const float &x);

        virtual Magnum::Matrix4 translationX();

        virtual void setTranslationY(const float &y);

        virtual void addTranslationY(const float &y);

        virtual void subTranslationY(const float &y);

        virtual void mulTranslationY(const float &y);

        virtual void divTranslationY(const float &y);

        virtual Magnum::Matrix4 translationY();

        virtual void setTranslationZ(const float &z);

        virtual void addTranslationZ(const float &z);

        virtual void subTranslationZ(const float &z);

        virtual void mulTranslationZ(const float &z);

        virtual void divTranslationZ(const float &z);

        virtual Magnum::Matrix4 translationZ();

        virtual void setTranslation(const float &x, const float &y, const float &z);

        virtual void addTranslation(const float &x, const float &y, const float &z);

        virtual void subTranslation(const float &x, const float &y, const float &z);

        virtual void mulTranslation(const float &x, const float &y, const float &z);

        virtual void divTranslation(const float &x, const float &y, const float &z);

        virtual Magnum::Matrix4 translation();

        static Magnum::Matrix4 translationDistance(const Magnum::Matrix4 & A, const Magnum::Matrix4 & B);
    };
}

#endif //CRAFTER_TRANSLATION_H
