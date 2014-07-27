#include "TextLabel.h"
#include "../creation/TextureFactory.h"


namespace sdl_gui {

TextLabel::TextLabel(std::shared_ptr<creation::ITextureFactory> factory) :
		 m_text{""}, m_font_size{DEFAULT_FONT_SIZE}, m_halignment{Text_HAlignment::LEFT},
		 m_hoffset(0), m_valignment{Text_VAlignment::TOP}, m_voffset(0), m_factory{factory} {
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

SDL_Rect TextLabel::relative_dimension() const {
	auto r = WindowBase::relative_dimension();

	switch (m_halignment) {
	case Text_HAlignment::LEFT:
		r.x = r.x + m_hoffset;
		break;
	case Text_HAlignment::RIGHT:
		if (m_parent != nullptr) {
			r.x = m_parent->relative_dimension().w - m_dimension.w - m_hoffset;
		}
		break;
	case Text_HAlignment::CENTER:
		if (m_parent != nullptr) {
			r.x = m_parent->relative_dimension().w/2 - m_dimension.w/2 + m_hoffset;
		}
		break;
	}

	switch (m_valignment) {
		case Text_VAlignment::TOP:
			r.y = r.y + m_voffset;
			break;
		case Text_VAlignment::BOTTOM:
			if (m_parent != nullptr) {
				r.y = m_parent->relative_dimension().h - m_dimension.h - m_voffset;
			}
			break;
		case Text_VAlignment::CENTER:
			if (m_parent != nullptr) {
				r.y = m_parent->relative_dimension().h/2 - m_dimension.h/2 + m_voffset;
			}
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
