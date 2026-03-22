#include "palette.h"

void Palette::init(bool dark) {
    panel = {102, 85, 74};
    text_body = {70, 27, 10};
    text_header = {233, 229, 227};
    highlight = {255, 0, 0};
    bg_selection = {232, 152, 80};
    bg_selection_alt = {232, 201, 173};
    bg_normal = {255, 255, 255};
    bg_alternate = {232, 228, 224};
    icon_dir = {75, 70, 164};
    icon_file = {100, 100, 100};

    if (dark) {
        panel.invert();
        text_body.invert();
        text_header.invert();
        highlight.invert();
        bg_selection.invert();
        bg_selection_alt.invert();
        bg_normal.invert();
        bg_alternate.invert();
        icon_dir.invert();
        icon_file.invert();
    }
}

Palette g_palette;
