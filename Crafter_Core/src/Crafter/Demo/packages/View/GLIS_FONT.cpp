//
// Created by Matthew Good on 25/6/21.
//

#include <Magnum/GL/BufferImage.h>
#include <Magnum/GL/PixelFormat.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Mesh.h>
#include <Corrade/Utility/Algorithms.h>
#include "GLIS_FONT.h"
#include "TextureHelpers.h"
#include "TextureHelpers.cpp"
#include "../../../../../../Crafter_Magnum/magnum-plugins/src/MagnumPlugins/FreeTypeFont/FreeTypeFont.h"
#include <Magnum/Shaders/VectorGL.h>
#include <Corrade/PluginManager/Manager.h>
#include <Magnum/Text/GlyphCache.h>
#include <Magnum/Text/Alignment.h>
#include <Magnum/Text/Renderer.h>
#include <Corrade/Utility/DebugStl.h>
#include <Corrade/TestSuite/Comparator.h>
#include <Corrade/TestSuite/Tester.h>

void GLIS_FONT::set_max_width_height(GLint width, GLint height) {
    this->width = width;
    this->height = height;
}

GLIS_FONT::ATLAS_TYPE * GLIS_FONT::add_font(const char *id, const char *path) {
    font_init *i = new font_init(path);
    i->load();
    Object * o = font.newObject(
            0,
            0,
            ATLAS_TYPE{
                    id,
                    path,
                    AnyOpt(i, true),
                    AnyOpt(new font_data(Kernel()), true)
            }
    );
    return o == nullptr ? nullptr : o->resource.get<ATLAS_TYPE*>();
}

GLIS_FONT::ATLAS_TYPE * GLIS_FONT::add_font(const char *id, const Containers::ArrayView<const char> & data) {
    font_init *i = new font_init(data);
    i->load();
    Object * o = font.newObject(
            0,
            0,
            ATLAS_TYPE{
                    id,
                    nullptr,
                    AnyOpt(i, true),
                    AnyOpt(new font_data(Kernel()), true)
            }
    );
    return o == nullptr ? nullptr : o->resource.get<ATLAS_TYPE*>();
}

Object *GLIS_FONT::find_font(const char *id) {
    size_t resource_len = strlen(id);
    int page = 1;
    size_t index = 0;
    size_t page_size = font.table->page_size;
    printf("font.table->Page.count() is %d\n", font.table->Page.count());
    for (; page <= font.table->Page.count(); page++) {
        index = ((page_size * page) - page_size);
        for (; index < page_size * page; index++)
            if (font.table->table[index] != nullptr) {
                const char *data = font.table->table[index]->resource.get<ATLAS_TYPE *>()->first;
                if (!memcmp(data, id, resource_len))
                    return font.table->table[index];
            } else {
                printf("font.table->table[%zu] is nullptr\n", index);
            }
    }
    return nullptr;
}

GLIS_FONT::ATLAS_TYPE *GLIS_FONT::get_atlas(const char *id) {
    auto o = find_font(id);
    if (o == nullptr) return nullptr;
    return o->resource.get<ATLAS_TYPE *>();
}

GLIS_FONT::atlas * GLIS_FONT::add_font_size(const char *id, int size) {
    ATLAS_TYPE *data = get_atlas(id);
    if (data == nullptr) return nullptr;
    auto fontInit = data->third.get<font_init *>();
    auto fontData = data->fourth.get<font_data *>();
    atlas * x = new atlas();
    x->init(fontInit->face, size);
    x->font_source = fontInit;
    Object * o = fontData->sizes.newObject(0, 0, AnyOpt(x, true));
    return o == nullptr ? nullptr : o->resource.get<atlas*>();
}

GLIS_FONT::atlas *GLIS_FONT::find_size(const char *id, GLIS_FONT::font_data *fontData, int size) {
    Kernel *x = &fontData->sizes;
    if (x->table->Page.count() == 0) {
        printf("font %s has no sizes created\n", id);
    } else {
        int page = 1;
        size_t index = 0;
        size_t page_size = x->table->page_size;
        for (; page <= x->table->Page.count(); page++) {
            index = ((page_size * page) - page_size);
            for (; index < page_size * page; index++)
                if (x->table->table[index] != nullptr) {
                    if (x->table->table[index]->resource.has_value()) {
                        printf("checking index %zu\n", index);
                        atlas *atlas_ = x->table->table[index]->resource.get<atlas *>();
                        if (atlas_->size == size) {
                            printf("found requested size at index %zu\n", index);
                            return atlas_;
                        }
                    } else
                        printf("index %zu has no resource\n", index);
                }
        }
    }
    printf("failed to find size %d\n", size);
    return nullptr;
}

