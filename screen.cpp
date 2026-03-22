#include "screen.h"

#include <algorithm>
#include <cstdint>
#include <cstdio>

#include "sdlutils.h"

Screen screen;

namespace {

void MaybeHeuristicAutoscale(const Config &cfg, int best_w, int best_h)
{
    if (!cfg.disp_autoscale) return;
    if (screen.actual_w == best_w && screen.actual_h == best_h) return;

    if (best_w >= screen.w * 2) {
        // E.g. 640x480. Upscale to the smaller of the two.
        const float scale = std::min(best_w / static_cast<float>(screen.w),
            best_h / static_cast<float>(screen.h));
        screen.ppu_x = screen.ppu_y = scale;
    } else {
        // E.g. RS07 with 480x272 screen.
        screen.ppu_x = screen.ppu_y = 1;
    }
}

} // namespace

int Screen::init()
{
    const auto &cfg = config();
    screen.w = cfg.disp_width;
    screen.h = cfg.disp_height;
    screen.ppu_x = cfg.disp_ppu_x;
    screen.ppu_y = cfg.disp_ppu_y;
    screen.actual_w = cfg.disp_width * cfg.disp_ppu_x;
    screen.actual_h = cfg.disp_height * cfg.disp_ppu_y;

    int window_flags = 0;
    if (cfg.disp_windowed) {
        window_flags |= SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED;
    } else {
        window_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    int window_w = screen.actual_w;
    int window_h = screen.actual_h;
    window = SDL_CreateWindow("Commander", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, window_w, window_h, window_flags);
    if (window == nullptr) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return 1;
    }
    SDL_GetWindowSize(window, &window_w, &window_h);
    if (cfg.disp_autoscale) {
        MaybeHeuristicAutoscale(cfg, window_w, window_h);
    }
    setPhysicalResolution(window_w, window_h);

    screen.surface = SDL_GetWindowSurface(window);
    if (screen.surface == nullptr) {
        SDL_Log("SDL_GetWindowSurface failed: %s", SDL_GetError());
    }
    return 0;
}

int Screen::onResize(int w, int h)
{
    this->surface = SDL_GetWindowSurface(this->window);
    setPhysicalResolution(surface->w, surface->h);
    return 0;
}

void Screen::setPhysicalResolution(int actual_w, int actual_h)
{
    this->actual_w = actual_w;
    this->actual_h = actual_h;
    this->w = static_cast<int>(actual_w / ppu_x);
    this->h = static_cast<int>(actual_h / ppu_y);
}

void Screen::zoom(float factor) {
    ppu_x *= factor;
    ppu_y *= factor;
    this->w = static_cast<int>(actual_w / ppu_x);
    this->h = static_cast<int>(actual_h / ppu_y);
}
