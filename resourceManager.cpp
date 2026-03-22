#include <iostream>

#include <fontconfig/fontconfig.h>
#include <lunasvg.h>

#include "config.h"
#include "def.h"
#include "icons.h"
#include "resourceManager.h"
#include "screen.h"
#include "sdlutils.h"
#include <SDL2_rotozoom.h>

namespace {

std::string replaceCurrentColor(const std::string &svg, const std::string &color) {
    std::string result = svg;
    std::string search = "currentColor";
    size_t pos = 0;
    while ((pos = result.find(search, pos)) != std::string::npos) {
        result.replace(pos, search.length(), color);
        pos += color.length();
    }
    return result;
}

SDLSurfaceUniquePtr LoadSvgIcon(const char *svg_data, const std::string &color) {
    std::string modified_svg = replaceCurrentColor(svg_data, color);
    auto document = lunasvg::Document::loadFromData(modified_svg);
    if (!document) {
        std::cerr << "LoadSvgIcon: failed to parse SVG" << std::endl;
        return nullptr;
    }

    int w = 24 * screen.ppu_x / 2;
    int h = 24 * screen.ppu_y / 2;
    auto bitmap = document->renderToBitmap(w, h);
    if (bitmap.isNull()) {
        std::cerr << "LoadSvgIcon: failed to render SVG" << std::endl;
        return nullptr;
    }

    bitmap.convertToRGBA();
    SDL_Surface *surf = SDL_CreateRGBSurface(0, w, h, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
    if (!surf) {
        std::cerr << "LoadSvgIcon: SDL_CreateRGBSurface failed" << std::endl;
        return nullptr;
    }

    SDL_memcpy(surf->pixels, bitmap.data(), w * h * 4);
    return SDLSurfaceUniquePtr { surf };
}

std::string ResDir = RES_DIR "";

std::string ResPath(const char *path) { return ResDir + path; }
std::string ResPath(const std::string &path) { return ResDir + path; }

std::string ResolveFontPath(const std::string &family) {
    FcPattern *pattern = FcPatternCreate();
    if (!pattern) return { };

    FcPatternAddString(pattern, FC_FAMILY, reinterpret_cast<const FcChar8 *>(family.c_str()));

    FcConfigSubstitute(nullptr, pattern, FcMatchPattern);
    FcDefaultSubstitute(pattern);

    FcResult result;
    FcPattern *match = FcFontMatch(nullptr, pattern, &result);
    FcPatternDestroy(pattern);

    if (!match) return { };

    FcChar8 *filename = nullptr;
    FcPatternGetString(match, FC_FILE, 0, &filename);
    std::string path = reinterpret_cast<const char *>(filename);
    FcPatternDestroy(match);

    return path;
}

std::vector<TTF_Font *> LoadFonts() {
    std::vector<TTF_Font *> fonts;

    const int primary_size = static_cast<int>(FONT_PRIMARY_SIZE * screen.ppu_y + 0.5f);
    const int fallback_size = static_cast<int>(FONT_FALLBACK_SIZE * screen.ppu_y + 0.5f);

    const std::string &primary = config().font_primary;
    if (!primary.empty()) {
        std::string path = ResolveFontPath(primary);
        if (!path.empty()) {
            auto *font = SDL_utils::loadFont(path, primary_size);
            if (font) fonts.push_back(font);
        }
        if (fonts.empty()) {
            std::cerr << "Failed to load primary font: " << primary << std::endl;
        }
    }

    const std::string &fallback = config().font_fallback;
    if (!fallback.empty()) {
        std::string path = ResolveFontPath(fallback);
        if (!path.empty()) {
            auto *font = SDL_utils::loadFont(path, fallback_size);
            if (font) fonts.push_back(font);
        } else {
            std::cerr << "Failed to resolve fallback font: " << fallback << std::endl;
        }
    }

    if (fonts.empty()) {
        std::cerr << "No fonts found!" << std::endl;
        exit(1);
    }
    return fonts;
}

} // namespace

void CResourceManager::SetResDir(const char *res_dir)
{
    ResDir = res_dir;
    if (!ResDir.empty() && ResDir.back() != '/') ResDir += '/';
    std::fprintf(stderr, "Set resource directory to %s\n", ResDir.c_str());
}

CResourceManager& CResourceManager::instance()
{
    static CResourceManager l_singleton;
    return l_singleton;
}

CResourceManager::CResourceManager()
    : m_fonts({})
    , m_ppu_x(0)
    , m_ppu_y(0)
{
    onResize();
}

void CResourceManager::onResize()
{
    if (screen.ppu_x != m_ppu_x || screen.ppu_y != m_ppu_y) {
        std::string iconColor = config().icon_color;
        m_surfaces[T_SURFACE_FOLDER] = LoadSvgIcon(Icons::ICON_FOLDER, iconColor);
        m_surfaces[T_SURFACE_FOLDER_SYMLINK] = LoadSvgIcon(Icons::ICON_FOLDER_SYMLINK, iconColor);
        m_surfaces[T_SURFACE_FILE] = LoadSvgIcon(Icons::ICON_FILE_GENERIC, iconColor);
        m_surfaces[T_SURFACE_FILE_SYMLINK] = LoadSvgIcon(Icons::ICON_FILE_SYMLINK, iconColor);
        m_surfaces[T_SURFACE_FILE_IMAGE] = LoadSvgIcon(Icons::ICON_FILE_IMAGE, iconColor);
        m_surfaces[T_SURFACE_UP] = LoadSvgIcon(Icons::ICON_UP, iconColor);
    }

    m_surfaces[T_SURFACE_CURSOR1] = SDLSurfaceUniquePtr {
        SDL_utils::createImage(screen.actual_w / 2, LINE_HEIGHT_PHYS,
            SDL_MapRGB(screen.surface->format, COLOR_CURSOR_1))
    };
    m_surfaces[T_SURFACE_CURSOR2] = SDLSurfaceUniquePtr {
        SDL_utils::createImage(screen.actual_w / 2, LINE_HEIGHT_PHYS,
            SDL_MapRGB(screen.surface->format, COLOR_CURSOR_2))
    };

    if (screen.ppu_x != m_ppu_x || screen.ppu_y != m_ppu_y) {
        closeFonts();
        m_fonts = Fonts { LoadFonts() };
    }
    m_ppu_x = screen.ppu_x;
    m_ppu_y = screen.ppu_y;
}

void CResourceManager::sdlCleanup() {
    for (auto &surface : m_surfaces) surface = nullptr;
    closeFonts();
    FcFini();
}

void CResourceManager::closeFonts() {
    for (auto &font : m_fonts.fonts()) {
        if (font != nullptr) {
            TTF_CloseFont(font);
            font = nullptr;
        }
    }
}

SDL_Surface *CResourceManager::getSurface(const T_SURFACE p_surface) const
{
    return m_surfaces[p_surface].get();
}

const Fonts &CResourceManager::getFonts() const
{
    return m_fonts;
}
