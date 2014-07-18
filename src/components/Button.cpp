#include "Button.h"
#include "TextLabel.h"
#include <iostream>

namespace sdl_gui {

Button::Button(const creation::TextureFactory &factory) : Button{factory, ""} {

}

Button::Button(const creation::TextureFactory &factory, std::string text) : m_text(text) {
	std::unique_ptr<TextLabel> label{new TextLabel{factory, text}};
	add_child(std::move(label));
}

Button::~Button() {

}

void Button::draw() {
	WindowBase::draw();
}

void Button::on_mouse_over(Sint16 mouse_x, Sint16 mouse_y) {
	WindowBase::on_mouse_over(mouse_x, mouse_y);
	std::cout << "Button mouse over event\n";
}

void Button::on_losing_focus() {
	WindowBase::on_losing_focus();

	std::cout << "Button lost focus!\n";
}

void Button::set_text(std::string text) {
	m_text = text;
	TextLabel *label = static_cast<TextLabel *>(m_children[0].get());
	label->set_text(text);
	SDL_Rect r = label->absolute_dimension();

	r.x = m_dimension.w/2 - r.w/2;
	r.y = m_dimension.h/2 - r.h/2;
	label->set_relative_dimension(r);
}

} /* namespace SDL_GUI */
