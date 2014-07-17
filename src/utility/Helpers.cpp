#include "Helpers.h"
#include <algorithm>

namespace sdl_gui {
namespace utility {

bool point_inside_rect(SDL_Point p, SDL_Rect r) {
	return p.x > r.x && p.x < r.x + r.w && p.y > r.y && p.y < r.y + r.h;
}

void clip_draw_rectangles(const SDL_Rect &draw_area, SDL_Rect &source_rect, SDL_Rect &destination_rect) {


	int top_side_clipping = draw_area.y - destination_rect.y;
	int left_side_clipping = draw_area.x - destination_rect.x;
	int right_side_clipping = destination_rect.x + destination_rect.w - draw_area.x - draw_area.w;
	int bot_side_clipping = destination_rect.y + destination_rect.h - draw_area.y - draw_area.h;

	source_rect.x = std::min(source_rect.w, std::max(source_rect.x, source_rect.x + left_side_clipping));
	source_rect.y = std::min(source_rect.h, std::max(source_rect.y, source_rect.y + top_side_clipping));
	source_rect.w = std::max(0, std::min(source_rect.w, source_rect.w - right_side_clipping - std::max(0, left_side_clipping)));
	source_rect.h = std::max(0, std::min(source_rect.h, source_rect.h - bot_side_clipping - std::max(0, top_side_clipping)));

	SDL_IntersectRect(&draw_area, &destination_rect, &destination_rect);

}

} /* namespace utility */

} /* namespace sdl_gui */
