#include "TextCursorLinePosition.h"
#include "../utility/StringUtility.h"

namespace sdl_gui {

TextCursorLinePosition::TextCursorLinePosition() :
        m_cursor_line_position { 0, 0 } {

}

// m_cursor_line_position x value might be larger than the line allows so that when you move cursor up/down and move through shorter lines,
// it snaps to correct position once line is long enough to allow this.
// However, this method returns the visible position on screen, so x must be restricted to 0 < x < line_max_x
SDL_Point TextCursorLinePosition::cursor_line_position(const std::vector<std::string> &lines) const {

    int max_position = current_line_length(lines);

    return {
        std::min(max_position, m_cursor_line_position.x),
        m_cursor_line_position.y
    };
}

void TextCursorLinePosition::set_cursor_line_position(const SDL_Point position, const std::vector<std::string> &lines) {
    if (lines.empty()) {
        m_cursor_line_position = {0, 0};
        return;
    }
    m_cursor_line_position.y = std::max((Sint64)0, std::min((Sint64) lines.size() - 1, (Sint64)position.y));

    const int line_length = utility::glyph_count_utf8(lines[m_cursor_line_position.y]);
    m_cursor_line_position.x = std::max((Sint64)0, std::min((Sint64)line_length, (Sint64)position.x));
}

void TextCursorLinePosition::move_cursor(const SDL_Point movement, const std::vector<std::string> &lines) {
    if (lines.empty()) {
        m_cursor_line_position = {0, 0};
        return;
    }

    update_cursor_y_position(movement, lines);
    handle_cursor_movement(movement, lines);
}

void TextCursorLinePosition::update_cursor_y_position(const SDL_Point movement, const std::vector<std::string> &lines) {
    m_cursor_line_position.y = std::max((Sint64) 0,
            std::min((Sint64) lines.size() - 1, (Sint64) m_cursor_line_position.y + movement.y));
}

void TextCursorLinePosition::handle_cursor_movement(const SDL_Point movement, const std::vector<std::string> &lines) {
    const auto new_x = m_cursor_line_position.x + movement.x;
    if (cursor_moving_right(movement, new_x, lines)) {
        handle_right_movement(lines);
    } else if (cursor_moving_left_and_new_position_outside_right_edge(movement, new_x, lines)) {
        handle_left_movement_outside_right_edge(movement, lines);
    } else if (cursor_new_position_outside_left_edge(new_x)) {
        handle_cursor_outside_left_edge(lines);
    } else {
        set_cursor_position_to_new_position(new_x);
    }
}

bool TextCursorLinePosition::cursor_moving_right(const SDL_Point movement, const int new_x,
        const std::vector<std::string> &lines) const {
    return movement.x > 0 && new_x > current_line_length(lines);
}

bool TextCursorLinePosition::cursor_moving_left_and_new_position_outside_right_edge(const SDL_Point movement,
        const int new_x, const std::vector<std::string> &lines) const {
    return movement.x < 0 && new_x > current_line_length(lines);
}

bool TextCursorLinePosition::cursor_new_position_outside_left_edge(const int new_x) const {
    return new_x < 0;
}

void TextCursorLinePosition::handle_right_movement(const std::vector<std::string> &lines) {
    if (cursor_at_last_line(lines.size())) {
        m_cursor_line_position.x = current_line_length(lines);
    } else {
        ++m_cursor_line_position.y;
        m_cursor_line_position.x = 0;
    }
}

bool TextCursorLinePosition::cursor_at_last_line(const size_t line_size) const {
    return m_cursor_line_position.y == line_size - 1;
}

// cursor might still be right of the current line ending when moving left because when moving up\down, the x position is not updated
// so that the cursor snaps back to its old x position when line is long enough
void TextCursorLinePosition::handle_left_movement_outside_right_edge(const SDL_Point movement,
        const std::vector<std::string> &lines) {
    m_cursor_line_position.x = current_line_length(lines);
    move_cursor( { movement.x, 0 }, lines);
}

void TextCursorLinePosition::handle_cursor_outside_left_edge(const std::vector<std::string> &lines) {
    if (cursor_at_first_line()) {
        m_cursor_line_position.x = 0;
    } else {
        set_cursor_position_to_end_of_previous_line(lines);
    }
}

bool TextCursorLinePosition::cursor_at_first_line() const {
    return m_cursor_line_position.y == 0;
}

void TextCursorLinePosition::set_cursor_position_to_end_of_previous_line(const std::vector<std::string> &lines) {
    --m_cursor_line_position.y;
    m_cursor_line_position.x = current_line_length(lines);
}
void TextCursorLinePosition::set_cursor_position_to_new_position(const int new_x) {
    m_cursor_line_position.x = new_x;
}

int TextCursorLinePosition::current_line_length(const std::vector<std::string> &lines) const {
    if (lines.size() <= m_cursor_line_position.y) {
        return 0;
    }

    return utility::glyph_count_utf8(lines[m_cursor_line_position.y]);
}

void TextCursorLinePosition::calculate_cursor_line_position_from_character_position(const int cursor_character_position,
        const std::vector<std::string> &new_lines) {
    int glyphs_remaining = cursor_character_position;
    m_cursor_line_position = {0, 0};

    for (int i = 0; i < new_lines.size() && glyphs_remaining > 0; ++i) {
        update_cursor_line_position_by_line(new_lines[i], glyphs_remaining);
    }
}

void TextCursorLinePosition::update_cursor_line_position_by_line(const std::string &line, int &glyphs_remaining) {
    int line_glyph_count = utility::glyph_count_utf8(line);
    if (line_glyph_count < glyphs_remaining) {
        ++m_cursor_line_position.y;
        glyphs_remaining -= line_glyph_count;
    } else {
        m_cursor_line_position.x = glyphs_remaining;
        glyphs_remaining = 0;
    }
}
} /* namespace sdl_gui */
