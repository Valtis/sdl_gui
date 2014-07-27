#include "Button.h"
#include "TextLabel.h"
namespace sdl_gui {


Button::Button() : m_current_texture(Button_Graphics::DEFAULT),
		m_additional_textures{ texture_ptr{nullptr, SDL_DestroyTexture}, texture_ptr{ nullptr, SDL_DestroyTexture} } {
}

Button::~Button() {

}

void Button::draw() {
	if (m_current_texture == Button_Graphics::DEFAULT) {
		WindowBase::draw(m_background);
	} else {
		int position = static_cast<int>(m_current_texture);
		WindowBase::draw(m_additional_textures[position]);
	}
}

void Button::on_mouse_over(Sint32 mouse_x, Sint32 mouse_y) {
	m_current_texture = Button_Graphics::HOVER_OVER;
	call_handler(Handler_Type::ON_MOUSE_OVER);
}

void Button::on_mouse_down(Sint32 mouse_x, Sint32 mouse_y) {
	m_current_texture = Button_Graphics::PRESSED_DOWN;
	call_handler(Handler_Type::ON_MOUSE_DOWN);
}

void Button::on_mouse_up(Sint32 mouse_x, Sint32 mouse_y) {
	m_current_texture = Button_Graphics::DEFAULT;
	call_handler(Handler_Type::ON_CLICK);
}

void Button::on_losing_focus() {
	WindowBase::on_losing_focus();
	m_current_texture = Button_Graphics::DEFAULT;
}


// Todo: This probably should be handled in a less stupid way
std::string Button::get_text() {
	for (const auto &child : m_children) {
		TextLabel *label = dynamic_cast<TextLabel *>(child.get());
		if (label) {
			return label->get_text();
		}
	}
	return "";
}

} /* namespace SDL_GUI */
