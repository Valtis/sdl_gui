#include "Window.h"
#include "../serialization/Serializer.h"
#include <functional>

namespace sdl_gui {

Window::Window() : m_title{""} {

}

Window::~Window() {
}

void Window::on_drag(Sint16 mouse_x, Sint16 mouse_y, Sint16 dx, Sint16 dy) {
	auto child = child_under_coordinates(mouse_x, mouse_y);
	if (child) {
		child->on_drag(mouse_x, mouse_y, dx, dy);
		return;
	}
	m_dimension.x += dx;
	m_dimension.y += dy;
}

} /* namespace sdl_gui */
