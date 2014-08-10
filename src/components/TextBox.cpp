#include "TextBox.h"
#include "../utility/StringUtility.h"
namespace sdl_gui {

TextBox::TextBox(std::shared_ptr<creation::ITextureFactory> factory) : m_factory(factory), m_font_size(12), m_word_wrap(false),
		m_cursor{nullptr, SDL_DestroyTexture}, m_cursor_relative_position{0, 0, 0, 0}, m_cursor_line_position{0, 0},
		m_cursor_timer_id{0}, m_draw_cursor(false){
}

TextBox::~TextBox() {

}

void TextBox::on_gaining_focus() {
	SDL_StartTextInput();
	start_timer();
}

void TextBox::on_losing_focus() {
	SDL_StopTextInput();
	stop_timer();
	m_draw_cursor = false;
}

void TextBox::start_timer() {
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

void TextBox::stop_timer() {
	if (m_cursor_timer_id != 0) {
		SDL_RemoveTimer(m_cursor_timer_id);
		m_cursor_timer_id = 0;
	}
}

/**
 * text must be utf8-encoded
 */
void TextBox::on_text_input(std::string text) {
	set_text(m_text + text);
}

void TextBox::on_key_down(SDL_Keycode code) {
	stop_timer();
	start_timer();

	switch (code) {
	case SDLK_BACKSPACE:
		if (m_text.length() > 0) {
			m_text = utility::erase_from_end_utf8(m_text, 1);
			set_text(m_text);
		}
		break;
	case SDLK_LEFT:
		m_cursor_line_position.x = std::max(0, m_cursor_line_position.x - 1);
		set_cursor_position();
		break;

	case SDLK_RIGHT:
		{
			int max = 0;

			if (!m_text_lines.empty()) {
				max = m_text_lines[m_cursor_line_position.y]->get_text().length();
			}

			m_cursor_line_position.x = std::min(max, m_cursor_line_position.x + 1);
			set_cursor_position();
		}
		break;
	case SDLK_UP:
	{
		int max = 0;
		m_cursor_line_position.y = std::max(0, m_cursor_line_position.y - 1);

		if (!m_text_lines.empty()) {
			max = m_text_lines[m_cursor_line_position.y]->get_text().length();
		}

		m_cursor_line_position.x = std::max(0, std::min(max, m_cursor_line_position.x));
		set_cursor_position();
	}
	break;
	case SDLK_DOWN:
	{
		int max = 0;
		m_cursor_line_position.y = std::min(m_text_lines.size() - 1, (size_t)m_cursor_line_position.y + 1);

		if (!m_text_lines.empty()) {
			max = m_text_lines[m_cursor_line_position.y]->get_text().length();
		}

		m_cursor_line_position.x = std::max(0, std::min(max, m_cursor_line_position.x));
		set_cursor_position();
	}
	break;
	default:
		break;
	}
}

void TextBox::set_text(std::string text) {
	stop_timer();
	start_timer();

	m_text_lines.clear();
	m_text = text;

	set_text_lines();
	set_cursor_position();

}

void TextBox::set_text_lines() {

	if (m_text.empty()) {
		return;
	}

	const int offset_from_left = 2;
	const int offset_from_right = 2;

	std::vector<std::string> m_lines;
	if (m_word_wrap) {
		m_lines = utility::wrap_text(m_text, m_font_size, m_renderer, relative_dimension(), { offset_from_left, offset_from_right });
	} else {
		m_lines.push_back(m_text);
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

	m_cursor_line_position.y = m_lines.size() - 1;
	m_cursor_line_position.x = m_lines.back().length();
}

void TextBox::set_cursor_position() {

	m_cursor_relative_position.x = 1;
	m_cursor_relative_position.y = 0;

	if (!m_text_lines.empty()) {
		auto line_text = m_text_lines[m_cursor_line_position.y]->get_text();
		line_text = utility::substring_utf8(line_text, 0, m_cursor_line_position.x);
		int width = 0;
		int height = 0;
		m_renderer->text_width_and_height(line_text, m_font_size, &width, &height);
		m_cursor_relative_position.x += width;
		m_cursor_relative_position.y += height*m_cursor_line_position.y;
	}
}

void TextBox::draw() const {
	WindowBase::draw();
	for (const auto &line : m_text_lines) {
		line->draw();
	}

	if (m_draw_cursor) {
		auto pos = m_cursor_relative_position;
		pos.x += absolute_dimension().x;
		pos.y += absolute_dimension().y;
		do_draw(m_cursor, pos);
	}
}

} /* namespace sdl_gui */
