//
// Created by Matthew Good on 18/6/21.
//

#ifndef CRAFTER_WORLDENGINEBASE_H
#define CRAFTER_WORLDENGINEBASE_H

#include <Magnum/SceneGraph/MatrixTransformation3D.hpp>
#include <Magnum/SceneGraph/Drawable.hpp>

class WorldEngineBase {
    typedef Magnum::SceneGraph::MatrixTransformation3D WORLD_TRANSFORMATION_TYPE;
public:
    typedef Magnum::SceneGraph::Scene<WORLD_TRANSFORMATION_TYPE> Scene3D;
    typedef Magnum::SceneGraph::Object<WORLD_TRANSFORMATION_TYPE> Object3D;
};

#endif //CRAFTER_WORLDENGINEBASE_H
