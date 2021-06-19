//
// Created by Matthew Good on 14/6/21.
//

#ifndef CRAFTER_BLUEPRINT_H
#define CRAFTER_BLUEPRINT_H

#include <Crafter/WorldEngine/WorldEngine.h>

namespace Crafter {
    class Blueprint {
        WorldEngine::WorldEngine engine;
    public:
        void setup();

        void attachToCamera(Magnum::SceneGraph::Camera3D * camera);

        void updateAspectRatio(const Magnum::Vector2i & viewport, float aspectRatio);

        void rotateRelative(Magnum::Vector2 relative);

        void draw();
    };
}

#endif //CRAFTER_BLUEPRINT_H
