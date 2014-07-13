#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace sdl_gui {

typedef std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture_ptr;
typedef std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface_ptr;
typedef std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font_ptr;

}

#endif
