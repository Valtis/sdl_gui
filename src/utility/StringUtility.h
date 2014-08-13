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

    // if include_delimiters is true, delimiters are added as separate strings to return vector
	std::vector<std::string> tokenize(const std::string &text, const char delimiter, bool include_delimiters=false);
	std::vector<std::string> wrap_text(const std::string &text, const int font_size, rendering::Renderer *renderer, const SDL_Rect &text_box_size, const std::pair<int, int> offsets_from_sides);

	// TODO: replace with unicode library that handles this for us...
	std::string substring_utf8(const std::string &text, const unsigned int  pos, const unsigned int length);
	std::string erase_from_end_utf8(const std::string &text, const int erasable_char_count);
	int glyph_count_utf8(const std::string &text);

} /* namespace utility */
} /* namespace sdl_gui*/

#endif /* STRINGUTILITY_H_ */
