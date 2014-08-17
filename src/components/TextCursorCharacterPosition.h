#ifndef TEXTCURSORCHARACTERPOSITION_H_
#define TEXTCURSORCHARACTERPOSITION_H_
#include <SDL2/SDL.h>
#include <vector>
#include <string>
namespace sdl_gui {

/**
 * This class handles cursor position as offset from the beginning of the text string. This allows easier cursor position updates when typing or deleting text
 */
class TextCursorCharacterPosition {
public:
    TextCursorCharacterPosition();

    int cursor_character_position() const;
    void update_cursor_character_position(const SDL_Point cursor_line_position, const std::vector<std::string> &lines);

    void text_insertion(const std::string &inserted_text, const std::string &text_string, const std::vector<std::string> &new_lines);
    void text_deletion(int delete_count);


private:
    int m_cursor_character_position; // 0 = before first character in unwrapped string, string.length_utf8() = position in the front of last character
};

} /* namespace sdl_gui */

#endif /* TEXTCURSORCHARACTERPOSITION_H_ */
