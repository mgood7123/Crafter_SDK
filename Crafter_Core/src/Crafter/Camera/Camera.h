//
// Created by Matthew Good on 14/6/21.
//

#ifndef CRAFTER_CAMERA_H
#define CRAFTER_CAMERA_H

#include <Crafter/CoordinateSystems/ClipSpace.h>
#include <Crafter/CoordinateSystems/ViewSpace.h>

namespace Crafter {
    class Camera: public ClipSpace, public ViewSpace {
    public:
        Magnum::Matrix4 _modelView;
        const Magnum::Matrix4 &modelView() const;
        void updateCamera();
    };
}


#endif //CRAFTER_CAMERA_H
