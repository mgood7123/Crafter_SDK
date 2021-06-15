//
// Created by Matthew Good on 14/6/21.
//

#include "MeshGenerator.h"
#include <Magnum/Mesh.h>
#include <Magnum/Math/Matrix.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Shaders/FlatGL.h>

Magnum::GL::Mesh Crafter::WorldEngine::MeshGenerator::triangleWireframe2D(const Magnum::Vector2 &left,
                                                                    const Magnum::Vector2 &right,
                                                                    const Magnum::Vector2 &top) {
    const VertexWireframe2D vertex[] {
            {(left)},    {(right)},
            {(right)}, {(top)},
            {(top)},  {(left)}
    };

    Magnum::GL::Buffer vertices(vertex);

    Magnum::GL::Mesh mesh;
    mesh
        .setPrimitive(Magnum::MeshPrimitive::Lines)
        .addVertexBuffer(std::move(vertices), 0, Magnum::GL::Attribute<0, Magnum::Vector2> {})
        .setCount(sizeof(vertex)/sizeof(VertexWireframe2D));
    return mesh;
}

Magnum::GL::Mesh Crafter::WorldEngine::MeshGenerator::triangle2D(const Magnum::Vector2 &left,
                                                                 const Magnum::Vector2 &right,
                                                                 const Magnum::Vector2 &top) {
    const Vertex2D vertex[] {
            {left , {0.0f, 0.0f}}, /* Left position and texture coordinate for mapping textures */
            {right, {1.0f, 0.0f}}, /* Right position and texture coordinate for mapping textures */
            {top  , {0.5f, 1.0f}}  /* Top position and texture coordinate for mapping textures */
    };

    Magnum::GL::Buffer buffer(vertex);

    Magnum::GL::Mesh mesh;
    mesh
        .addVertexBuffer(
                    std::move(buffer), 0,
                    Magnum::GL::Attribute<0, Magnum::Vector2> {},
                    Magnum::GL::Attribute<1, Magnum::Vector2> {}
            )
        .setCount(sizeof(vertex)/sizeof(Vertex2D));
    return mesh;
}

Magnum::GL::Mesh Crafter::WorldEngine::MeshGenerator::planeWireframe2D(
        const Magnum::Vector2 &topLeft, const Magnum::Vector2 &topRight,
        const Magnum::Vector2 &bottomRight, const Magnum::Vector2 &bottomLeft
) {
    const VertexWireframe2D vertex[] {
            {(topRight)},    {(bottomRight)}, // right
            {(bottomRight)}, {(bottomLeft)},  // bottom
            {(bottomLeft)},  {(topLeft)},     // left
            {(topLeft)},     {(topRight)}     // top
    };

    Magnum::GL::Buffer vertices(vertex);

    Magnum::GL::Mesh mesh;
    mesh
        .setPrimitive(Magnum::MeshPrimitive::Lines)
        .addVertexBuffer(std::move(vertices), 0, Magnum::GL::Attribute<0, Magnum::Vector2> {})
        .setCount(sizeof(vertex)/sizeof(VertexWireframe2D));
    return mesh;
}

Magnum::GL::Mesh Crafter::WorldEngine::MeshGenerator::plane2D(
        const Magnum::Vector2 &topLeft, const Magnum::Vector2 &topRight,
        const Magnum::Vector2 &bottomRight, const Magnum::Vector2 &bottomLeft
) {
    const Vertex2D vertex[] {
            {topRight,    {1.0f, 1.0f}},
            {bottomRight, {1.0f, 0.0f}},
            {bottomLeft,  {0.0f, 0.0f}},
            {topLeft,     {0.0f, 1.0f}}
    };

    Magnum::UnsignedInt indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    Magnum::GL::Buffer vertexBuffer(vertex);
    Magnum::GL::Buffer indexBuffer(indices);

    Magnum::GL::Mesh mesh;
    mesh
        .setPrimitive(Magnum::MeshPrimitive::TriangleStrip)
        .addVertexBuffer(
                    std::move(vertexBuffer), 0,
                    Magnum::GL::Attribute<0, Magnum::Vector2> {}, Magnum::GL::Attribute<1, Magnum::Vector2> {}
            )
        .setCount(sizeof(vertex)/sizeof(Vertex2D))
        .setIndexBuffer(
                    std::move(indexBuffer), 0, Magnum::GL::MeshIndexType::UnsignedInt
            )
        .setCount(sizeof(indices)/sizeof(Magnum::UnsignedInt))
            ;
    return mesh;
}

Magnum::GL::Mesh Crafter::WorldEngine::MeshGenerator::triangle3D() {
    using namespace Magnum;
    using namespace Magnum::Math::Literals;

    struct TriangleVertex {
        Vector3 position;
        Color3 color;
    };
    const TriangleVertex data[] {
            {{-0.5f, -0.5f, 0.0f}, 0xff0000_rgbf},    /* Left vertex, red color */
            {{ 0.5f, -0.5f, 0.0f}, 0x00ff00_rgbf},    /* Right vertex, green color */
            {{ 0.0f,  0.5f, 0.0f}, 0x0000ff_rgbf}     /* Top vertex, blue color */
    };

    GL::Buffer buffer;
    buffer.setData(data, GL::BufferUsage::StaticDraw);

    GL::Mesh mesh;
    mesh.setCount(3)
            .addVertexBuffer(std::move(buffer), 0, Magnum::Shaders::FlatGL3D::Position{}, Magnum::Shaders::FlatGL3D::Color3{});
    return mesh;
}
