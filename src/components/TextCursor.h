#ifndef TEXTCURSOR_H_
#define TEXTCURSOR_H_
#include <SDL2/SDL.h>
#include "WindowBase.h"

#include "TextCursorLinePosition.h"

namespace sdl_gui {
namespace creation {
class ITextureFactory;
}
class TextCursor: public WindowBase {
public:
    TextCursor();
    virtual ~TextCursor();
    void set_cursor_position();

    virtual void on_gaining_focus() override;
    virtual void on_losing_focus() override;

    void move_cursor(const SDL_Point movement, const std::vector<std::string> &lines);
    void text_insertion(const std::string &inserted_text, const std::string &total_text_string,
            const std::vector<std::string> &new_lines);

    void text_deletion(const int deletion_count, const std::vector<std::string> &new_lines);
    void set_cursor_line_position(const SDL_Point position, const std::vector<std::string> &lines);
    SDL_Point cursor_line_position(const std::vector<std::string> &lines) const;
    int cursor_character_position() const {
        return m_cursor_character_position;
    }

    void set_font_size(int font_size);
    void set_texture_factory(std::shared_ptr<creation::ITextureFactory> factory);
    void set_renderer(rendering::Renderer *renderer);

    void draw() const override;

private:
    void reset_blink();
    void start_timer();
    void stop_timer();
    void update_cursor_texture();
    void update_cursor_screen_position(const std::vector<std::string> &lines);
    void update_cursor_text_position(const std::vector<std::string> &lines);


    std::shared_ptr<creation::ITextureFactory> m_texture_factory;
    int m_font_size;

    TextCursorLinePosition m_line_position;

    int m_cursor_character_position; // 0 = before first character in unwrapped string, string.length_utf8() = position in the front of last character
    SDL_TimerID m_cursor_timer_id;

    bool m_draw_cursor;
};

} /* namespace sdl_gui */

#endif /* TEXTCURSOR_H_ */
