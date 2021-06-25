//
// Created by Matthew Good on 10/6/21.
//

#ifndef CRAFTER_UI_H
#define CRAFTER_UI_H
#include <Magnum/Ui/UserInterface.h>

namespace Crafter {
    namespace Demo {
        namespace Packages {
            class UI : public Crafter::Package {
            public:
                CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_HPP(UI);

                void setup() override;

                void viewportEvent(ViewportEvent &event) override;

                void drawEvent() override;
            };
        }
    }
}
#endif //CRAFTER_UI_H
