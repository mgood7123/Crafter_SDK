//
// Created by Matthew Good on 14/6/21.
//

#ifndef CRAFTER_CAMERA_H
#define CRAFTER_CAMERA_H

#include <Magnum/Magnum.h> // Magnum:: typedefs
#include <Magnum/Math/Matrix4.h> // Magnum::Matrix4
#include "Rotation.h"
#include "Translation.h"

namespace Crafter {
    class Camera: public Rotation, public Translation {
    private:
        Magnum::Matrix4 _modelView, _perspectiveProjection;

        bool hasPerspectiveProjection = false;

    public:

        const Magnum::Matrix4 &modelView() const;

        const Magnum::Matrix4 &perspectiveProjection() const;

        void setPerspectiveProjection(const Magnum::Vector2 & size, const float near, const float far);

        void setPerspectiveProjection(Magnum::Rad fov, float aspectRatio, float near, float far);

        void setPerspectiveProjection(const Magnum::Vector2 & bottomLeft, const Magnum::Vector2 & topRight, float near, float far);

        void updateCamera();
    };
}


#endif //CRAFTER_CAMERA_H
