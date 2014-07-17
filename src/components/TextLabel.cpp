#include "TextLabel.h"
#include "../creation/TextureFactory.h"

namespace sdl_gui {

TextLabel::TextLabel(creation::TextureFactory factory) : TextLabel{factory, ""} {
}

TextLabel::TextLabel(creation::TextureFactory factory, std::string text) :
		 m_text(text), m_factory(factory){

}

TextLabel::~TextLabel() {
}

void TextLabel::set_text(std::string text) {
	m_text = text;
	m_background = m_factory.create_text(text);
	SDL_QueryTexture(m_background.get(), nullptr, nullptr, &m_dimension.w, &m_dimension.h);
}


} /* namespace sdl_gui */