GLIS_FONT::atlas *GLIS_FONT::find_size(const char *id, int size) {
    ATLAS_TYPE *data = get_atlas(id);
    if (data == nullptr) return nullptr;
    font_data *fontData = data->fourth.get<font_data *>();
    assert(fontData != nullptr);
    return find_size(id, fontData, size);
}

void GLIS_FONT::set_color(const GLfloat color[4]) {
    current_color = const_cast<GLfloat *>(color);
}

template<class T> void createIndices(void* output, const UnsignedInt glyphCount) {
    T* const out = reinterpret_cast<T*>(output);
    for(UnsignedInt i = 0; i != glyphCount; ++i) {
        /* 0---2 0---2 5
           |   | |  / /|
           |   | | / / |
           |   | |/ /  |
           1---3 1 3---4 */

        const T vertex = T(i)*4;
        const UnsignedInt pos = T(i)*6;
        out[pos]   = vertex;
        out[pos+1] = vertex+1;
        out[pos+2] = vertex+2;
        out[pos+3] = vertex+1;
        out[pos+4] = vertex+3;
        out[pos+5] = vertex+2;
    }
}

std::pair<Containers::Array<char>, MeshIndexType> renderIndicesInternal(const UnsignedInt glyphCount) {
    const UnsignedInt vertexCount = glyphCount*4;
    const UnsignedInt indexCount = glyphCount*6;

    Containers::Array<char> indices;
    MeshIndexType indexType;
    if(vertexCount <= 256) {
        indexType = MeshIndexType::UnsignedByte;
        indices = Containers::Array<char>(indexCount*sizeof(UnsignedByte));
        createIndices<UnsignedByte>(indices, glyphCount);
    } else if(vertexCount <= 65536) {
        indexType = MeshIndexType::UnsignedShort;
        indices = Containers::Array<char>(indexCount*sizeof(UnsignedShort));
        createIndices<UnsignedShort>(indices, glyphCount);
    } else {
        indexType = MeshIndexType::UnsignedInt;
        indices = Containers::Array<char>(indexCount*sizeof(UnsignedInt));
        createIndices<UnsignedInt>(indices, glyphCount);
    }

    return {std::move(indices), indexType};
}

struct Vertex {
    Vector2 position, textureCoordinates;
};

#if (false)
static class REPURPOSED_RENDERER {

    template<class T> void createIndices(void* output, const UnsignedInt glyphCount) {
        T* const out = reinterpret_cast<T*>(output);
        for(UnsignedInt i = 0; i != glyphCount; ++i) {
            /* 0---2 0---2 5
               |   | |  / /|
               |   | | / / |
               |   | |/ /  |
               1---3 1 3---4 */

            const T vertex = T(i)*4;
            const UnsignedInt pos = T(i)*6;
            out[pos]   = vertex;
            out[pos+1] = vertex+1;
            out[pos+2] = vertex+2;
            out[pos+3] = vertex+1;
            out[pos+4] = vertex+3;
            out[pos+5] = vertex+2;
        }
    }

    struct Vertex {
        Vector2 position, textureCoordinates;
    };

