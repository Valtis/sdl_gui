#include "TextBox.h"
#include "../utility/StringUtility.h"
namespace sdl_gui {

TextBox::TextBox(std::shared_ptr<creation::ITextureFactory> factory) : m_factory(factory), m_font_size(12), m_word_wrap(false) {

}

TextBox::~TextBox() {

}

void TextBox::on_gaining_focus() {
	SDL_StartTextInput();
}

void TextBox::on_losing_focus() {
	SDL_StopTextInput();
}

void TextBox::on_text_input(std::string text) {
	set_text(m_text + text);
}

void TextBox::on_key_down(SDL_Keycode code) {
	if (code == SDLK_BACKSPACE && m_text.length() > 0) {
		m_text.erase(m_text.end()-1);
		set_text(m_text);
	}
}

void TextBox::set_text(std::string text) {
	m_text_lines.clear();
	m_text = text;

	const int offset_from_left = 2;
	const int offset_from_right = 2;

	if (!text.empty()) {
		std::vector<std::string> m_lines;
		if (m_word_wrap) {
			m_lines = utility::wrap_text(m_text, m_font_size, m_renderer, relative_dimension(), { offset_from_left, offset_from_right });
		} else {
			m_lines.push_back(text);
		}

		int height = 0;
		int current_y_pos = 0;

		for (const std::string &line : m_lines) {
			auto label = std::make_shared<TextLabel>(m_factory);

			label->set_parent(this);
			label->set_renderer(m_renderer);
			label->set_text(line);
			label->set_relative_dimension({offset_from_left, current_y_pos, label->relative_dimension().w, label->relative_dimension().h});

			m_renderer->text_width_and_height(line, m_font_size, nullptr, &height);
			current_y_pos += height;
			m_text_lines.push_back(label);
		}
	}
}

void TextBox::draw() const {
	WindowBase::draw();
	for (const auto &line : m_text_lines) {
		line->draw();
	}

}

} /* namespace sdl_gui */
