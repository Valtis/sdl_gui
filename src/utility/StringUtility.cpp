#include "StringUtility.h"
#include <cstring>
#include <iostream>
#include "../rendering/Renderer.h"

namespace sdl_gui {
namespace utility {

std::vector<std::string> tokenize(const std::string &text, const char delimiter)
{
	std::vector<std::string> tokens;

	if (text.empty())
	{
		return tokens;
	}

	int begin_pos = 0;
	int end_pos = 0;

	while ((end_pos = text.find(delimiter, begin_pos)) != std::string::npos) {
		std::string token = text.substr(begin_pos, end_pos - begin_pos);

		if (!token.empty()) {
			tokens.push_back(token);
		}
		begin_pos = end_pos+1;
	}

	if (begin_pos != std::string::npos) {
		tokens.push_back(text.substr(begin_pos));
	}

	return tokens;
}


std::vector<std::string> do_wrap(const std::string &text, const int font_size, rendering::Renderer *renderer, const int max_width);

std::vector<std::string> wrap_text(const std::string &text, const int font_size, rendering::Renderer *renderer, const SDL_Rect &text_box_size, const std::pair<int, int> offsets_from_sides) {
	int width = 0;
	renderer->text_width_and_height(text, font_size, &width, nullptr);

	const int max_width = text_box_size.w - offsets_from_sides.first - offsets_from_sides.second;
	if (width <= max_width || text.empty()) {
		return std::vector<std::string>{text};
	}

   return do_wrap(text, font_size, renderer, max_width);
}


std::vector<std::string> do_wrap(const std::string &text, const int font_size, rendering::Renderer *renderer, const int max_width) {

	const char delimiter = ' ';
	std::vector<std::string> tokens = tokenize(text, delimiter);
	std::vector<std::string> wrapped_lines;


	std::string wrapped_text = tokens[0];

	for (int i = 1; i < tokens.size(); ++i) {
		int width = 0;
		std::string new_string = wrapped_text + delimiter + tokens[i];
		renderer->text_width_and_height(new_string, font_size, &width, nullptr);

		if (width <= max_width) {
			wrapped_text = new_string;
		} else {
			wrapped_lines.push_back(wrapped_text);
			wrapped_text = tokens[i];
		}
	}

	if (!wrapped_text.empty()) {
		wrapped_lines.push_back(wrapped_text);
	}

	return wrapped_lines;
}

} /* namespace utility */
} /* namespace sdl_gui */
