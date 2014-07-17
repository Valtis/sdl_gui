
#ifndef HELPERS_H_
#define HELPERS_H_
#include <SDL2/SDL.h>

namespace sdl_gui {

namespace utility {

bool point_inside_rect(SDL_Point p, SDL_Rect r);
void clip_draw_rectangles(const SDL_Rect &draw_area, SDL_Rect &source_rect, SDL_Rect &destination_rect);

} /* namespace utility */
} /* namespace sdl_gui */

#endif /* HELPERS_H_ */
