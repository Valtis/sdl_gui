
#ifndef HELPERS_H_
#define HELPERS_H_
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <utility>

namespace sdl_gui {

namespace rendering {
	class Renderer;
}

namespace utility {

bool point_inside_rect(SDL_Point p, SDL_Rect r);
void clip_draw_rectangles(const SDL_Rect &draw_area, SDL_Rect &source_rect, SDL_Rect &destination_rect);
SDL_Color lighter_color(const SDL_Color &color, double amount);
SDL_Color darker_color(const SDL_Color &color, double amount);
std::vector<std::string> wrap_text(const std::string &text, const int font_size, rendering::Renderer *renderer, const SDL_Rect &text_box_size, const std::pair<int, int> offsets_from_sides);

} /* namespace utility */
} /* namespace sdl_gui */

#endif /* HELPERS_H_ */
