#include "TextBox.h"
#include "../utility/StringUtility.h"
namespace sdl_gui {

TextBox::TextBox(std::shared_ptr<creation::ITextureFactory> factory, int font_size) :
        m_texture_factory(factory), m_font_size(font_size), m_word_wrap(false) {
    m_cursor.set_texture_factory(factory);
    m_cursor.set_parent(this);
    m_cursor.set_font_size(font_size);
}

TextBox::~TextBox() {

}

void TextBox::on_gaining_focus() {
    SDL_StartTextInput();
    m_cursor.on_gaining_focus();
}

void TextBox::on_losing_focus() {
    SDL_StopTextInput();
    m_cursor.on_losing_focus();
}

void TextBox::set_renderer(rendering::Renderer *renderer) {
    WindowBase::set_renderer(renderer);
    m_cursor.set_renderer(renderer);
}

/**
 * text must be utf8-encoded
 */
void TextBox::on_text_input(std::string text) {
    int m_lines_count = m_text_lines.size();

    std::string new_text = utility::substring_utf8(m_text, 0, m_cursor.cursor_character_position()) +
            text +
            utility::substring_utf8(m_text, utility::glyph_count_utf8(text) + m_cursor.cursor_character_position()-1, std::string::npos);

    set_text( new_text);

    m_cursor.text_insertion(text, m_text, get_text_lines());
}

void TextBox::on_key_down(SDL_Keycode code) {
    m_cursor.reset_blink();

    switch (code) {
    case SDLK_BACKSPACE:
        if (m_text.length() > 0) {
            m_text = utility::erase_from_end_utf8(m_text, 1);
            set_text(m_text);
            m_cursor.move_cursor( { -1, 0 }, get_text_lines());
        }
        break;
    case SDLK_LEFT:
        m_cursor.move_cursor( { -1, 0 }, get_text_lines());

        break;

    case SDLK_RIGHT:
        m_cursor.move_cursor( { 1, 0 }, get_text_lines());
        break;
    case SDLK_UP:
        m_cursor.move_cursor( { 0, -1 }, get_text_lines());
        break;
    case SDLK_DOWN:
        m_cursor.move_cursor( { 0, 1 }, get_text_lines());
        break;
    default:
        break;
    }
}

void TextBox::set_text(std::string text) {
    m_cursor.reset_blink();

    m_text_lines.clear();
    m_text = text;

    set_text_lines();
}

void TextBox::set_text_lines() {

    if (m_text.empty()) {
        return;
    }

    const int offset_from_left = 2;
    const int offset_from_right = 2;

    std::vector<std::string> m_lines;
    if (m_word_wrap) {
        m_lines = utility::wrap_text(m_text, m_font_size, m_renderer, relative_dimension(), { offset_from_left,
                offset_from_right });
    } else {
        m_lines.push_back(m_text);
    }

    int height = 0;
    int current_y_pos = 0;

    for (const std::string &line : m_lines) {
        auto label = std::make_shared<TextLabel>(m_texture_factory);

        label->set_parent(this);
        label->set_renderer(m_renderer);
        label->set_text(line);
        label->set_relative_dimension(
                { offset_from_left, current_y_pos, label->relative_dimension().w, label->relative_dimension().h });

        m_renderer->text_width_and_height(line, m_font_size, nullptr, &height);
        current_y_pos += height;
        m_text_lines.push_back(label);
    }
}

std::vector<std::string> TextBox::get_text_lines() {
    std::vector<std::string> ret;
    for (auto line : m_text_lines) {
        ret.push_back(line->get_text());
    }

    return ret;
}

void TextBox::draw() const {
    WindowBase::draw();
    for (const auto &line : m_text_lines) {
        line->draw();
    }

    m_cursor.draw();
}

void TextBox::set_font_size(int size) {
    m_font_size = size;
    m_cursor.set_font_size(size);
}

} /* namespace sdl_gui */
