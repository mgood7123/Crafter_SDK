//
// Created by Matthew Good on 10/6/21.
//

#ifndef CRAFTER_POLYGON_H
#define CRAFTER_POLYGON_H
#include "../PolygonDeformer/PolygonDeformerBlueprint.h"

namespace Crafter {
    namespace Packages {
        class Polygon : public Crafter::Package {
            PolygonDeformer::Blueprint blueprint;
        public:
            CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_HPP(Polygon);

            void setup() override;

            void drawEvent() override;
        };
    }
}
#endif //CRAFTER_POLYGON_H
