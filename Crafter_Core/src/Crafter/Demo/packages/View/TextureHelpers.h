//
// Created by Matthew Good on 25/6/21.
//

#ifndef CRAFTER_TEXTUREHELPERS_H
#define CRAFTER_TEXTUREHELPERS_H

#include <Magnum/GL/Framebuffer.h>
#include <Magnum/ImageView.h>
#include <Magnum/PixelFormat.h>
#include <Magnum/Shaders/FlatGL.h>
#include <Magnum/Math/Color.h>

typedef Magnum::GL::Framebuffer TextureHelpersFramebuffer;
typedef Magnum::ImageView2D TextureHelpersImageView2D;
typedef Corrade::Containers::ArrayView<const void> TextureHelpersImageData;
typedef Magnum::GL::Texture2D TextureHelpersTexture2D;
typedef Magnum::Shaders::FlatGL2D TextureHelpersShader;
typedef Magnum::Color4 TextureHelpersColor;

class TextureHelpers {
public:
    TextureHelpersFramebuffer * framebuffer_ = nullptr;
    TextureHelpersImageView2D * image_ = nullptr;
    TextureHelpersImageData * data_ = nullptr;
    TextureHelpersTexture2D * texture2DRead = nullptr;
    TextureHelpersTexture2D * texture2DDraw = nullptr;
    TextureHelpersShader * shaderRead = nullptr;
    TextureHelpersShader * shaderReadTexture = nullptr;
    TextureHelpersShader * shaderDraw = nullptr;

    TextureHelpersShader * newShaderReadTexture();

    TextureHelpersShader * newShaderRead();

    int width = 0;
    int height = 0;

    void release();

    void newTexture2D(const Magnum::VectorTypeFor<2, int> & size);

    void newFramebuffer(const Magnum::VectorTypeFor<2, int> & size);

    void resize(const Magnum::VectorTypeFor<2, int> & size);

    void resize(const Magnum::VectorTypeFor<2, int> & size1, const Magnum::VectorTypeFor<2, int> & size2);

    template <typename T> void setTextureData(const T * data, int texture_width, int texture_height) {

        newTexture2D({texture_width, texture_height});

        texture2DDraw->setSubImage(
                0,
                {},
                std::move(
                        Magnum::ImageView2D(
                                Magnum::PixelFormat::RGBA8Unorm,
                                {texture_width, texture_height},
                                std::move(
                                        Corrade::Containers::ArrayView<const T> (
                                                data,
                                                texture_width*texture_height
                                        )
                                )
                        )

                )
        ).generateMipmap();
    }

    void genTextureFromGLTexture(const GLuint & id);

    void bindFramebuffer();

    void clearFramebuffer();

    void bindFramebufferAndClearFramebuffer();

    void draw(TextureHelpersShader * shader, const TextureHelpersColor & color, Magnum::GL::Mesh && mesh);

    Range2Di getViewport();
};


#endif //CRAFTER_TEXTUREHELPERS_H
