//
// Created by Matthew Good on 16/6/21.
//

#ifndef CRAFTER_DRAWABLE_OBJECTS_TRIANGLE_H
#define CRAFTER_DRAWABLE_OBJECTS_TRIANGLE_H

#include "Primatives/Triangle.h"

namespace Crafter {
    namespace WorldEngine {
        namespace DrawableObjects {
            class Triangle : public DrawableObject {
                Primitives::Triangle *left, *right, *top_A, *top_B, *back_A, *back_B, *bottom_A, *bottom_B;

            public:
                DRAWABLE_OBJECT_CONSTRUCTOR_HPP(Triangle)

                void init(const Magnum::Color3 &color) {
                    left = createDrawableObject<Primitives::Triangle>("left");
                    left->init(
                            {-1, -1, 1},
                            {1, -1, 1},
                            {1, 1, 1},
                            color
                    );
                    right = createDrawableObject<Primitives::Triangle>("right");
                    right->init(
                            {-1, -1, 1},
                            {1, -1, 1},
                            {-1, 1, 1},
                            color
                    );
                    top_A = createDrawableObject<Primitives::Triangle>("top_A");
                    top_A->init(
                            {-1, -1, 1},
                            {1, -1, 1},
                            {1, 1, -1},
                            color
                    );
                    top_B = createDrawableObject<Primitives::Triangle>("top_B");
                    top_B->init(
                            {-1, -1, 1},
                            {1, 1, -1},
                            {-1, 1, -1},
                            color
                    );
                    back_A = createDrawableObject<Primitives::Triangle>("back_A");
                    back_A->init(
                            {-1, -1, 1},
                            {1, -1, 1},
                            {1, 1, 1},
                            color
                    );
                    back_B = createDrawableObject<Primitives::Triangle>("back_B");
                    back_B->init(
                            {-1, -1, 1},
                            {1, 1, 1},
                            {-1, 1, 1},
                            color
                    );
                    bottom_A = createDrawableObject<Primitives::Triangle>("bottom_A");
                    bottom_A->init(
                            {-1, -1, 1},
                            {1, -1, -1},
                            {1, -1, 1},
                            color
                    );
                    bottom_B = createDrawableObject<Primitives::Triangle>("bottom_B");
                    bottom_B->init(
                            {-1, -1, 1},
                            {-1, -1, -1},
                            {1, -1, -1},
                            color
                    );

                    right->addRotationY(180);
                    top_A->addRotationY(-90);
                    top_B->addRotationY(-90);
                    back_A->addRotationY(90);
                    back_B->addRotationY(90);
                }

                void draw(Crafter::Camera *mainCamera) override {
                    left->draw(mainCamera);
                    right->draw(mainCamera);
                    top_A->draw(mainCamera);
                    top_B->draw(mainCamera);
                    back_A->draw(mainCamera);
                    back_B->draw(mainCamera);
                    bottom_A->draw(mainCamera);
                    bottom_B->draw(mainCamera);
                }
            };
        }
    }
}

#endif //CRAFTER_DRAWABLE_OBJECTS_TRIANGLE_H