    static std::tuple<std::vector<Vertex>, Range2D> renderVerticesInternal(GLIS_FONT::atlas *atlas, const std::string& text, const Alignment alignment) {
        /* Output data, reserve memory as when the text would be ASCII-only. In
           reality the actual vertex count will be smaller, but allocating more at
           once is better than reallocating many times later. */
        std::vector<Vertex> vertices;
        vertices.reserve(text.size()*4);

        /* Total rendered bounds, intial line position, line increment, last+1
           vertex on previous line */
        Range2D rectangle;
        Vector2 linePosition;
        const Vector2 lineAdvance = Vector2::yAxis(atlas->c[0].ay);
        std::size_t lastLineLastVertex = 0;

        /* Temp buffer so we don't allocate for each new line */
        /**
         * @todo C++1z: use std::string_view to avoid the one allocation and all
         *      the copying altogether
         */
        std::string line;
        line.reserve(text.size());

        /* Render each line separately and align it horizontally */
        std::size_t pos, prevPos = 0;
        do {
            /* Empty line, nothing to do (the rest is done below in while expression) */
            if((pos = text.find('\n', prevPos)) == prevPos) continue;

            /* Copy the line into the temp buffer */
            line.assign(text, prevPos, pos-prevPos);

            /* Layout the line */
            Containers::Pointer<Magnum::Text::AbstractLayouter> layouter = font.layout(cache, size, line);

            /* Verify that we don't reallocate anything. The only problem might
               arise when the layouter decides to compose one character from more
               than one glyph (i.e. accents). Will remove the assert when this
               issue arises. */
            CORRADE_INTERNAL_ASSERT(vertices.size() + layouter->glyphCount()*4 <= vertices.capacity());

            /* Bounds of rendered line */
            Range2D lineRectangle;

            /* Render all glyphs */
            Vector2 cursorPosition(linePosition);
            for(UnsignedInt i = 0; i != layouter->glyphCount(); ++i) {
                Range2D quadPosition, textureCoordinates;
                std::tie(quadPosition, textureCoordinates) = layouter->renderGlyph(i, cursorPosition, lineRectangle);

                /* 0---2
                   |   |
                   |   |
                   |   |
                   1---3 */

                vertices.insert(vertices.end(), {
                        {quadPosition.topLeft(), textureCoordinates.topLeft()},
                        {quadPosition.bottomLeft(), textureCoordinates.bottomLeft()},
                        {quadPosition.topRight(), textureCoordinates.topRight()},
                        {quadPosition.bottomRight(), textureCoordinates.bottomRight()}
                });
            }

            /** @todo What about top-down text? */

            /* Horizontally align the rendered line */
            Float alignmentOffsetX = 0.0f;
            if((UnsignedByte(alignment) & Magnum::Text::Implementation::AlignmentHorizontal) == Magnum::Text::Implementation::AlignmentCenter)
                alignmentOffsetX = -lineRectangle.centerX();
            else if((UnsignedByte(alignment) & Magnum::Text::Implementation::AlignmentHorizontal) == Magnum::Text::Implementation::AlignmentRight)
                alignmentOffsetX = -lineRectangle.right();

            /* Integer alignment */
            if(UnsignedByte(alignment) & Magnum::Text::Implementation::AlignmentIntegral)
                alignmentOffsetX = Math::round(alignmentOffsetX);

            /* Align positions and bounds on current line */
            lineRectangle = lineRectangle.translated(Vector2::xAxis(alignmentOffsetX));
            for(auto it = vertices.begin()+lastLineLastVertex; it != vertices.end(); ++it)
                it->position.x() += alignmentOffsetX;

            /* Add final line bounds to total bounds, similarly to AbstractFont::renderGlyph() */
            if(!rectangle.size().isZero()) {
                rectangle.bottomLeft() = Math::min(rectangle.bottomLeft(), lineRectangle.bottomLeft());
                rectangle.topRight() = Math::max(rectangle.topRight(), lineRectangle.topRight());
            } else rectangle = lineRectangle;

            /* Move to next line */
        } while(prevPos = pos+1,
                linePosition -= lineAdvance,
                lastLineLastVertex = vertices.size(),
                pos != std::string::npos);

        /* Vertically align the rendered text */
        Float alignmentOffsetY = 0.0f;
        if((UnsignedByte(alignment) & Magnum::Text::Implementation::AlignmentVertical) == Magnum::Text::Implementation::AlignmentMiddle)
            alignmentOffsetY = -rectangle.centerY();
        else if((UnsignedByte(alignment) & Magnum::Text::Implementation::AlignmentVertical) == Magnum::Text::Implementation::AlignmentTop)
            alignmentOffsetY = -rectangle.top();

        /* Integer alignment */
        if(UnsignedByte(alignment) & Magnum::Text::Implementation::AlignmentIntegral)
            alignmentOffsetY = Math::round(alignmentOffsetY);

        /* Align positions and bounds */
        rectangle = rectangle.translated(Vector2::yAxis(alignmentOffsetY));
        for(auto& v: vertices) v.position.y() += alignmentOffsetY;

        return std::make_tuple(std::move(vertices), rectangle);
    }

