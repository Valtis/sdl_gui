#ifndef STRINGUTILITY_H_
#define STRINGUTILITY_H_

#include <SDL2/SDL.h>
#include <vector>
#include <string>

namespace sdl_gui {

namespace rendering {
	class Renderer;
}

namespace utility {

	std::vector<std::string> tokenize(const std::string &text, const char delimiter);
	std::vector<std::string> wrap_text(const std::string &text, const int font_size, rendering::Renderer *renderer, const SDL_Rect &text_box_size, const std::pair<int, int> offsets_from_sides);

} /* namespace utility */
} /* namespace sdl_gui*/

#endif /* STRINGUTILITY_H_ */
