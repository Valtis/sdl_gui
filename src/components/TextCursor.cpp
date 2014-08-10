#include "TextCursor.h"
#include "../utility/StringUtility.h"
#include "../rendering/Renderer.h"
#include "../creation/ITextureFactory.h"

namespace sdl_gui {

TextCursor::TextCursor() : m_font_size(0) , m_cursor_line_position{0, 0},  m_cursor_timer_id{0},
		m_draw_cursor(false) {
    m_dimension = {1, 0, 1, 0 };
}

TextCursor::~TextCursor() {

}


void TextCursor::on_gaining_focus() {
	start_timer();
}

void TextCursor::on_losing_focus() {
	stop_timer();
	m_draw_cursor = false;
}

void TextCursor::reset_blink() {
	stop_timer();
	start_timer();
}

void TextCursor::move_cursor(const SDL_Point movement, const std::vector<std::string> &lines) {

	// fails if m_lines has more than 2^31 lines but this is mostly theoretical concern
	m_cursor_line_position.y = std::max(0, std::min((int)lines.size() - 1, m_cursor_line_position.y + movement.y));


	m_cursor_line_position.x = m_cursor_line_position.x + movement.x;

	// if x < 0, move to end of previous line, or if on first line, back to 0
	if (m_cursor_line_position.x < 0) {
		if (m_cursor_line_position.y == 0) {
			m_cursor_line_position.x = 0;
		} else {
			--m_cursor_line_position.y;
			m_cursor_line_position.x = lines[m_cursor_line_position.y].length();
		}
	}

	// if moving outside the end of line, move the cursor to the beginning of the next line, or if on last line, back to the end
	if (!lines.empty() && (size_t)m_cursor_line_position.x > lines[m_cursor_line_position.y].length()) {
			if ((size_t)m_cursor_line_position.y == lines.size() - 1) {
				m_cursor_line_position.x = lines[m_cursor_line_position.y].length();
			} else {
				++m_cursor_line_position.y;
				m_cursor_line_position.x = 0;
			}
		}

	update_cursor_position(lines);
}

void TextCursor::start_timer() {
	m_draw_cursor = true;
	if (m_cursor_timer_id == 0) {
		m_cursor_timer_id = SDL_AddTimer(750, [](Uint32 interval, void *param) {
			bool *draw_cursor = (bool *)param;
			*draw_cursor = !(*draw_cursor);
			return interval;
		},

		&m_draw_cursor);
	}
}

void TextCursor::stop_timer() {
	if (m_cursor_timer_id != 0) {
		SDL_RemoveTimer(m_cursor_timer_id);
		m_cursor_timer_id = 0;
	}
}

void TextCursor::update_cursor_position(const std::vector<std::string> &lines) {

	m_dimension.x = 1;
	m_dimension.y = 0;

	if (!lines.empty()) {
		auto line_text = lines[m_cursor_line_position.y];
		line_text = utility::substring_utf8(line_text, 0, m_cursor_line_position.x);
		int width = 0;
		int height = 0;
		m_renderer->text_width_and_height(line_text, m_font_size, &width, &height);
		m_dimension.x += width;
		m_dimension.y += height*m_cursor_line_position.y;
	}
}

void TextCursor::set_font_size(int size) {
	m_font_size = size;
	update_cursor_texture();
}

void TextCursor::update_cursor_texture() {
	if (m_renderer) {
		int height = m_renderer->get_font_height(m_font_size);

		m_background = m_texture_factory->create_text_cursor(1, height, {0, 0, 0, 255});
		m_dimension.h = height;
	}
}

void TextCursor::set_renderer(rendering::Renderer *renderer) {
	m_renderer = renderer;
	update_cursor_texture();
}

void TextCursor::set_texture_factory(std::shared_ptr<creation::ITextureFactory> factory) {
	m_texture_factory = factory;
}

void TextCursor::draw() const {
	if (m_draw_cursor) {
		WindowBase::draw();
	}
}



} /* namespace sdl_gui */
