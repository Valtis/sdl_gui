#include "Button.h"
#include "TextLabel.h"
namespace sdl_gui {


Button::Button(std::shared_ptr<creation::ITextureFactory> factory) : m_current_texture(ButtonGraphics::DEFAULT),
		m_additional_textures{ texture_ptr{nullptr, SDL_DestroyTexture}, texture_ptr{ nullptr, SDL_DestroyTexture} } {
	std::unique_ptr<TextLabel> label{new TextLabel{factory}};
	add_child(std::move(label));
}

Button::~Button() {

}

void Button::draw() {
	if (m_current_texture == ButtonGraphics::DEFAULT) {
		WindowBase::draw(m_background);
	} else {
		int position = static_cast<int>(m_current_texture);
		WindowBase::draw(m_additional_textures[position]);
	}
}

void Button::on_mouse_over(Sint32 mouse_x, Sint32 mouse_y) {
	m_current_texture = ButtonGraphics::HOVER_OVER;
}

void Button::on_mouse_down(Sint32 mouse_x, Sint32 mouse_y) {
	WindowBase::on_mouse_down(mouse_x, mouse_y);
	m_current_texture = ButtonGraphics::PRESSED_DOWN;
}

void Button::on_mouse_up(Sint32 mouse_x, Sint32 mouse_y) {
	m_current_texture = ButtonGraphics::DEFAULT;
	call_handler(HandlerType::ON_CLICK);
}

void Button::on_losing_focus() {
	WindowBase::on_losing_focus();
	m_current_texture = ButtonGraphics::DEFAULT;
}

} /* namespace SDL_GUI */