    std::pair<Containers::Array<char>, MeshIndexType> renderIndicesInternal(const UnsignedInt glyphCount) {
        const UnsignedInt vertexCount = glyphCount*4;
        const UnsignedInt indexCount = glyphCount*6;

        Containers::Array<char> indices;
        MeshIndexType indexType;
        if(vertexCount <= 256) {
            indexType = MeshIndexType::UnsignedByte;
            indices = Containers::Array<char>(indexCount*sizeof(UnsignedByte));
            createIndices<UnsignedByte>(indices, glyphCount);
        } else if(vertexCount <= 65536) {
            indexType = MeshIndexType::UnsignedShort;
            indices = Containers::Array<char>(indexCount*sizeof(UnsignedShort));
            createIndices<UnsignedShort>(indices, glyphCount);
        } else {
            indexType = MeshIndexType::UnsignedInt;
            indices = Containers::Array<char>(indexCount*sizeof(UnsignedInt));
            createIndices<UnsignedInt>(indices, glyphCount);
        }

        return {std::move(indices), indexType};
    }

    static std::tuple<std::vector<Vector2>, std::vector<Vector2>, std::vector<UnsignedInt>, Range2D> render(GLIS_FONT & glis_font, const std::string& text, Magnum::Text::Alignment alignment) {
        /* Render vertices */
        std::vector<Vertex> vertices;
        Range2D rectangle;
        std::tie(vertices, rectangle) = renderVerticesInternal(glis_font, text, alignment);

        /* Deinterleave the vertices */
        std::vector<Vector2> positions, textureCoordinates;
        positions.reserve(vertices.size());
        positions.reserve(textureCoordinates.size());
        for(const auto& v: vertices) {
            positions.push_back(v.position);
            textureCoordinates.push_back(v.textureCoordinates);
        }

        /* Render indices */
        const UnsignedInt glyphCount = vertices.size()/4;
        std::vector<UnsignedInt> indices(glyphCount*6);
        createIndices<UnsignedInt>(indices.data(), glyphCount);

        return std::make_tuple(std::move(positions), std::move(textureCoordinates), std::move(indices), rectangle);
    }
};
#endif

Magnum::Color4 from(const GLfloat * color) {
    return {color[0], color[1], color[2], color[3]};
}

