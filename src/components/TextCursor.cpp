#include "TextCursor.h"
#include "../utility/StringUtility.h"
#include "../rendering/Renderer.h"
#include "../creation/ITextureFactory.h"

namespace sdl_gui {

TextCursor::TextCursor() :
        m_font_size(0), m_cursor_timer_id { 0 }, m_cursor_x_offset(1), m_draw_cursor(false) {
    m_dimension = {1, 0, 1, 0};
}

void TextCursor::on_gaining_focus() {
    start_timer();
}

void TextCursor::on_losing_focus() {
    stop_timer();
    m_draw_cursor = false;
}

void TextCursor::move_cursor(const SDL_Point movement, const std::vector<std::string> &lines) {

    reset_blink();

    m_line_position.move_cursor(movement, lines);
    update_cursor_screen_position(lines);
    update_cursor_character_position(lines);
}

void TextCursor::set_cursor_line_position(const SDL_Point point, const std::vector<std::string> &lines) {

    m_line_position.set_cursor_line_position(point, lines);
    update_cursor_screen_position(lines);
    update_cursor_character_position(lines);
}

SDL_Point TextCursor::cursor_line_position(const std::vector<std::string> &lines) const {
    return m_line_position.cursor_line_position(lines);
}

int TextCursor::cursor_character_position() const {
    return m_character_position.cursor_character_position();
}

void TextCursor::text_insertion(const std::string &inserted_text, const std::string &text_string,
        const std::vector<std::string> &new_lines) {
    reset_blink();

    m_character_position.text_insertion(inserted_text, text_string, new_lines);
    m_line_position.calculate_cursor_line_position_from_character_position(
            m_character_position.cursor_character_position(), new_lines);

    update_cursor_screen_position(new_lines);
}

void TextCursor::text_deletion(const int delete_count, const std::vector<std::string> &new_lines) {
    m_character_position.text_deletion(delete_count);
    m_line_position.calculate_cursor_line_position_from_character_position(m_character_position.cursor_character_position(), new_lines);
    update_cursor_screen_position(new_lines);
}

void TextCursor::update_cursor_character_position(const std::vector<std::string> &lines) {
   m_character_position.update_cursor_character_position(m_line_position.cursor_line_position(lines), lines);
}

void TextCursor::update_cursor_screen_position(const std::vector<std::string> &lines) {

    m_dimension.x = m_cursor_x_offset;
    m_dimension.y = 0;

    if (lines.empty()) {
        return;
    }
    set_cursor_width_and_height(lines);
}

void TextCursor::set_cursor_width_and_height(const std::vector<std::string> &lines) {

    int width = 0;
    int height = 0;
    current_line_to_cursor_width_and_height(width, height, lines);

    int max_width = line_width_as_pixels(lines);
    m_dimension.x = std::min(max_width + m_cursor_x_offset, m_dimension.x + width);
    m_dimension.y += height * cursor_line_position(lines).y;
}

void TextCursor::current_line_to_cursor_width_and_height(int &width, int &height, const std::vector<std::string> &lines) const {
    auto line_position = cursor_line_position(lines);
    auto text_until_cursor = utility::substring_utf8(lines[line_position.y], 0, line_position.x);
    m_renderer->text_width_and_height(text_until_cursor, m_font_size, &width, &height);
}

int TextCursor::line_width_as_pixels(const std::vector<std::string> &lines) const {
    int width = 0;
    auto line_position = cursor_line_position(lines);
    auto line_text = lines[line_position.y];
    m_renderer->text_width_and_height(line_text, m_font_size, &width, 0);
    return width;
}




void TextCursor::reset_blink() {
    stop_timer();
    start_timer();
}

void TextCursor::start_timer() {
    m_draw_cursor = true;
    if (m_cursor_timer_id == 0) {
        set_timer();
    }
}

void TextCursor::set_timer() {
    m_cursor_timer_id = SDL_AddTimer(750, [](Uint32 interval, void *param) {
        bool *draw_cursor = (bool *)param;
        *draw_cursor = !(*draw_cursor);
        return interval;
    },

    &m_draw_cursor);
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
