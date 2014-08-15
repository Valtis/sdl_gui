#ifndef TEXTCURSORLINEPOSITION_H_
#define TEXTCURSORLINEPOSITION_H_
#include <SDL2/SDL.h>
#include <vector>
#include <string>

namespace sdl_gui {

class TextCursorLinePosition {
public:
    TextCursorLinePosition();
    void move_cursor(const SDL_Point position, const std::vector<std::string> &lines);

    SDL_Point cursor_line_position(const std::vector<std::string> &lines) const;
    void set_cursor_line_position(const SDL_Point position, const std::vector<std::string> &lines);

    void calculate_cursor_line_position_from_character_position(const int cursor_character_position, const std::vector<std::string> &new_lines);
    void update_cursor_line_position_by_line(const std::string &line, int &glyphs_remaining);

private:

    void update_cursor_y_position(const SDL_Point movement, const std::vector<std::string> &lines);

    void handle_cursor_movement(const SDL_Point movement, const std::vector<std::string> &lines);
    bool cursor_moving_right(const SDL_Point movement, const int new_x, const std::vector<std::string> &lines) const;
    bool cursor_moving_left_and_new_position_outside_right_edge(const SDL_Point movement, const int new_x,
            const std::vector<std::string> &lines) const;
    bool cursor_new_position_outside_left_edge(const int new_x) const;

    void handle_right_movement(const std::vector<std::string> &lines);
    bool cursor_at_last_line(const size_t line_size) const;

    void handle_cursor_outside_left_edge(const std::vector<std::string> &lines);
    bool cursor_at_first_line() const;
    void set_cursor_position_to_end_of_previous_line(const std::vector<std::string> &lines);

    void handle_left_movement_outside_right_edge(const SDL_Point movement, const std::vector<std::string> &lines);
    void set_cursor_position_to_new_position(int new_x);

    int current_line_length(const std::vector<std::string> &lines) const;

    SDL_Point m_cursor_line_position; // x=the number of character the cursor is in front of, y = line number. Used to calculate new relative position on changes
};

} /* namespace sdl_gui */

#endif /* TEXTCURSORLINEPOSITION_H_ */