void
GLIS_FONT::render_text(const char *text, GLIS_FONT::atlas *a, float x, float y, float sx, float sy,
                       const GLfloat * color) {
    // flip y axis
    float y_ = static_cast<float>(height) - y;
    const uint8_t *p;

    typedef font_init::point point;

    point coords[6 * strlen(text)];
    int c = 0;

    /* Loop through all characters */
    for (p = (const uint8_t *) text; *p; p++) {
        /* Calculate the vertex and texture coordinates */
        float x2 = x + a->c[*p].bl * sx;
        float y2 = -y_ - a->c[*p].bt * sy;
        float w = a->c[*p].bw * sx;
        float h = a->c[*p].bh * sy;

        /* Advance the cursor to the start of the next character */
        x += a->c[*p].ax * sx;
        y += a->c[*p].ay * sy;

        /* Skip glyphs that have no pixels */
        if ((w == 0.0f) || (h == 0.0f))
            continue;

        coords[c++] = (point) {
                x2, -y2, a->c[*p].tx, a->c[*p].ty};
        coords[c++] = (point) {
                x2 + w, -y2, a->c[*p].tx + a->c[*p].bw / a->w, a->c[*p].ty};
        coords[c++] = (point) {
                x2, -y2 - h, a->c[*p].tx, a->c[*p].ty + a->c[*p].bh / a->h};
        coords[c++] = (point) {
                x2 + w, -y2, a->c[*p].tx + a->c[*p].bw / a->w, a->c[*p].ty};
        coords[c++] = (point) {
                x2, -y2 - h, a->c[*p].tx, a->c[*p].ty + a->c[*p].bh / a->h};
        coords[c++] = (point) {
                x2 + w, -y2 - h, a->c[*p].tx + a->c[*p].bw / a->w,
                a->c[*p].ty + a->c[*p].bh / a->h};
    }

    /* Draw all the character on the screen in one go */

    /* Enable blending, necessary for our alpha texture */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader = Magnum::Shaders::FlatGL2D{Magnum::Shaders::FlatGL2D::Flag::Textured};
//    auto shader_ = Magnum::Shaders::FlatGL2D{Magnum::Shaders::FlatGL2D::Flag::Textured};
    Magnum::Shaders::VectorGL2D shader_;

    shader_.setColor(from(
            color != nullptr ? color
                             : current_color != nullptr ? current_color
                                                        : colors.red
    ));

    /* Use the texture containing the atlas */
    //    glBindTexture(GL_TEXTURE_2D, a->tex);
    //    glUniform1i(a->font_source->uniform_tex, 0);
    //    glUniformMatrix4fv(
    //            glGetUniformLocation(a->font_source->program, "projection"),
    //            1,
    //            GL_FALSE,
    //           glm::value_ptr(
    //                   glm::ortho(
    //                           0.0f,
    //                           static_cast<GLfloat>(width),
    //                           0.0f,
    //                                static_cast<GLfloat>(height)
    //                   )
    //           )
    //    );
    //
    //    /* Set up the VBO for our vertex data */
    //    glEnableVertexAttribArray(a->font_source->attribute_coord);
    //    glBindBuffer(GL_ARRAY_BUFFER, a->font_source->vbo);
    //    glVertexAttribPointer(a->font_source->attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);
    shader_.bindVectorTexture(a->texture2D);
    Matrix3 matrix3 = Magnum::Matrix4::orthographicProjection(
            {static_cast<float>(width), static_cast<float>(height)},
            0,
            100
    ).normalMatrix();
    shader_.setTransformationProjectionMatrix(matrix3);

    /* Draw all the character on the screen in one go */
    //    glBufferData(GL_ARRAY_BUFFER, sizeof coords, coords, GL_DYNAMIC_DRAW);
    //    glDrawArrays(GL_TRIANGLES, 0, c);
    //    glDisableVertexAttribArray(a->font_source->attribute_coord);

    Debug{} << "building Buffer...";
    Magnum::GL::Buffer buffer{{coords, 6 * strlen(text)}, Magnum::GL::BufferUsage::DynamicDraw};
    Debug{} << "building mesh...";
    GL::Mesh mesh;
    Debug{} << "setting mesh primitive...";
    mesh.setPrimitive(Magnum::MeshPrimitive::Triangles);
    Debug{} << "adding vertex buffer...";
    mesh.addVertexBuffer(std::move(buffer), 0, Shaders::FlatGL2D::Position{},
                         Shaders::FlatGL2D::TextureCoordinates{});
    Debug{} << "setting count...";
    mesh.setCount(c);
    Debug{} << "built mesh";

    Debug{} << "drawing...";

//    shader_.draw(mesh);
    Debug{} << "drawn";

    /* Configured glyph cache */

    Shaders::VectorGL2D shader;
    GL::Buffer vertexBuffer, indexBuffer;
    GL::Mesh mesh_;



    /* Render the text, centered */
//    std::tie(mesh, std::ignore) = INTERNAL_RENDERER::render(this, text, vertexBuffer, indexBuffer, GL::BufferUsage::StaticDraw, Text::Alignment::LineCenter);


    /* Render vertices and upload them */
    std::vector<Vertex> vertices;
    for(int i = 0; i <= strlen(text); i++) {
        vertices.push_back({{coords[0].x, coords[0].y}, {coords[0].s, coords[0].t}});
    }
    vertexBuffer.setData({vertices.data(), vertices.size()}, GL::BufferUsage::StaticDraw);

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
    shader_.setTransformationProjectionMatrix(matrix3)
            .setColor(0xffffff_rgbf)
            .draw(mesh);

    glDisable(GL_BLEND);
}

void
GLIS_FONT::render_text(const char *text, GLIS_FONT::atlas *a, float x, float y, float sx, float sy)
{
    render_text(text, a, x, y, sx, sy, nullptr);
}

void
GLIS_FONT::render_text(const char *text, const char *font_id, const int font_size, float x, float y,
                       float sx, float sy, const GLfloat * color) {
    ATLAS_TYPE *data = get_atlas(font_id);
    if (data == nullptr) return;
    atlas *a = find_size(font_id, data->fourth.get<font_data *>(), font_size);
    render_text(text, a, x, y, sx, sy, color);
}

void
GLIS_FONT::render_text(const char *text, const char *font_id, const int font_size, float x, float y,
                       float sx, float sy) {
    render_text(text, font_id, font_size, x, y, sx, sy, nullptr);
}

void
GLIS_FONT::render_text(const char *text, GLIS_FONT::atlas *a, float x, float y,
                       const GLfloat * color) {
    render_text(text, a, x, y, 1.0f, 1.0f, color);
}

void
GLIS_FONT::render_text(const char *text, GLIS_FONT::atlas *a, float x, float y) {
    render_text(text, a, x, y, 1.0f, 1.0f, nullptr);
}

