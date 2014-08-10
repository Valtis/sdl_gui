#ifndef TEXTBOX_H_
#define TEXTBOX_H_
#include "WindowBase.h"
#include "TextLabel.h"
#include "TextCursor.h"
#include <memory>


namespace sdl_gui {

namespace creation {
	class ITextureFactory;
	class WindowLoader;
}

class TextBox : public WindowBase {
public:
	TextBox(std::shared_ptr<creation::ITextureFactory> factory, int font_size);
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

	void set_font_size(int size);
	void set_renderer(rendering::Renderer *renderer) override;

private:
	friend class creation::WindowLoader;

	void set_text_lines();
	std::vector<std::string> get_text_lines();

	std::shared_ptr<creation::ITextureFactory> m_texture_factory;
	std::string m_text;
	// vector needs copyability in order to resize and unique_ptrs are non-copyable
	// therefore we use shared_ptrs
	std::vector<std::shared_ptr<TextLabel>> m_text_lines;
	int m_font_size;
	bool m_word_wrap;

	TextCursor m_cursor;
};

} /* namespace sdl_gui */

#endif /* TEXTBOX_H_ */
