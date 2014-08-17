#ifndef TEXTCURSOR_H_
#define TEXTCURSOR_H_
#include <SDL2/SDL.h>
#include "WindowBase.h"

#include "TextCursorLinePosition.h"
#include "TextCursorCharacterPosition.h"

namespace sdl_gui {

namespace creation {
class ITextureFactory;
}

class TextCursor: public WindowBase {
public:
    TextCursor();
    void set_cursor_position();

    virtual void on_gaining_focus() override;
    virtual void on_losing_focus() override;

    void move_cursor(const SDL_Point movement, const std::vector<std::string> &lines);
    void text_insertion(const std::string &inserted_text, const std::string &total_text_string,
            const std::vector<std::string> &new_lines);

    void text_deletion(const int deletion_count, const std::vector<std::string> &new_lines);

    void set_cursor_line_position(const SDL_Point position, const std::vector<std::string> &lines);
    SDL_Point cursor_line_position(const std::vector<std::string> &lines) const;
    int cursor_character_position() const;

    void set_font_size(int font_size);
    void set_texture_factory(std::shared_ptr<creation::ITextureFactory> factory);
    void set_renderer(rendering::Renderer *renderer);

    void draw() const override;

private:
    void reset_blink();
    void start_timer();
    void set_timer();
    void stop_timer();
    void update_cursor_texture();
    void update_cursor_screen_position(const std::vector<std::string> &lines);
    void update_cursor_character_position(const std::vector<std::string> &lines);

    void set_cursor_width_and_height(const std::vector<std::string> &lines);
    int line_width_as_pixels(const std::vector<std::string> &lines) const;
    void current_line_to_cursor_width_and_height(int &width, int &height, const std::vector<std::string> &lines) const;



    std::shared_ptr<creation::ITextureFactory> m_texture_factory;
    int m_font_size;

    TextCursorLinePosition m_line_position;
    TextCursorCharacterPosition m_character_position;

    const int m_cursor_x_offset; // offset to cursor position to make it look a bit better
    SDL_TimerID m_cursor_timer_id;
    bool m_draw_cursor;
};

} /* namespace sdl_gui */

#endif /* TEXTCURSOR_H_ */
