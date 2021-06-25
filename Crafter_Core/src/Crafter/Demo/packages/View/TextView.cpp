//
// Created by Matthew Good on 25/6/21.
//

#include "TextView.h"
#include "GLIS_FONT.cpp"
#include <Corrade/Utility/Resource.h>

void TextView::init() {
    View::init();
}

void TextView::onDraw() {
    View::onDraw();

    GLIS_FONT font;

    GLIS_FONT::ATLAS_TYPE * quad_cache = nullptr;
    GLIS_FONT::font_init * fontInit_cache = nullptr;
    GLIS_FONT::font_data * fontData_cache = nullptr;
    GLIS_FONT::atlas * a12_cache = nullptr;
    GLIS_FONT::atlas * a24_cache = nullptr;
    GLIS_FONT::atlas * a48_cache = nullptr;

    font.set_max_width_height(400, 400);
    quad_cache = font.add_font("id", Corrade::Utility::Resource{"MagnumUi"}.getRaw("SourceSansPro-Regular.ttf"));
    a12_cache = font.add_font_size("id", 12);
    a24_cache = font.add_font_size("id", 24);
    a48_cache = font.add_font_size("id", 48);

    // initialize cache
    if (quad_cache == nullptr) quad_cache = font.get_atlas("id");
    if (fontInit_cache == nullptr) fontInit_cache = quad_cache->third.get<GLIS_FONT::font_init*>();
    if (fontData_cache == nullptr) fontData_cache = quad_cache->fourth.get<GLIS_FONT::font_data*>();
    if (a12_cache == nullptr) a12_cache = font.find_size("id", fontData_cache, 12);
    if (a24_cache == nullptr) a24_cache = font.find_size("id", fontData_cache, 24);
    if (a48_cache == nullptr) a48_cache = font.find_size("id", fontData_cache, 48);
    // cache initialized

    /* Set color to black */
    font.set_color(font.colors.red);

    /* Effects of alignment */
    font.render_text("The Quick Brown Fox Jumps Over The Lazy Dog", a48_cache, 8, 50);
//    font.render_text("The Misaligned Fox Jumps Over The Lazy Dog", a48_cache, 8.5, 100.5);
//
//    /* Scaling the texture versus changing the font size */
//    font.render_text("The Small Texture Scaled Fox Jumps Over The Lazy Dog", a48_cache, 8, 175, 0.5f, 0.5f);
//    font.render_text("The Small Font Sized Fox Jumps Over The Lazy Dog", a24_cache, 8, 200);
//    font.render_text("The Tiny Texture Scaled Fox Jumps Over The Lazy Dog", a48_cache, 8, 235, 0.25, 0.25);
//    font.render_text("The Tiny Font Sized Fox Jumps Over The Lazy Dog", a12_cache, 8, 250);
//
//    /* Colors and transparency */
//    font.render_text("The Solid Black Fox Jumps Over The Lazy Dog", a48_cache, 8, 430);
//
//    font.set_color(font.colors.red);
//    font.render_text("The Solid Red Fox Jumps Over The Lazy Dog", a48_cache, 8, 330);
//    font.render_text("The Solid Red Fox Jumps Over The Lazy Dog", a48_cache, 28, 450);
//
//    font.set_color(font.colors.transparent_green);
//    font.render_text("The Transparent Green Fox Jumps Over The Lazy Dog", a48_cache, 0, 380);
//    font.render_text("The Transparent Green Fox Jumps Over The Lazy Dog", a48_cache, 18, 440);
}

void TextView::setText(const std::string &string) {}

void TextView::setTextSize(const int &size) {}
