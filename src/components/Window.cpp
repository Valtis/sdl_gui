#include "Window.h"
#include "../serialization/Serializer.h"
#include <functional>

namespace sdl_gui {

Window::Window() : m_title{""}, m_child_is_being_dragged(false), m_has_focus(false), m_no_focus_overlay{nullptr, SDL_DestroyTexture} {

}

Window::~Window() {
}

void Window::on_drag(Sint32 mouse_x, Sint32 mouse_y, Sint32 dx, Sint32 dy) {
	auto child = child_under_coordinates(mouse_x, mouse_y);
	if (child) {
		child->on_drag(mouse_x, mouse_y, dx, dy);
		m_child_is_being_dragged = true;
		return;
	}

	if (!m_child_is_being_dragged) {
		m_dimension.x += dx;
		m_dimension.y += dy;
	}
}

void Window::draw() const {
	WindowBase::draw();

	if (!m_has_focus) {
		auto r = absolute_dimension();
		m_renderer->draw(m_no_focus_overlay, nullptr, &r);
	}
}

void Window::on_mouse_up(Sint32 mouse_x, Sint32 mouse_y) {
	WindowBase::on_mouse_up(mouse_x, mouse_y);
	m_child_is_being_dragged = false;
}

void Window::on_losing_focus() {
	WindowBase::on_losing_focus();
	m_child_is_being_dragged = false;
	m_has_focus = false;
}

void Window::on_gaining_focus() {
	WindowBase::on_gaining_focus();
	m_has_focus = true;
}

} /* namespace sdl_gui */
