#include "Button.h"
#include "TextLabel.h"

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
