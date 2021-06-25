//
// Created by Matthew Good on 10/6/21.
//

#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/Ui/Plane.h>
#include <Magnum/Ui/Anchor.h>
#include <Magnum/Ui/Button.h>
#include <Crafter/Demo/packages/View/View.cpp>
#include <Crafter/Demo/packages/View/TextView.cpp>
#include <Crafter/Demo/packages/View/TextView.h>
#include <Magnum/GL/Renderer.h>

CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_CPP(Crafter::Demo::Packages::UI, UI)

void Crafter::Demo::Packages::UI::viewportEvent(ViewportEvent &event) {
    GL::defaultFramebuffer.setViewport({{}, event.framebufferSize()});
}

void Crafter::Demo::Packages::UI::setup() {
}

void Crafter::Demo::Packages::UI::drawEvent() {

    const char & character = 'a';

    // clear to white
    GL::Renderer::setClearColor(Magnum::Color4{1,1,1,1});
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);

    // https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Text_Rendering_02

    FT_Library ft = nullptr;
    FT_Face face = nullptr;
    FT_Init_FreeType(&ft);

    auto tmp = Corrade::Utility::Resource{"MagnumUi"}.getRaw("SourceSansPro-Regular.ttf");
    auto m = Containers::Array<unsigned char>{NoInit, tmp.size()};
    Utility::copy(Containers::arrayCast<const unsigned char>(tmp), m);

    FT_New_Memory_Face(ft, m.begin(), m.size(), 0, &face);



    struct {
        float ax = 0.0f;    // advance.x
        float ay = 0.0f;    // advance.y

        float bw = 0.0f;    // bitmap.width;
        float bh = 0.0f;    // bitmap.height;

        float bl = 0.0f;    // bitmap_left;
        float bt = 0.0f;    // bitmap_top;

        float tx = 0.0f;    // x offset of glyph in texture coordinates
        float ty = 0.0f;    // y offset of glyph in texture coordinates
    } c;        // character information
    Magnum::GL::Texture2D texture2D{Corrade::NoCreate};
    auto height = 24;
    auto size = height;
    FT_Set_Pixel_Sizes(face, 0, height);
    FT_GlyphSlot g = face->glyph;

    unsigned int roww = 0;
    unsigned int rowh = 0;
    auto w = 0;
    auto h = 0;


    if (FT_Load_Char(face, character, FT_LOAD_RENDER)) {
        fprintf(stderr, "Loading character %c failed!\n", character);
        return;
    }
    roww += g->bitmap.width + 1;
    rowh = std::max(rowh, g->bitmap.rows);

    w = roww;
    h += rowh;

    /* Create a texture that will be used to hold all ASCII glyphs */

    texture2D.setStorage(1, Magnum::GL::TextureFormat::RGBA8, {static_cast<int>(w),static_cast<int>(h)});
    texture2D.setWrapping(Magnum::GL::SamplerWrapping::ClampToEdge);
    texture2D.setMagnificationFilter(Magnum::GL::SamplerFilter::Linear);

    /* Paste all glyph bitmaps into the texture, remembering the offset */
    int ox = 0;
    int oy = 0;

    rowh = 0;

    if (FT_Load_Char(face, character, FT_LOAD_RENDER)) {
        fprintf(stderr, "Loading character %c failed!\n", character);
        return;
    }

    Containers::ArrayView<const void> data{g->bitmap.buffer, (g->bitmap.width * g->bitmap.rows) * 4};
    Magnum::GL::Buffer buffer{Magnum::GL::Buffer::TargetHint::PixelPack};
    buffer.setData(
            data,
            Magnum::GL::BufferUsage::StaticDraw
    );

    Magnum::GL::BufferImage2D bufferImage2D {
            Magnum::PixelStorage{}
                    .setAlignment(1)
                    .setRowLength(g->bitmap.width)
                    .setImageHeight(g->bitmap.rows),
            Magnum::GL::PixelFormat::RGBA,
            Magnum::GL::PixelType::UnsignedByte,
            {static_cast<int>(g->bitmap.width), static_cast<int>(g->bitmap.rows)},
            std::move(buffer),
            data.size()
    };
    texture2D.setSubImage(0, {ox, oy}, std::move(bufferImage2D));

    c.ax = g->advance.x >> 6;
    c.ay = g->advance.y >> 6;

    c.bw = g->bitmap.width;
    c.bh = g->bitmap.rows;

    c.bl = g->bitmap_left;
    c.bt = g->bitmap_top;

    c.tx = ox / (float) w;
    c.ty = oy / (float) h;

    rowh = std::max(rowh, g->bitmap.rows);
    ox += g->bitmap.width + 1;

    fprintf(stderr, "Generated a %d x %d (%d bytes) texture atlas\n", w, h, w * h);




    float x = 8, y = 50, sx = 1, sy = 1;

    // flip y axis
    float y_ = static_cast<float>(height) - y;
    const uint8_t *p;

    struct point {
        GLfloat x;
        GLfloat y;
        GLfloat s;
        GLfloat t;
    };

    point coords[6];
    int c_ = 0;

    /* Calculate the vertex and texture coordinates */
    float x2 = x + c.bl * sx;
    float y2 = -y_ - c.bt * sy;
    float w_ = c.bw * sx;
    float h_ = c.bh * sy;

    /* Advance the cursor to the start of the next character */
    x += c.ax * sx;
    y += c.ay * sy;

    /* Skip glyphs that have no pixels */
    if ((w_ == 0.0f) || (h_ == 0.0f))
        return;

    coords[0] = {x2, -y2, c.tx, c.ty};
    coords[1] = {x2 + w_, -y2, c.tx + c.bw / w, c.ty};
    coords[2] = {x2, -y2 - h_, c.tx, c.ty + c.bh / h};
    coords[3] = {x2 + w_, -y2, c.tx + c.bw / w_, c.ty};
    coords[4] = {x2, -y2 - h_, c.tx, c.ty + c.bh / h};
    coords[5] = {x2 + w_, -y2 - h_, c.tx + c.bw / w,c.ty + c.bh / h};

    /* Draw all the character on the screen in one go */

    GL::Mesh mesh;
    GL::Buffer vertexBuffer, indexBuffer;

    /* Render vertices and upload them */
    std::vector<Vertex> vertices;
    for(int i = 0; i <= 6; i++) {
        vertices.push_back({{coords[0].x, coords[0].y}, {coords[0].s, coords[0].t}});
    }
    vertexBuffer.setData({vertices.data(), vertices.size()}, GL::BufferUsage::DynamicDraw);

    const UnsignedInt glyphCount = vertices.size();
    const UnsignedInt indexCount = glyphCount*6;

    /* Render indices and upload them */
    Containers::Array<char> indices;
    MeshIndexType indexType;
    std::tie(indices, indexType) = renderIndicesInternal(glyphCount);
    indexBuffer.setData(indices, GL::BufferUsage::StaticDraw);

    /* Configure mesh except for vertex buffer (depends on dimension count, done
   in subclass) */
    mesh.setPrimitive(MeshPrimitive::Triangles)
            .setCount(indexCount)
            .addVertexBuffer(vertexBuffer, 0,
                             typename Shaders::GenericGL<2>::Position(
                                     Shaders::GenericGL<2>::Position::Components::Two),
                             typename Shaders::GenericGL<2>::TextureCoordinates())
            .setIndexBuffer(indexBuffer, 0, indexType, 0, vertexBuffer.size());

    /* Draw the text on the screen */

    /* Enable blending, necessary for our alpha texture */

    GL::Renderer::enable(GL::Renderer::Feature::Blending);
    GL::Renderer::setBlendFunction(GL::Renderer::BlendFunction::One, GL::Renderer::BlendFunction::OneMinusSourceAlpha);
    GL::Renderer::setBlendEquation(GL::Renderer::BlendEquation::Add, GL::Renderer::BlendEquation::Add);

    Magnum::Shaders::VectorGL2D shader_;
    shader_.setTransformationProjectionMatrix(
                    Matrix3::projection(
                            Vector2::xScale(Vector2{windowSize()}.aspectRatio()))
    )

                    // text color black
            .setColor({0,1,0,1})
            .bindVectorTexture(texture2D)
            .draw(mesh);

    GL::Renderer::disable(GL::Renderer::Feature::Blending);


    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    swapBuffers();
    redraw();
}