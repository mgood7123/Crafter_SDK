//
// Created by Matthew Good on 10/6/21.
//

#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/Trade/MeshData.h>

CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_CPP(Crafter::Demo::Packages::Cube, Cube)

void Crafter::Demo::Packages::Cube::setup() {
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

    _transformation = Matrix4::rotationX(30.0_degf)*Matrix4::rotationY(40.0_degf);
    _projection =
            Matrix4::perspectiveProjection(
                    35.0_degf, Vector2{windowSize()}.aspectRatio(), 0.01f, 100.0f)*
            Matrix4::translation(Vector3::zAxis(-10.0f));
    _color = Color3::fromHsv({35.0_degf, 1.0f, 1.0f});
}

void Crafter::Demo::Packages::Cube::drawEvent() {
    GL::defaultFramebuffer.clear(
            GL::FramebufferClear::Color|GL::FramebufferClear::Depth);

    _shader.setLightPositions({{1.4f, 1.0f, 0.75f, 0.0f}})
            .setDiffuseColor(_color)
            .setAmbientColor(Color3::fromHsv({_color.hue(), 1.0f, 0.3f}))
            .setTransformationMatrix(_transformation)
            .setNormalMatrix(_transformation.normalMatrix())
            .setProjectionMatrix(_projection)
            .draw(_mesh);

    swapBuffers();
}

void Crafter::Demo::Packages::Cube::viewportEvent(ViewportEvent &event) {
    GL::defaultFramebuffer.setViewport({{}, event.framebufferSize()});

    _projection = Matrix4::perspectiveProjection(35.0_degf, Vector2{GL::defaultFramebuffer.viewport().size()}.aspectRatio(), 0.01f, 100.0f)*
                  Matrix4::translation(Vector3::zAxis(-10.0f));
}

void Crafter::Demo::Packages::Cube::mousePressEvent(MouseEvent& event) {
    if(event.button() != MouseEvent::Button::Left) return;
    event.setAccepted();
}

void Crafter::Demo::Packages::Cube::mouseReleaseEvent(MouseEvent& event) {
    _color = Color3::fromHsv({_color.hue() + 50.0_degf, 1.0f, 1.0f});

    event.setAccepted();
    redraw();
}

void Crafter::Demo::Packages::Cube::mouseMoveEvent(MouseMoveEvent& event) {
    if(!(event.buttons() & MouseMoveEvent::Button::Left)) return;

    Vector2 delta = 3.0f*Vector2{event.relativePosition()}/Vector2{windowSize()};
    _transformation =
            Matrix4::rotationX(Rad{delta.y()})*
            _transformation*
            Matrix4::rotationY(Rad{delta.x()});

    event.setAccepted();
    redraw();
}
