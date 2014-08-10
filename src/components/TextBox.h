#ifndef TEXTBOX_H_
#define TEXTBOX_H_
#include "WindowBase.h"
#include "TextLabel.h"
#include <memory>


namespace sdl_gui {

namespace creation {
	class ITextureFactory;
	class WindowLoader;
}

class TextBox : public WindowBase {
public:
	TextBox(std::shared_ptr<creation::ITextureFactory> factory);
	virtual ~TextBox();

	virtual void on_key_down(SDL_Keycode code) override;
	virtual void on_text_input(std::string text) override;
	virtual void draw() const override;

	virtual void on_gaining_focus() override;
	virtual void on_losing_focus() override;

	void set_text(std::string text);
	std::string get_text() {
		return m_text;
	}

	void set_word_wrap(bool wrap) {
		m_word_wrap = wrap;
	}

private:
	friend class creation::WindowLoader;

	void set_text_lines();
	void set_cursor_position();
	void start_timer();
	void stop_timer();
	std::shared_ptr<creation::ITextureFactory> m_factory;
	std::string m_text;
	// vector needs copyability in order to resize and unique_ptrs are non-copyable
	// therefore we use shared_ptrs
	std::vector<std::shared_ptr<TextLabel>> m_text_lines;
	int m_font_size;
	bool m_word_wrap;


	texture_ptr m_cursor;

	SDL_Rect m_cursor_relative_position;
	SDL_TimerID m_cursor_timer_id;

	bool m_draw_cursor;
};

} /* namespace sdl_gui */

#endif /* TEXTBOX_H_ */