void
GLIS_FONT::render_text(const char *text, const char *font_id, const int font_size, float x, float y,
                       const GLfloat * color) {
    render_text(text, font_id, font_size, x, y, 1.0f, 1.0f, color);
}

void
GLIS_FONT::render_text(const char *text, const char *font_id, const int font_size, float x, float y)
{
    render_text(text, font_id, font_size, x, y, 1.0f, 1.0f, nullptr);
}

void
GLIS_FONT::render_text(const char *text, GLIS_FONT::atlas *a, float x, float y, float sxy,
                       const GLfloat * color) {
    render_text(text, a, x, y, sxy, sxy, color);
}

void
GLIS_FONT::render_text(const char *text, GLIS_FONT::atlas *a, float x, float y, float sxy) {
    render_text(text, a, x, y, sxy, sxy, nullptr);
}

void
GLIS_FONT::render_text(const char *text, const char *font_id, const int font_size, float x, float y,
                       float sxy, const GLfloat * color) {
    render_text(text, font_id, font_size, x, y, sxy, sxy, color);
}

void
GLIS_FONT::render_text(const char *text, const char *font_id, const int font_size, float x, float y,
                       float sxy)
{
    render_text(text, font_id, font_size, x, y, sxy, sxy, nullptr);
}

GLIS_FONT::font_init::font_init() {
    std::cout << "font_init default constructor" << std::endl << std::flush;
}

GLIS_FONT::font_init::font_init(const char *path) {
    std::cout << "font_init path constructor" << std::endl << std::flush;
    font_path = const_cast<char *>(path);
    if (!ft_initialized) {
        /* Initialize the FreeType2 library */
        if (FT_Init_FreeType(&ft)) {
            fprintf(stderr, "Could not init freetype library\n");
            ft_initialized = false;
            return;
        }
        ft_initialized = true;
    }
}

GLIS_FONT::font_init::font_init(const Containers::ArrayView<const char> & data) {
    std::cout << "font_init memory constructor" << std::endl << std::flush;
    font_memory_tmp = const_cast<Containers::ArrayView<const char> *>(&data);
    if (!ft_initialized) {
        /* Initialize the FreeType2 library */
        if (FT_Init_FreeType(&ft)) {
            fprintf(stderr, "Could not init freetype library\n");
            ft_initialized = false;
            return;
        }
        ft_initialized = true;
    }
}

GLIS_FONT::font_init::font_init(const GLIS_FONT::font_init &p2) {
    std::cout << "font_init copy constructor" << std::endl << std::flush;
    this->font_path = p2.font_path;
    this->ft_initialized = p2.ft_initialized;
    this->ft = p2.ft;
    this->face = p2.face;
//    this->hasProgram = p2.hasProgram;
//    std::swap(this->v, const_cast<font_init &>(p2).v);
//    std::swap(this->f, const_cast<font_init &>(p2).f);
//    std::swap(this->program, const_cast<font_init &>(p2).program);
//    std::swap(this->uniform_color, const_cast<font_init &>(p2).uniform_color);
//    std::swap(this->uniform_tex, const_cast<font_init &>(p2).uniform_tex);
//    std::swap(this->attribute_coord, const_cast<font_init &>(p2).attribute_coord);
//    std::swap(this->vbo, const_cast<font_init &>(p2).vbo);
}

GLIS_FONT::font_init::font_init(GLIS_FONT::font_init &&p2) {
    std::cout << "font_init move constructor" << std::endl << std::flush;
    std::swap(this->font_path, p2.font_path);
    std::swap(this->ft_initialized, p2.ft_initialized);
    std::swap(this->ft, p2.ft);
    std::swap(this->face, p2.face);
//    std::swap(this->hasProgram, p2.hasProgram);
//    std::swap(this->v, p2.v);
//    std::swap(this->f, p2.f);
//    std::swap(this->program, p2.program);
//    std::swap(this->uniform_color, p2.uniform_color);
//    std::swap(this->uniform_tex, p2.uniform_tex);
//    std::swap(this->attribute_coord, p2.attribute_coord);
//    std::swap(this->vbo, p2.vbo);
}

