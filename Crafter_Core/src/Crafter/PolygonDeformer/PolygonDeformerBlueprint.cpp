//
// Created by Matthew Good on 12/6/21.
//

#include "PolygonDeformerBlueprint.h"
#include <Magnum/GL/Mesh.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Vector2.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Primitives/Grid.h>
#include <Magnum/Shaders/VertexColorGL.h>
#include <Magnum/Shaders/FlatGL.h>
#include <Magnum/Trade/MeshData.h>

using namespace Magnum;

void PolygonDeformer::Blueprint::setPolygonResolution(int polygonResolution) {
    this->polygonResolution = polygonResolution;
}

int PolygonDeformer::Blueprint::getPolygonResolution() {
    return polygonResolution;
}

void PolygonDeformer::Blueprint::draw() {
    Shaders::FlatGL3D shader;
    shader.setColor({0.0f,0.0f,0.0f,1.0f})
        .draw(
                MeshTools::compile(
                        Primitives::grid3DWireframe(
                                {polygonResolution-1, polygonResolution-1}
                        )
                )
        );
}
