#include "Helpers.h"
#include <algorithm>
#include "../rendering/Renderer.h"

namespace sdl_gui {
namespace utility {

bool point_inside_rect(SDL_Point p, SDL_Rect r) {
	return p.x >= r.x && p.x <= r.x + r.w && p.y >= r.y && p.y <= r.y + r.h;
}

void clip_draw_rectangles(const SDL_Rect &draw_area, SDL_Rect &source_rect, SDL_Rect &destination_rect) {

	int top_side_clipping = draw_area.y - destination_rect.y;
	int left_side_clipping = draw_area.x - destination_rect.x;
	int right_side_size = draw_area.x + draw_area.w - destination_rect.x;
	int bot_side_size = draw_area.y + draw_area.h - destination_rect.y;

	source_rect.x = std::min(source_rect.w, std::max(source_rect.x, source_rect.x + left_side_clipping));
	source_rect.y = std::min(source_rect.h, std::max(source_rect.y, source_rect.y + top_side_clipping));

	source_rect.w = std::max(0, std::min(source_rect.w, right_side_size - std::max(0, left_side_clipping)));
	source_rect.h = std::max(0, std::min(source_rect.h, bot_side_size - std::max(0, top_side_clipping)));

	SDL_IntersectRect(&draw_area, &destination_rect, &destination_rect);

}

Uint8 scale_color(double bottom_color, double top_color) {
	bottom_color /= 255;
	top_color /= 255;

	return 255.0*(1 - (1-bottom_color)*(1-top_color));
}

SDL_Color lighter_color(const SDL_Color &color, double amount) {
	return {
		scale_color(color.r, amount*255),
		scale_color(color.g, amount*255),
		scale_color(color.b, amount*255),
		color.a
	};
}

SDL_Color darker_color(const SDL_Color &color, double amount) {
	return { (Uint8)(color.r*amount),
		(Uint8)(color.g*amount),
		(Uint8)(color.b*amount),
		color.a
	};
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
