#include "TextCursor.h"
#include "../utility/StringUtility.h"
#include "../rendering/Renderer.h"
#include "../creation/ITextureFactory.h"

namespace sdl_gui {

TextCursor::TextCursor() :
        m_font_size(0), m_cursor_line_position { 0, 0 }, m_cursor_character_position(0), m_cursor_timer_id { 0 }, m_draw_cursor(false) {
    m_dimension = {1, 0, 1, 0};
}

TextCursor::~TextCursor() {

}

void TextCursor::on_gaining_focus() {
    start_timer();
}

void TextCursor::on_losing_focus() {
    stop_timer();
    m_draw_cursor = false;
}

void TextCursor::reset_blink() {
    stop_timer();
    start_timer();
}

void TextCursor::move_cursor(const SDL_Point movement, const std::vector<std::string> &lines) {

    if (lines.size() == 0) {
        m_cursor_line_position = {0, 0};
    }

    m_cursor_line_position.y = std::max((Sint64)0, std::min((Sint64) lines.size() - 1, (Sint64)m_cursor_line_position.y + movement.y));

    const auto new_x = m_cursor_line_position.x + movement.x;
    const auto line_length = utility::glyph_count_utf8(lines[m_cursor_line_position.y]);

    // if moving right and new position is larger than glyph count in the line:
    // * if the line in question is the last one, move the cursor back to the end of line
    // * else, move the cursor to the beginning of next line
    if (movement.x > 0 && new_x > line_length) {
        if (m_cursor_line_position.y == lines.size() - 1) {
            m_cursor_line_position.x = line_length;
        } else {
            ++m_cursor_line_position.y;
            m_cursor_line_position.x = 0;
        }
        // if moving left, and cursor position is larger than glyph count (happens when moving up/down from longer line first as
        // x-value is intentionally not updated, only constrained for drawing):
        // set current cursor position to the end of current line and call the method again with the x-value so that any other constraints are respected
    } else if (movement.x < 0 && new_x > line_length) {
        m_cursor_line_position.x = line_length;
        move_cursor( {movement.x, 0}, lines);
    }
    // if x is smaller than zero:
    // * if at first line, set x to zero
    // * otherwise, move the cursor the end of previous line
    else if (new_x < 0) {
        if (m_cursor_line_position.y == 0) {
            m_cursor_line_position.x = 0;
        } else {
            --m_cursor_line_position.y;
            m_cursor_line_position.x = utility::glyph_count_utf8(lines[m_cursor_line_position.y]);
        }
        // if new coordinate is within the line boundaries, just update the position
    } else {
        m_cursor_line_position.x = new_x;
    }

    update_cursor_position (lines);
    update_cursor_text_position(lines);
}

void TextCursor::update_cursor_position(const std::vector<std::string> &lines) {

    const int x_offset = 1; // move cursor slightly right so it looks better
    m_dimension.x = x_offset;
    m_dimension.y = 0;

    int max_width = 0;

    if (!lines.empty()) {
        auto line_text = lines[m_cursor_line_position.y];
        m_renderer->text_width_and_height(line_text, m_font_size, &max_width, 0);

        line_text = utility::substring_utf8(line_text, 0, m_cursor_line_position.x);
        int width = 0;
        int height = 0;
        m_renderer->text_width_and_height(line_text, m_font_size, &width, &height);

        m_dimension.x = std::min(max_width + x_offset, m_dimension.x + width);
        m_dimension.y += height * m_cursor_line_position.y;
    }
}

void TextCursor::update_cursor_text_position(const std::vector<std::string> &lines) {
    const auto position = cursor_line_position(lines);
    m_cursor_character_position = 0;

    for (int y = 0; y < position.y; ++y) {
        m_cursor_character_position += utility::glyph_count_utf8(lines[y]);
    }

    m_cursor_character_position += position.x;
}

void TextCursor::set_cursor_line_position(SDL_Point point, const std::vector<std::string> &lines) {
    if (lines.size() == 0) {
        m_cursor_line_position = {0, 0};
    }

    m_cursor_line_position.y = std::max((Sint64)0, std::min((Sint64) lines.size() - 1, (Sint64)point.y));

    const int line_length = utility::glyph_count_utf8(lines[m_cursor_line_position.y]);
    m_cursor_line_position.x = std::max((Sint64)0, std::min((Sint64)line_length, (Sint64)point.x));
    update_cursor_position(lines);
    update_cursor_text_position(lines);
}

void TextCursor::text_insertion(const std::string &inserted_text, const std::string &text_string,
        const std::vector<std::string> &new_lines) {
    m_cursor_character_position += utility::glyph_count_utf8(inserted_text);
    const int text_length = utility::glyph_count_utf8(text_string);

    m_cursor_character_position = std::max(0, std::min(m_cursor_character_position, text_length));
    calculate_cursor_line_position_from_character_position(new_lines);
    update_cursor_position(new_lines);
}

void TextCursor::text_deletion(const int delete_count, const std::vector<std::string> &new_lines) {
    m_cursor_character_position = std::max(0, m_cursor_character_position - delete_count);
    calculate_cursor_line_position_from_character_position(new_lines);
    update_cursor_position(new_lines);
}



void TextCursor::calculate_cursor_line_position_from_character_position(const std::vector<std::string> &new_lines) {
    int glyphs_remaining = m_cursor_character_position;
    m_cursor_line_position = {0, 0};

    for (int i = 0; i < new_lines.size() && glyphs_remaining > 0; ++i) {
        update_cursor_line_position_by_line(new_lines[i], glyphs_remaining);
    }
}

void TextCursor::update_cursor_line_position_by_line(const std::string &line, int &glyphs_remaining) {
    int line_glyph_count = utility::glyph_count_utf8(line) ;
    if (line_glyph_count < glyphs_remaining) {
        ++m_cursor_line_position.y;
        glyphs_remaining -= line_glyph_count;
    } else {
        m_cursor_line_position.x = glyphs_remaining;
        glyphs_remaining = 0;
    }
}


// m_cursor_line_position x value might be larger than the line allows so that when you move cursor up/down and move through shorter lines,
// it snaps to correct position once line is long enough to allow this.
// However, this method returns the visible position on screen, so x must be restricted to 0 < x < line_max_x
SDL_Point TextCursor::cursor_line_position(const std::vector<std::string> &lines) const {
    int max_position = utility::glyph_count_utf8(lines[m_cursor_line_position.y]);
    return {
        std::min(max_position, m_cursor_line_position.x),
        m_cursor_line_position.y
    };
}

void TextCursor::start_timer() {
    m_draw_cursor = true;
    if (m_cursor_timer_id == 0) {
        m_cursor_timer_id = SDL_AddTimer(750, [](Uint32 interval, void *param) {
            bool *draw_cursor = (bool *)param;
            *draw_cursor = !(*draw_cursor);
            return interval;
        },

        &m_draw_cursor);
    }
}

void TextCursor::stop_timer() {
    if (m_cursor_timer_id != 0) {
        SDL_RemoveTimer(m_cursor_timer_id);
        m_cursor_timer_id = 0;
    }
}

void TextCursor::set_font_size(int size) {
    m_font_size = size;
    update_cursor_texture();
}

void TextCursor::update_cursor_texture() {
    if (m_renderer && m_texture_factory) {
        int height = m_renderer->get_font_height(m_font_size);
        m_background = m_texture_factory->create_text_cursor(1, height, { 0, 0, 0, 255 });
        m_dimension.h = height;
    }
}

void TextCursor::set_renderer(rendering::Renderer *renderer) {
    m_renderer = renderer;
    update_cursor_texture();
}

void TextCursor::set_texture_factory(std::shared_ptr<creation::ITextureFactory> factory) {
    m_texture_factory = factory;
}

void TextCursor::draw() const {
    if (m_draw_cursor) {
        WindowBase::draw();
    }
}

} /* namespace sdl_gui */
