//
// Created by Matthew Good on 25/6/21.
//

#include "TextureHelpers.h"
#include <Magnum/GL/TextureFormat.h>

void TextureHelpers::release() {
    delete framebuffer_;
    framebuffer_ = nullptr;
    delete image_;
    image_ = nullptr;
    delete data_;
    data_ = nullptr;
    delete texture2DRead;
    texture2DRead = nullptr;
    delete texture2DDraw;
    texture2DDraw = nullptr;
    delete shaderRead;
    shaderRead = nullptr;
    delete shaderReadTexture;
    shaderReadTexture = nullptr;
    delete shaderDraw;
    shaderDraw = nullptr;
}

void TextureHelpers::newTexture2D(const Magnum::VectorTypeFor<2, int> &size) {
    delete texture2DDraw;
    texture2DDraw = new TextureHelpersTexture2D;
    texture2DDraw->setStorage(1, Magnum::GL::TextureFormat::RGBA8, size);
}

void TextureHelpers::newFramebuffer(const Magnum::VectorTypeFor<2, int> &size) {
    width = size[0];
    height = size[1];
    if (framebuffer_ == nullptr) framebuffer_ = new TextureHelpersFramebuffer {{{}, size}};
    framebuffer_->setViewport({{}, size});
    newTexture2D(size);
    framebuffer_->attachTexture(Magnum::GL::Framebuffer::ColorAttachment{0}, *texture2DDraw, 0);
    framebuffer_->mapForDraw({{0, {Magnum::GL::Framebuffer::ColorAttachment{0}}}});
}

void TextureHelpers::resize(const Magnum::VectorTypeFor<2, int> &size) {
    if (framebuffer_ != nullptr) {
        newFramebuffer(size);
    } else {
        width = size[0];
        height = size[1];
        Magnum::GL::defaultFramebuffer.setViewport({{}, size});
    }
}

void TextureHelpers::resize(const Magnum::VectorTypeFor<2, int> &size1,
                          const Magnum::VectorTypeFor<2, int> &size2) {
    width = size2[0];
    height = size2[1];
    Magnum::GL::defaultFramebuffer.setViewport({size1, size2});
}

void TextureHelpers::genTextureFromGLTexture(const GLuint &id) {
    if (texture2DDraw != nullptr) delete texture2DDraw;
    texture2DDraw = new Magnum::GL::Texture2D;
    *texture2DDraw = Magnum::GL::Texture2D::wrap(id);
}

void TextureHelpers::bindFramebuffer() {
    framebuffer_ != nullptr ? framebuffer_->bind() : Magnum::GL::defaultFramebuffer.bind();
}

void TextureHelpers::clearFramebuffer() {
    if (framebuffer_ != nullptr) framebuffer_->clear(Magnum::GL::FramebufferClear::Color);
    else Magnum::GL::defaultFramebuffer.clear(Magnum::GL::FramebufferClear::Color);
}

void TextureHelpers::bindFramebufferAndClearFramebuffer() {
    bindFramebuffer();
    clearFramebuffer();
}

Magnum::Range2Di TextureHelpers::getViewport() {
    return framebuffer_ != nullptr ? framebuffer_->viewport() : Magnum::GL::defaultFramebuffer.viewport();
}

TextureHelpersShader *TextureHelpers::newShaderReadTexture() {
    if (shaderReadTexture == nullptr) shaderReadTexture = new TextureHelpersShader(Magnum::Shaders::FlatGL2D::Flag::Textured);
    return shaderReadTexture;
}

TextureHelpersShader *TextureHelpers::newShaderRead() {
    if (shaderRead == nullptr) shaderRead = new TextureHelpersShader;
    return shaderRead;
}

void TextureHelpers::draw(TextureHelpersShader *shader, const TextureHelpersColor &color,
                        Magnum::GL::Mesh &&mesh) {
    if (texture2DRead != nullptr) shader->bindTexture(*texture2DRead);
    shader
            ->setColor(color)
            .draw(mesh);
}