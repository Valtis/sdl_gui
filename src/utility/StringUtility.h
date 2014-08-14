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
	// deletes n character from the position; so characters position - n -> position are erased
	std::string erase_from_before_position_utf8(const std::string &text, const int erasable_char_count, const int position);

	int glyph_count_utf8(const std::string &text);
	std::string add_text_to_position_utf8(const std::string &original, const std::string &new_text, const int position);


} /* namespace utility */
} /* namespace sdl_gui*/

#endif /* STRINGUTILITY_H_ */
