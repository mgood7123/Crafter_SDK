//
// Created by Matthew Good on 17/6/21.
//

#ifndef CRAFTER_VIEW_SPACE_H
#define CRAFTER_VIEW_SPACE_H

#include "View_Matrix.h"
#include "Wrappers/Translation.h"
#include "Wrappers/Rotation.h"
#include "WorldSpace.h"

namespace Crafter {
    class ViewSpace {
    public:
        View_Matrix view_matrix;

        static Magnum::Vector3 normalize(const Magnum::Vector3 & vector) {
            Magnum::Vector3 result;
            result[0] = std::abs(vector[0]);
            result[1] = std::abs(vector[1]);
            result[2] = std::abs(vector[2]);
            return result;
        }

        Magnum::Matrix4 lookAt(
                const ViewSpace & cameraPosition,
                const WorldSpace & targetPosition,
                const Magnum::Vector3 & worldUp
        ) const {
            return lookAt(cameraPosition.translationVector3(), targetPosition.translationVector3(), worldUp);
        }

        Magnum::Matrix4 lookAt(
                const WorldSpace & targetPosition,
                const Magnum::Vector3 & worldUp
        ) const {
            return lookAt(translationVector3(), targetPosition.translationVector3(), worldUp);
        }

        Magnum::Matrix4 lookAt(
                const Magnum::Vector3 & cameraPosition,
                const Magnum::Vector3 & targetPosition,
                const Magnum::Vector3 & worldUp
        ) const {
            return calculate_lookAt_matrix(cameraPosition, targetPosition, worldUp);
        }

        // Custom implementation of the LookAt function
        Magnum::Matrix4 calculate_lookAt_matrix(
                const Magnum::Vector3 & position,
                const Magnum::Vector3 & target,
                const Magnum::Vector3 & worldUp
        ) const {
            // 1. Position = known
            // 2. Calculate cameraDirection
            const Magnum::Vector3 zaxis = normalize(position - target);
            // 3. Get positive right axis vector
            const Magnum::Vector3 xaxis = normalize(Magnum::Math::cross(normalize(worldUp), zaxis));
            // 4. Calculate camera up vector
            const Magnum::Vector3 yaxis = Magnum::Math::cross(zaxis, xaxis);

            // Create translation and rotation matrix
            // In glm we access elements as mat[col][row] due to column-major layout
            // Identity matrix by default
            Magnum::Matrix4 translation = Magnum::Matrix4(Magnum::Math::IdentityInit, 1.0f);
            translation[3][0] = -position.x(); // Third column, first row
            translation[3][1] = -position.y();
            translation[3][2] = -position.z();
            // Identity matrix by default
            Magnum::Matrix4 rotation = Magnum::Matrix4(Magnum::Math::IdentityInit, 1.0f);
            rotation[0][0] = xaxis.x(); // First column, first row
            rotation[1][0] = xaxis.y();
            rotation[2][0] = xaxis.z();
            rotation[0][1] = yaxis.x(); // First column, second row
            rotation[1][1] = yaxis.y();
            rotation[2][1] = yaxis.z();
            rotation[0][2] = zaxis.x(); // First column, third row
            rotation[1][2] = zaxis.y();
            rotation[2][2] = zaxis.z();

            // Return lookAt matrix as combination of translation and rotation matrix
            return rotation * translation; // Remember to read from right to left (first translation then rotation)
        }

        TRANSLATION_WRAPPER_HEADER
        ROTATION_WRAPPER_HEADER
    };
}

#endif //CRAFTER_VIEW_SPACE_H
