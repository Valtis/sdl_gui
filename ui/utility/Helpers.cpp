/*
 * Helpers.cpp
 *
 *  Created on: 8.7.2014
 *      Author: valtis
 */

#include "Helpers.h"

namespace sdl_gui {
namespace utility {

bool point_inside_rect(SDL_Point p, SDL_Rect r) {
	return p.x > r.x && p.x < r.x + r.w && p.y > r.y && p.y < r.y + r.h;
}

} /* namespace utility */

} /* namespace sdl_gui */
