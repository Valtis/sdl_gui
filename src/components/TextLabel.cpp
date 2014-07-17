#include "TextLabel.h"
#include "../creation/TextureFactory.h"

namespace sdl_gui {

TextLabel::TextLabel() : TextLabel("") {
}

TextLabel::TextLabel(std::string text) : m_text(text) {

}

TextLabel::~TextLabel() {
}

void TextLabel::set_text(std::string text) {
	m_text = text;
	creation::TextureFactory f(m_renderer);
	m_background = f.create_text(text);
	SDL_QueryTexture(m_background.get(), nullptr, nullptr, &m_dimension.w, &m_dimension.h);
}


} /* namespace sdl_gui */
