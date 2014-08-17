#include "StringUtility.h"
#include <cstring>
#include "../rendering/Renderer.h"
namespace sdl_gui {
namespace utility {

std::vector<std::string> tokenize(const std::string &text, const char delimiter, bool include_delimiters) {
    std::vector<std::string> tokens;

    if (text.empty()) {
        return tokens;
    }

    size_t begin_pos = 0;
    size_t end_pos = 0;

    while ((end_pos = text.find(delimiter, begin_pos)) != std::string::npos) {
        std::string token = text.substr(begin_pos, end_pos - begin_pos);

        if (!token.empty()) {
            tokens.push_back(token);
        }

        if (include_delimiters) {
            tokens.push_back(std::string("") + delimiter);
        }

        begin_pos = end_pos + 1;
    }

    if (begin_pos != std::string::npos) {
        tokens.push_back(text.substr(begin_pos));
    }

    return tokens;
}

std::vector<std::string> do_wrap(const std::string &text, const int font_size, rendering::Renderer *renderer,
        const int max_width);

std::vector<std::string> wrap_text(const std::string &text, const int font_size, rendering::Renderer *renderer,
        const SDL_Rect &text_box_size, const std::pair<int, int> offsets_from_sides) {
    int width = 0;
    renderer->text_width_and_height(text, font_size, &width, nullptr);

    const int max_width = text_box_size.w - offsets_from_sides.first - offsets_from_sides.second;
    if (width <= max_width || text.empty()) {
        return std::vector<std::string> { text };
    }

    return do_wrap(text, font_size, renderer, max_width);
}

std::vector<std::string> do_wrap(const std::string &text, const int font_size, rendering::Renderer *renderer,
        const int max_width) {

    const char delimiter = ' ';
    std::vector<std::string> tokens = tokenize(text, delimiter, true);
    std::vector<std::string> wrapped_lines;

    std::string wrapped_text = tokens[0];

    for (size_t i = 1; i < tokens.size(); ++i) {
        int width = 0;
        std::string new_string = wrapped_text + tokens[i];
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

bool is_continuation_codepoint(int c) {
    int mask = 0xc0; // 11000000
    return (c & mask) == 128; // is 10xxxxxx
}

// Todo: Refactor (or better yet, replace with unicode library instead of implementing this)
bool is_combining_character(const std::string &text, size_t start_pos) {
    // Combining Diacritical Marks U+0300 - U+036F -> between bytes 11001100:10000000 and 11001101:10101111

    const char block_1_first_char = 0xcc; // 11001100
    const char block_1_start = 0x80; // 10000000
    const char block_1_end = 0xaf; // 10101111

    if (start_pos <= text.length() - 2) {
        if (text[start_pos] == block_1_first_char && text[start_pos + 1] >= block_1_start
                && text[start_pos + 1] <= block_1_end) {
            return true;
        }
    }

    // Combining Diacritical Marks Extended U+1AB0 - U+1ABE:  11100001:10101010:10110000 - 11100001:10101010:10111110

    const char block_2_first_char = 0xe1;
    const char block_2_second_char = 0xaa;
    const char block_2_start = 0xb0;
    const char block_2_end = 0xbe;

    if (start_pos <= text.length() - 3) {
        if (text[start_pos] == block_2_first_char && text[start_pos + 1] == block_2_second_char
                && text[start_pos + 2] >= block_2_start && text[start_pos + 2] <= block_2_end) {
            return true;
        }
    }

    /* TODO: implement
     * Combining Diacritical Marks Supplement (1DC0–1DFF),
     * Combining Diacritical Marks for Symbols (20D0–20FF),
     * Combining Half Marks (FE20–FE2F)
     */

    return false;
}

bool is_glyph(const std::string &text, int pos) {
    return !is_continuation_codepoint(text[pos]) && !is_combining_character(text, pos);
}

std::string substring_utf8(const std::string &text, const size_t pos, const size_t length) {

    size_t start_buffer_pos = 0;
    size_t character_count = 0;
    while (character_count <= pos && start_buffer_pos < text.length()) {
        if (is_glyph(text, start_buffer_pos)) {
            ++character_count;
        }

        if (character_count <= pos) {
            ++start_buffer_pos;
        }
    }

    std::string ret;
    character_count = 0;
    for (size_t i = start_buffer_pos; character_count <= length && i < text.length(); ++i) {

        if (is_glyph(text, i)) {
            ++character_count;
        }

        if (character_count <= length) {
            ret += text[i];
        }
    }

    return ret;
}

std::string erase_from_end_utf8(const std::string &text, const int erasable_char_count) {
    int character_count = glyph_count_utf8(text);
    if (erasable_char_count >= character_count) {
        return "";
    }
    return substring_utf8(text, 0, character_count - erasable_char_count);
}

std::string erase_from_before_position_utf8(const std::string &text, const int erasable_char_count, const int position) {
    std::string beginning = "";
    if (erasable_char_count <= position) {
        beginning = substring_utf8(text, 0, position-erasable_char_count);
    }

    return beginning + substring_utf8(text, position, std::string::npos);
}

std::string erase_from_after_position_utf8(const std::string &text, const int erasable_char_count, const int position) {
    return substring_utf8(text, 0, position) + substring_utf8(text, position + erasable_char_count, std::string::npos);
}

int glyph_count_utf8(const std::string &text) {
    int count = 0;
    for (size_t i = 0; i < text.length(); ++i) {
        if (is_glyph(text, i)) {
            ++count;
        }
    }

    return count;
}

std::string add_text_to_position_utf8(const std::string &original, const std::string &new_text, const int position) {
    return substring_utf8(original, 0, position) + new_text + substring_utf8(original, position, std::string::npos);
}

} /* namespace utility */
} /* namespace sdl_gui */
