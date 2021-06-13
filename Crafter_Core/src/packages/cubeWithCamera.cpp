//
// Created by Matthew Good on 10/6/21.
//

#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/Trade/MeshData.h>

CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_CPP(Crafter::Packages::CubeWithCamera, CubeWithCamera)

void Crafter::Packages::CubeWithCamera::setup() {
    GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);

    Trade::MeshData cube = Primitives::cubeSolid();

    GL::Buffer vertices;
    vertices.setData(MeshTools::interleave(cube.positions3DAsArray(),
                                           cube.normalsAsArray()));

    std::pair<Containers::Array<char>, MeshIndexType> compressed =
            MeshTools::compressIndices(cube.indicesAsArray());
    GL::Buffer indices;
    indices.setData(compressed.first);

    _mesh.setPrimitive(cube.primitive())
            .setCount(cube.indexCount())
            .addVertexBuffer(std::move(vertices), 0, Shaders::PhongGL::Position{},
                             Shaders::PhongGL::Normal{})
            .setIndexBuffer(std::move(indices), 0, compressed.second);

    camera.setPerspectiveProjection(35.0_degf, Vector2{windowSize()}.aspectRatio(), 0.01f, 100.0f);
    camera.setRotation(30.0f, 40.0f, 0.0f);
    camera.setTranslation(0.0f, 0.0f, -10.0f);
    camera.updateCamera();

    _color = Color3::fromHsv({35.0_degf, 1.0f, 1.0f});
}

void Crafter::Packages::CubeWithCamera::drawEvent() {
    GL::defaultFramebuffer.clear(
            GL::FramebufferClear::Color|GL::FramebufferClear::Depth);

    _shader.setLightPositions({{1.4f, 1.0f, 0.75f, 0.0f}})
            .setDiffuseColor(_color)
            .setAmbientColor(Color3::fromHsv({_color.hue(), 1.0f, 0.3f}))
            .setTransformationMatrix(camera.rotation())
            .setProjectionMatrix(camera.modelView())
            .draw(_mesh);

    swapBuffers();
}

void Crafter::Packages::CubeWithCamera::viewportEvent(ViewportEvent &event) {
    GL::defaultFramebuffer.setViewport({{}, event.framebufferSize()});

    camera.setPerspectiveProjection(35.0_degf, Vector2{GL::defaultFramebuffer.viewport().size()}.aspectRatio(), 0.01f, 100.0f);
    camera.updateCamera();
}

void Crafter::Packages::CubeWithCamera::mousePressEvent(MouseEvent& event) {
    if(event.button() != MouseEvent::Button::Left) return;
    event.setAccepted();
}

void Crafter::Packages::CubeWithCamera::mouseReleaseEvent(MouseEvent& event) {
    _color = Color3::fromHsv({_color.hue() + 50.0_degf, 1.0f, 1.0f});

    event.setAccepted();
    redraw();
}

void Crafter::Packages::CubeWithCamera::mouseMoveEvent(MouseMoveEvent& event) {
    if(!(event.buttons() & MouseMoveEvent::Button::Left)) return;

    Vector2 delta = 3.0f*Vector2{event.relativePosition()}/Vector2{windowSize()};

    // move camera up and down
    camera.addTranslation(0.0f, -delta.y(), 0.0f);
    camera.updateCamera();

    event.setAccepted();
    redraw();
}
