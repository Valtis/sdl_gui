/*
 * WindowBase.cpp
 *
 *  Created on: 3.7.2014
 *      Author: valtis
 */

#include "WindowBase.h"
#include "utility/Helpers.h"

namespace sdl_gui {

WindowBase::WindowBase() : m_dimension{0, 0, 0, 0}, m_color{0, 0, 0, 0}, m_background{nullptr, SDL_DestroyTexture}, m_parent(nullptr) {


}

WindowBase::~WindowBase() {
	// TODO Auto-generated destructor stub
}


void WindowBase::draw(SDL_Renderer *renderer) {

	SDL_Rect rect = { 0, 0, 0, 0 };

	if (m_parent != nullptr) {
		rect = m_parent->dimension();
	}

	rect.x += m_dimension.x;
	rect.y += m_dimension.y;
	rect.w = m_dimension.w;
	rect.h = m_dimension.h;

	SDL_RenderCopy(renderer, m_background.get(), nullptr, &rect);

	for (const auto &child : m_children) {
		child->draw(renderer);
	}

}



void WindowBase::add_child(std::unique_ptr<WindowBase> child) {
	child->set_parent(this);
	m_children.push_back(std::move(child));
}

void WindowBase::on_click(Sint16 mouse_x, Sint16 mouse_y) {
	auto child = child_under_coordinates(mouse_x, mouse_y);
	if (child != nullptr) {
		child->on_click(mouse_x, mouse_y);
	}
}

void WindowBase::on_drag(Sint16 mouse_x, Sint16 mouse_y, Sint16 dx, Sint16 dy) {
	auto child = child_under_coordinates(mouse_x, mouse_y);
	if (child != nullptr) {
		child->on_drag(mouse_x, mouse_y, dx, dy);
	}
}


WindowBase *WindowBase::child_under_coordinates(Sint16 x, Sint16 y) {
	for (const auto &child : m_children) {
		if (utility::point_inside_rect({x, y}, child->dimension())) {
			return child.get();
		}
	}

	return nullptr;
}

} /* namespace SDL_GUI */
