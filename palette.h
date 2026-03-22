#ifndef PALETTE_H_
#define PALETTE_H_

#include <SDL.h>
#include <cstdint>
#include <string>

struct RGB : SDL_Color {
    RGB() : SDL_Color{0, 0, 0, 0} {}
    RGB(Uint8 r_, Uint8 g_, Uint8 b_) : SDL_Color{r_, g_, b_, 0} {}
    void invert() { r = 255 - r; g = 255 - g; b = 255 - b; }
};

inline Uint32 toPixel(const SDL_PixelFormat* f, const RGB& c) {
    return SDL_MapRGB(f, c.r, c.g, c.b);
}

struct Palette {
    RGB panel;
    RGB text_body;
    RGB text_header;
    RGB highlight;
    RGB bg_selection;
    RGB bg_selection_alt;
    RGB bg_normal;
    RGB bg_alternate;
    RGB icon_dir;
    RGB icon_file;

    void init(bool dark);
};

extern Palette g_palette;

#endif
