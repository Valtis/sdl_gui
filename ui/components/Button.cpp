#include "Button.h"

#include <iostream>

namespace sdl_gui {

Button::Button() : Button(""){

}

Button::Button(std::string text) : m_text_string{text}, m_text_texture{nullptr, SDL_DestroyTexture} {

}

Button::~Button() {

}

void Button::draw(SDL_Renderer *renderer) {
	WindowBase::draw(renderer);

}

void Button::on_click(Sint16 x, Sint16 y) {
	std::cout << "Pressed! X: " << x << "\tY: " << y << "\n";
}

} /* namespace SDL_GUI */
