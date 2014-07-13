#include "Button.h"
#include "TextLabel.h"
#include <iostream>

namespace sdl_gui {

Button::Button() :  Button{""} {

}

Button::Button(std::string text) : m_text(text) {
	std::unique_ptr<TextLabel> label{new TextLabel{text}};
	add_child(std::move(label));
}

Button::~Button() {

}

void Button::draw() {
	WindowBase::draw();
}

void Button::on_click(Sint16 x, Sint16 y) {
	std::cout << "Pressed! X: " << x << "\tY: " << y << "\n";
}

void Button::set_text(std::string text) {
	m_text = text;
	TextLabel *label = static_cast<TextLabel *>(m_children[0].get());
	label->set_text(text);
}

} /* namespace SDL_GUI */
