/*
 * WindowBase.cpp
 *
 *  Created on: 3.7.2014
 *      Author: valtis
 */

#include "WindowBase.h"

namespace SDL_GUI {

WindowBase::WindowBase() : m_dimension{0, 0, 0, 0}, m_color{0, 0, 0, 0}, m_background{nullptr, SDL_DestroyTexture} {


}

WindowBase::~WindowBase() {
	// TODO Auto-generated destructor stub
}


void WindowBase::draw(SDL_Renderer *renderer) {
	SDL_RenderCopy(renderer, m_background.get(), nullptr, &m_dimension);

}

void WindowBase::on_drag(Uint16 mouse_x, Uint16 mouse_y, Sint16 dx, Sint16 dy) {
	m_dimension.x += dx;
	m_dimension.y += dy;
}

} /* namespace SDL_GUI */
