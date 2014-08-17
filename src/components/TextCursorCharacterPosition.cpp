#include "TextCursorCharacterPosition.h"
#include "../utility/StringUtility.h"
namespace sdl_gui {

TextCursorCharacterPosition::TextCursorCharacterPosition() :
        m_cursor_character_position(0) {

}

int TextCursorCharacterPosition::cursor_character_position() const {
    return m_cursor_character_position;
}

void TextCursorCharacterPosition::update_cursor_character_position(const SDL_Point cursor_line_position, const std::vector<std::string> &lines) {
    m_cursor_character_position = 0;

   if (lines.empty()) {
       return;
   }


   for (int y = 0; y < cursor_line_position.y; ++y) {
       m_cursor_character_position += utility::glyph_count_utf8(lines[y]);
   }

   m_cursor_character_position += cursor_line_position.x;
}

void TextCursorCharacterPosition::text_insertion(const std::string &inserted_text, const std::string &text_string,
        const std::vector<std::string> &new_lines) {

    m_cursor_character_position += utility::glyph_count_utf8(inserted_text);
    const int text_length = utility::glyph_count_utf8(text_string);
    m_cursor_character_position = std::max(0, std::min(m_cursor_character_position, text_length));
}

void TextCursorCharacterPosition::text_deletion(int delete_count) {
    m_cursor_character_position = std::max(0, m_cursor_character_position - delete_count);
}

} /* namespace sdl_gui */
