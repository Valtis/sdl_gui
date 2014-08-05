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


std::vector<std::string> do_wrap(const std::string &text, const int font_size, rendering::Renderer *renderer,  int max_width);
bool splitting_word_from_middle(int i, const std::string &text);
void handle_wrap_from_middle_of_word(int &i, const std::string &text, std::string &wrapped_text, std::vector<std::string> &wrapped_lines);
void handle_single_word_wrap(int &i, const std::string &text, std::string &wrapped_text, std::vector<std::string> &wrapepd_lines);
void handle_multi_word_wrap(int &i, const std::string &text, std::string &wrapped_text, std::vector<std::string> &wrapepd_lines, const size_t whitespace_pos);

std::vector<std::string> wrap_text(const std::string &text, const int font_size, rendering::Renderer *renderer, const SDL_Rect &text_box_size, const std::pair<int, int> offsets_from_sides) {
	int width = 0;
	renderer->text_width_and_height(text, font_size, &width, nullptr);

	const int max_width = text_box_size.w - offsets_from_sides.first - offsets_from_sides.second;
	if (width <= max_width) {
		return std::vector<std::string>{text};
	}

   return do_wrap(text, font_size, renderer, max_width);
}


std::vector<std::string> do_wrap(const std::string &text, const int font_size, rendering::Renderer *renderer,  int max_width) {
	std::vector<std::string> wrapped_lines;
	std::string wrapped_text = "";
	int width = 0;

	for (int i = 0; i < text.length(); ++i) {

		renderer->text_width_and_height(wrapped_text + text[i], font_size, &width, nullptr);

		if (width <= max_width) {
			wrapped_text += text[i];
		} else {
			if (splitting_word_from_middle(i, text)) {
				handle_wrap_from_middle_of_word(i, text, wrapped_text, wrapped_lines);
			} else {
				wrapped_lines.push_back(wrapped_text);
				wrapped_text = text[i];
			}
		}
	}

	if (!wrapped_text.empty()) {
		wrapped_lines.push_back(wrapped_text);
	}

	return wrapped_lines;
}


bool splitting_word_from_middle(int i, const std::string &text) {
	return i < text.length() && i > 0 && text[i-1] != ' ' && text[i] != ' ';
}

void handle_wrap_from_middle_of_word(int &i, const std::string &text, std::string &wrapped_text, std::vector<std::string> &wrapped_lines) {
	auto whitespace_pos = wrapped_text.find_last_of(' ');
	// if no whitespace is found, it must be a single large word instead of just being inside a word when requiring a wrap; in this case we do not wrap anything
	if (whitespace_pos == std::string::npos) {
		handle_single_word_wrap(i, text, wrapped_text, wrapped_lines);
	} else {
		// white space was found; multiple words in wrapped_text
		handle_multi_word_wrap(i, text, wrapped_text, wrapped_lines, whitespace_pos);
	}
}

void handle_single_word_wrap(int &i, const std::string &text, std::string &wrapped_text, std::vector<std::string> &wrapped_lines) {
	// find next whitespace, add the large word as a single line to vector and continue
	auto endpos = text.find(' ', i);
	int startpos = i;

	// add rest of the word into wrapped_text
	wrapped_text += text.substr(std::max(0, startpos), endpos - startpos);
	wrapped_lines.push_back(wrapped_text);
	wrapped_text = "";

	// next cycle adds +1 to i; substract 1 so that character at position text[endpos] is handled as well
	i = endpos-1;
}

void handle_multi_word_wrap(int &i, const std::string &text, std::string &wrapped_text, std::vector<std::string> &wrapped_lines, const size_t whitespace_pos) {
	wrapped_lines.push_back(wrapped_text.substr(0, whitespace_pos+1));
	wrapped_text = wrapped_text.substr(whitespace_pos+1) + text[i];
}


} /* namespace utility */
} /* namespace sdl_gui */