GLIS_FONT::font_init &GLIS_FONT::font_init::operator=(const GLIS_FONT::font_init &p2) {
    std::cout << "font_init copy assignment" << std::endl << std::flush;
    fflush(stdout);
    this->font_path = p2.font_path;
    this->ft_initialized = p2.ft_initialized;
    this->ft = p2.ft;
    this->face = p2.face;
//    this->hasProgram = p2.hasProgram;
//    std::swap(this->v, const_cast<font_init &>(p2).v);
//    std::swap(this->f, const_cast<font_init &>(p2).f);
//    std::swap(this->program, const_cast<font_init &>(p2).program);
//    std::swap(this->uniform_color, const_cast<font_init &>(p2).uniform_color);
//    std::swap(this->uniform_tex, const_cast<font_init &>(p2).uniform_tex);
//    std::swap(this->attribute_coord, const_cast<font_init &>(p2).attribute_coord);
//    std::swap(this->vbo, const_cast<font_init &>(p2).vbo);
    return *const_cast<font_init *>(this);
}

GLIS_FONT::font_init &GLIS_FONT::font_init::operator=(GLIS_FONT::font_init &&p2) {
    std::cout << "font_init move assignment" << std::endl << std::flush;
    fflush(stdout);
    std::swap(this->font_path, p2.font_path);
    std::swap(this->ft_initialized, p2.ft_initialized);
    std::swap(this->ft, p2.ft);
    std::swap(this->face, p2.face);
//    std::swap(this->hasProgram, p2.hasProgram);
//    std::swap(this->v, p2.v);
//    std::swap(this->f, p2.f);
//    std::swap(this->program, p2.program);
//    std::swap(this->uniform_color, p2.uniform_color);
//    std::swap(this->uniform_tex, p2.uniform_tex);
//    std::swap(this->attribute_coord, p2.attribute_coord);
//    std::swap(this->vbo, p2.vbo);
    return *const_cast<font_init *>(this);
}

GLIS_FONT::font_init::~font_init() {
    std::cout << "font_init destructor" << std::endl << std::flush;
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
//    if (hasProgram) {
//        glDeleteProgram(program);
//        glDeleteShader(f);
//        glDeleteShader(v);
//        hasProgram = false;
//    }
}

bool GLIS_FONT::font_init::load() {
    if (font_memory_tmp != nullptr) {
        /* We need to preserve the data for whole FT_Face lifetime */
        font_memory = Containers::Array<unsigned char>{NoInit, font_memory_tmp->size()};
        Utility::copy(Containers::arrayCast<const unsigned char>(*font_memory_tmp), font_memory);

        if(FT_Error error = FT_New_Memory_Face(ft, font_memory.begin(), font_memory.size(), 0, &face)) {
            fprintf(stderr, "Could not open font: %d\n", error);
            return false;
        }
    } else {
        /* Load a font */
        if (FT_New_Face(ft, font_path, 0, &face)) {
            fprintf(stderr, "Could not open font %s\n", font_path);
            return false;
        }
    }
    return true;
}

void GLIS_FONT::atlas::init(FT_Face face, int height) {
    size = height;
    FT_Set_Pixel_Sizes(face, 0, height);
    FT_GlyphSlot g = face->glyph;

    unsigned int roww = 0;
    unsigned int rowh = 0;
    w = 0;
    h = 0;

    memset(c, 0, sizeof c);

    /* Find minimum size for a texture holding all visible ASCII characters */
    for (int i = 32; i < 128; i++) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            fprintf(stderr, "Loading character %c failed!\n", i);
            continue;
        }
        if (roww + g->bitmap.width + 1 >= MAXWIDTH) {
            w = std::max(w, roww);
            h += rowh;
            roww = 0;
            rowh = 0;
        }
        roww += g->bitmap.width + 1;
        rowh = std::max(rowh, g->bitmap.rows);
    }

    w = std::max(w, roww);
    printf("adding rowh (%d) to h (%d)\n", rowh, h);
    h += rowh;
    printf("added rowh (%d) to h (%d)\n", rowh, h);

    /* Create a texture that will be used to hold all ASCII glyphs */

    texture2D.setStorage(1, Magnum::GL::TextureFormat::RGBA8, {static_cast<int>(w),static_cast<int>(h)});
    texture2D.setWrapping(Magnum::GL::SamplerWrapping::ClampToEdge);
    texture2D.setMagnificationFilter(Magnum::GL::SamplerFilter::Linear);

    /* Paste all glyph bitmaps into the texture, remembering the offset */
    int ox = 0;
    int oy = 0;

    rowh = 0;

    for (int i = 32; i < 128; i++) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            fprintf(stderr, "Loading character %c failed!\n", i);
            continue;
        }

        if (ox + g->bitmap.width + 1 >= MAXWIDTH) {
            oy += rowh;
            rowh = 0;
            ox = 0;
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

        c[i].ax = g->advance.x >> 6;
        c[i].ay = g->advance.y >> 6;

        c[i].bw = g->bitmap.width;
        c[i].bh = g->bitmap.rows;

        c[i].bl = g->bitmap_left;
        c[i].bt = g->bitmap_top;

        c[i].tx = ox / (float) w;
        c[i].ty = oy / (float) h;

        rowh = std::max(rowh, g->bitmap.rows);
        ox += g->bitmap.width + 1;
    }

    fprintf(stderr, "Generated a %d x %d (%d kb) texture atlas\n", w, h, w * h / 1024);
}

