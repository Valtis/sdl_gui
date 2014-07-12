/*
 * Window.cpp
 *
 *  Created on: 29.6.2014
 *      Author: valtis
 */

#include "Window.h"
#include "../serialization/Serializer.h"
#include <functional>


namespace sdl_gui {

Window::Window() : m_title{""} {

}

Window::~Window() {
}

void Window::on_drag(Sint16 mouse_x, Sint16 mouse_y, Sint16 dx, Sint16 dy) {
	m_dimension.x += dx;
	m_dimension.y += dy;
}

} /* namespace sdl_gui */
