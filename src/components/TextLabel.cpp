#include "TextLabel.h"
#include "../creation/TextureFactory.h"


namespace sdl_gui {

TextLabel::TextLabel(std::shared_ptr<creation::ITextureFactory> factory) :
		 m_text{""}, m_font_size{DEFAULT_FONT_SIZE}, m_halignment{Text_HAlignment::LEFT},
		 m_hoffset(0), m_valignment{Text_VAlignment::TOP}, m_voffset(0),
		 m_max_width(0), m_max_height(0), m_factory{factory} {
}

TextLabel::~TextLabel() {
}

void TextLabel::set_text(std::string text) {
	m_text = text;

	m_background = m_factory->create_text(text, m_color, m_font_size);
	int w, h;
	m_renderer->texture_width_and_height(m_background, w, h);

	if (m_max_width == 0) {
		m_max_width = w;
	}

	if (m_max_height == 0) {
		m_max_height = h;
	}

	m_dimension.w = std::min(w, m_max_width);
	m_dimension.h = std::min(h, m_max_height);
}

void TextLabel::set_relative_dimension(SDL_Rect r) {
	WindowBase::set_relative_dimension(r);
	m_max_width = r.w;
	m_max_height = r.h;
}

SDL_Rect TextLabel::relative_dimension() const {
	auto r = WindowBase::relative_dimension();

	switch (m_halignment) {
	case Text_HAlignment::LEFT:
		r.x = r.x + m_hoffset;
		break;
	case Text_HAlignment::RIGHT:

		r.x = r.x + m_max_width - m_dimension.w - m_hoffset;
		break;
	case Text_HAlignment::CENTER:
		r.x = r.x + m_max_width/2 - m_dimension.w/2 + m_hoffset;

		break;
	}

	switch (m_valignment) {
		case Text_VAlignment::TOP:
			r.y = r.y + m_voffset;
			break;
		case Text_VAlignment::BOTTOM:

			r.y = r.y + m_max_height - m_dimension.h - m_voffset;

			break;
		case Text_VAlignment::CENTER:
			r.y = r.y + m_max_height/2 - m_dimension.h/2 + m_voffset;
			break;
		}


	return r;
}

void TextLabel::set_horizontal_alignment(Text_HAlignment alignment, int offset) {
	m_halignment = alignment;
	m_hoffset = offset;
}

void TextLabel::set_vertical_alignment(Text_VAlignment alignment, int offset) {
	m_valignment = alignment;
	m_voffset = offset;
}


void TextLabel::set_font_size(int size) {
	m_font_size = size;
	if (!m_text.empty()) {
		set_text(m_text);
	}
}


} /* namespace sdl_gui */