void GLIS_FONT::atlas::denit() {
}

GLIS_FONT::atlas::atlas(FT_Face face, int height) {
    init(face, height);
}

GLIS_FONT::atlas::atlas() {
    std::cout << "atlas constructor" << std::endl << std::flush;
}

GLIS_FONT::atlas::atlas(const GLIS_FONT::atlas &p2) {
    std::cout << "atlas copy constructor" << std::endl << std::flush;
    this->size = p2.size;
//    this->tex = p2.tex;
    this->w = p2.w;
    this->h = p2.h;
    this->font_source = p2.font_source;
    for (int i = 0; i != 128; i++) this->c[i] = p2.c[i];
}

GLIS_FONT::atlas::atlas(GLIS_FONT::atlas &&p2) {
    std::cout << "atlas move constructor" << std::endl << std::flush;
    std::swap(this->size, p2.size);
    std::swap(this->texture2D, p2.texture2D);
    std::swap(this->w, p2.w);
    std::swap(this->h, p2.h);
    std::swap(this->font_source, p2.font_source);
    for (int i = 0; i != 128; i++) std::swap(this->c[i], p2.c[i]);
}

GLIS_FONT::atlas &GLIS_FONT::atlas::operator=(const GLIS_FONT::atlas &p2) {
    std::cout << "atlas copy assignment" << std::endl << std::flush;
    this->size = p2.size;
//    this->tex = p2.tex;
    this->w = p2.w;
    this->h = p2.h;
    this->font_source = p2.font_source;
    for (int i = 0; i != 128; i++) this->c[i] = p2.c[i];
    return *const_cast<atlas *>(this);
}

GLIS_FONT::atlas &GLIS_FONT::atlas::operator=(GLIS_FONT::atlas &&p2) {
    std::cout << "atlas move assignment" << std::endl << std::flush;
    std::swap(this->size, p2.size);
    std::swap(this->texture2D, p2.texture2D);
    std::swap(this->w, p2.w);
    std::swap(this->h, p2.h);
    std::swap(this->font_source, p2.font_source);
    for (int i = 0; i != 128; i++) std::swap(this->c[i], p2.c[i]);
    return *const_cast<atlas *>(this);
}

GLIS_FONT::atlas::~atlas() {
    std::cout << "atlas destructor" << std::endl << std::flush;
    denit();
}

GLIS_FONT::font_data::font_data() {
    std::cout << "font_data default constructor" << std::endl << std::flush;
}

GLIS_FONT::font_data::font_data(const Kernel &kernel) {
    std::cout << "font_data kernel constructor" << std::endl << std::flush;
    sizes = kernel;
}

GLIS_FONT::font_data::font_data(const GLIS_FONT::font_data &p2) {
    std::cout << "font_data copy constructor" << std::endl << std::flush;
    this->sizes = p2.sizes;
}

GLIS_FONT::font_data::font_data(GLIS_FONT::font_data &&p2) {
    std::cout << "font_data move constructor" << std::endl << std::flush;
    std::swap(this->sizes, p2.sizes);
}

GLIS_FONT::font_data &GLIS_FONT::font_data::operator=(const GLIS_FONT::font_data &p2) {
    std::cout << "font_data copy assignment" << std::endl << std::flush;
    this->sizes = p2.sizes;
    return *const_cast<font_data *>(this);
}

GLIS_FONT::font_data &GLIS_FONT::font_data::operator=(GLIS_FONT::font_data &&p2) {
    std::cout << "font_data move assignment" << std::endl << std::flush;
    std::swap(this->sizes, p2.sizes);
    return *const_cast<font_data *>(this);
}

GLIS_FONT::font_data::~font_data() {
    std::cout << "font_data destructor" << std::endl << std::flush;
}
