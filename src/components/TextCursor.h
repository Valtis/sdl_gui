#ifndef TEXTCURSOR_H_
#define TEXTCURSOR_H_
#include <SDL2/SDL.h>
#include "WindowBase.h"

namespace sdl_gui {
namespace creation {
class ITextureFactory;
}
class TextCursor : public WindowBase {
public:
	TextCursor();
	virtual ~TextCursor();
	void set_cursor_position();

	virtual void on_gaining_focus() override;
	virtual void on_losing_focus() override;

	void reset_blink();

	void move_cursor(const SDL_Point movement, const std::vector<std::string> &lines);
	void set_cursor_line_position(SDL_Point position, const std::vector<std::string> &lines);
    SDL_Point cursor_line_position(const std::vector<std::string> &lines) const;

	void set_font_size(int font_size);
	void set_texture_factory(std::shared_ptr<creation::ITextureFactory> factory);
	void set_renderer(rendering::Renderer *renderer);


	void draw() const override;
private:

	void start_timer();
	void stop_timer();
	void update_cursor_texture();
	void update_cursor_position(const std::vector<std::string> &lines);

	std::shared_ptr<creation::ITextureFactory> m_texture_factory;
	int m_font_size;

	SDL_Point m_cursor_line_position; // x=the number of character the cursor is in front of, y = line number. Used to calculate new relative position on changes
	SDL_TimerID m_cursor_timer_id;

	bool m_draw_cursor;
};

} /* namespace sdl_gui */

#endif /* TEXTCURSOR_H_ */
