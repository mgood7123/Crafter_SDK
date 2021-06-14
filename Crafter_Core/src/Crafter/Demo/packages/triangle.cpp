//
// Created by Matthew Good on 10/6/21.
//

#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Buffer.h>

CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_CPP(Crafter::Demo::Packages::Triangle, Triangle)

void Crafter::Demo::Packages::Triangle::setup() {

    struct TriangleVertex {
        Vector2 position;
        Color3 color;
    };
    const TriangleVertex data[]{
            {{-0.5f, -0.5f}, 0xff0000_rgbf},    /* Left vertex, red color */
            {{ 0.5f, -0.5f}, 0x00ff00_rgbf},    /* Right vertex, green color */
            {{ 0.0f,  0.5f}, 0x0000ff_rgbf}     /* Top vertex, blue color */
    };

    GL::Buffer buffer;
    buffer.setData(data);

    _mesh.setCount(3)
            .addVertexBuffer(std::move(buffer), 0,
                             Shaders::VertexColorGL2D::Position{},
                             Shaders::VertexColorGL2D::Color3{});
}

void Crafter::Demo::Packages::Triangle::drawEvent() {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);

    _shader.draw(_mesh);
    swapBuffers();
}
