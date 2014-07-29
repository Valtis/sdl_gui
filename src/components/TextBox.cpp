#include "TextBox.h"

namespace sdl_gui {

TextBox::TextBox(std::shared_ptr<creation::ITextureFactory> factory) : m_factory(factory) {

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
	m_text += text;
	m_text_lines.clear();
	auto label = std::make_shared<TextLabel>(m_factory);
	label->set_parent(this);
	label->set_renderer(m_renderer);
	label->set_text(m_text);
	m_text_lines.push_back(label);
}

void TextBox::draw() const {
	WindowBase::draw();
	for (const auto &line : m_text_lines) {
		line->draw();
	}

}

} /* namespace sdl_gui */
