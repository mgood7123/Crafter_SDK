//
// Created by Matthew Good on 14/6/21.
//

#ifndef CRAFTER_WORLDENGINE_H
#define CRAFTER_WORLDENGINE_H

#include "WorldEngineBase.h"
#include <Crafter/CameraControls/FreeformCamera.h>
#include <Magnum/DebugTools/FrameProfiler.h>

namespace Crafter {
    namespace WorldEngine {
        using namespace Magnum;
        using namespace SceneGraph;
        using namespace Magnum::Math::Literals;

        typedef WorldEngineBase::Object3D Object3D;
        typedef WorldEngineBase::Scene3D Scene3D;

        typedef FreeformCamera<Scene3D, Object3D> FreeformCamera3D;

        class WorldEngine : public WorldEngineBase {
            Magnum::DebugTools::FrameProfilerGL profiler;

            FreeformCamera3D * _freeformCamera;

            WorldEngineBase::Scene3D _scene;
            Object3D* _cameraObject;
            Camera3D* _camera;
            DrawableGroup3D _drawables;

        public:
            void setup();

            void attachToCamera(Camera3D *camera);

            void updateAspectRatio(const Vector2i & viewport, float aspectRatio);

            void rotateRelative(Vector2 relative);

            void draw();
        };
    }
}

#endif //CRAFTER_WORLDENGINE_H
