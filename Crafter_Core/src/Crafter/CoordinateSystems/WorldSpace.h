//
// Created by Matthew Good on 17/6/21.
//

#ifndef CRAFTER_WORLDSPACE_H
#define CRAFTER_WORLDSPACE_H

#include "Wrappers/Translation.h"
#include "Wrappers/Scale.h"
#include "Wrappers/Rotation.h"
#include "Model_Matrix.h"

namespace Crafter {
    class WorldSpace {
    public:
        Model_Matrix model_matrix;

        TRANSLATION_WRAPPER_HEADER
        SCALE_WRAPPER_HEADER
        ROTATION_WRAPPER_HEADER
    };
}

#endif //CRAFTER_WORLDSPACE_H
