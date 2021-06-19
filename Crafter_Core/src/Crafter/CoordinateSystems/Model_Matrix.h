//
// Created by Matthew Good on 17/6/21.
//

#ifndef CRAFTER_MODEL_MATRIX_H
#define CRAFTER_MODEL_MATRIX_H


#include "Translation.h"
#include "Scale.h"
#include "Rotation.h"

namespace Crafter {
    /**
     * part of World Space
     */
    class Model_Matrix : public Translation, public Scale, public Rotation {
    public:
        Model_Matrix() = default;

        Model_Matrix(const Model_Matrix & other) : Translation(other), Scale(other), Rotation(other) {};

        Model_Matrix &operator=(const Model_Matrix & other) {
            Translation::operator=(other);
            Scale::operator=(other);
            Rotation::operator=(other);
            return *this;
        };

        Model_Matrix(Model_Matrix &&other) : Translation(std::move(other)), Scale(std::move(other)), Rotation(std::move(other)) {}

        Model_Matrix &operator=(Model_Matrix &&other) noexcept {
            Translation::operator=(std::move(other));
            Scale::operator=(std::move(other));
            Rotation::operator=(std::move(other));
            return *this;
        }
    };
}


#endif //CRAFTER_MODEL_MATRIX_H
