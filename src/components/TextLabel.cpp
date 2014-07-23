#include "TextLabel.h"
#include "../creation/TextureFactory.h"


namespace sdl_gui {

TextLabel::TextLabel(std::shared_ptr<creation::ITextureFactory> factory) :
		 m_text(""), m_factory(factory), m_font_size(DEFAULT_FONT_SIZE) {

}

TextLabel::~TextLabel() {
}

void TextLabel::set_text(std::string text) {
	m_text = text;

	m_background = m_factory->create_text(text, m_color, m_font_size);
	int w, h;
	m_renderer->texture_width_and_height(m_background, w, h);
	if (m_dimension.w == 0) {
		m_dimension.w = w;
	}

	if (m_dimension.h == 0) {
		m_dimension.h = h;
	}
}

void TextLabel::set_font_size(int size) {
	m_font_size = size;
	if (!m_text.empty()) {
		set_text(m_text);
	}
}


} /* namespace sdl_gui */
