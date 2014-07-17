#ifndef SURFACEOPERATIONS_H_
#define SURFACEOPERATIONS_H_
#include <SDL2/SDL.h>
namespace sdl_gui {

namespace creation {
Uint8 get_alpha(SDL_Surface *surface, int x, int y);
Uint8 get_red(SDL_Surface *surface, int x, int y);
Uint8 get_green(SDL_Surface *surface, int x, int y);
Uint8 get_blue(SDL_Surface *surface, int x, int y);

void set_alpha(SDL_Surface *surface, int x, int y, Uint32 color);
void set_red(SDL_Surface *surface, int x, int y, Uint32 _color);
void set_green(SDL_Surface *surface, int x, int y, Uint32 color);
void set_blue(SDL_Surface *surface, int x, int y, Uint32 _color);
void set_color(SDL_Surface *surface, int x, int y, SDL_Color color);

void fill_surface_with_color(SDL_Surface *surface, const SDL_Color &color);

} /* namespace creation */
} /* namespace sdl_gui */

#endif /* SURFACEOPERATIONS_H_ */
