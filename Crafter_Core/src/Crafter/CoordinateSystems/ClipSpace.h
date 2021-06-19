//
// Created by Matthew Good on 17/6/21.
//

#ifndef CRAFTER_CLIPSPACE_H
#define CRAFTER_CLIPSPACE_H

#include <Magnum/Magnum.h> // Magnum:: typedefs
#include <Magnum/Math/Matrix4.h> // Magnum::Matrix4

namespace Crafter {
    class ClipSpace {
    protected:

        bool hasPerspectiveProjection = false;

        Magnum::Matrix4 _perspectiveProjection;
    public:

        const Magnum::Matrix4 &perspectiveProjection() const;

        void
        setPerspectiveProjection(const Magnum::Vector2 &size, const float near, const float far);

        void setPerspectiveProjection(float fov, float aspectRatio, float near, float far);

        void setPerspectiveProjection(Magnum::Rad fov, float aspectRatio, float near, float far);

        void
        setPerspectiveProjection(const Magnum::Vector2 &bottomLeft, const Magnum::Vector2 &topRight,
                                 float near, float far);
    };
}


#endif //CRAFTER_CLIPSPACE_H
