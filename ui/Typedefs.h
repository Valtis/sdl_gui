
#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

namespace sdl_gui {

typedef std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture_ptr;
typedef std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface_ptr;

}

#endif
