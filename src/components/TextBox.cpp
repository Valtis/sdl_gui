#include "TextBox.h"

namespace sdl_gui {

TextBox::TextBox(std::shared_ptr<creation::ITextureFactory> factory) : m_factory(factory) {

}

TextBox::~TextBox() {

}

void TextBox::on_key_down(SDL_Keycode code) {

}

void TextBox::draw() const {
	WindowBase::draw();
	for (const auto &line : m_text_lines) {
		line->draw();
	}

}

} /* namespace sdl_gui */
