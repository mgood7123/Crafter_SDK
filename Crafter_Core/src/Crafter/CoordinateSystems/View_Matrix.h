//
// Created by Matthew Good on 17/6/21.
//

#ifndef CRAFTER_VIEW_MATRIX_H
#define CRAFTER_VIEW_MATRIX_H

#include <Crafter/CoordinateSystems/Rotation.h>
#include <Crafter/CoordinateSystems/Translation.h>

namespace Crafter {
    /**
     * part of View Space
     */
    class View_Matrix: public Translation, public Rotation {};
}


#endif //CRAFTER_VIEW_MATRIX_H
