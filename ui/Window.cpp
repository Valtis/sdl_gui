/*
 * Window.cpp
 *
 *  Created on: 29.6.2014
 *      Author: valtis
 */

#include "Window.h"
#include "../serialization/Serializer.h"
#include "creation/TextureFactory.h"
#include <functional>


namespace sdl_gui {

Window::Window() : m_title{""} {

}

Window::~Window() {
}



// TODO: Refactor the loading into something much nicer
void Window::load(Serializer &serializer, SDL_Renderer *renderer) {

	auto factory = creation::TextureFactory{renderer};

	auto visitor = [&](const Node &node) {

		// helper function, modifies stoi behaviour slightly
		// if string is empty, returns zero instead of throwing
		auto stoi = [](const std::string &str) {
			if (str.empty()) {
				return 0;
			}
			return std::stoi(str);
		};

		auto set_dimensions = [stoi](const Node &node, SDL_Rect &dimension) {
			dimension.x = stoi(node.value("x"));
			dimension.y = stoi(node.value("y"));
			dimension.w = stoi(node.value("w"));
			dimension.h = stoi(node.value("h"));
		};

		auto set_color = [stoi](const Node &node, SDL_Color &color) {
			color.r = stoi(node.value("r"));
			color.g = stoi(node.value("g"));
			color.b = stoi(node.value("b"));
			color.a = stoi(node.value("a"));
		};

		if (node.name() == "window") {

			m_title = node.value("title");

			set_dimensions(node, m_dimension);
			set_color(node, m_color);


			m_background = factory.create_window(m_dimension.w, m_dimension.h, m_color);

		} else if (node.name() == "button") {




			m_background = factory.create_window(m_dimension.w, m_dimension.h, m_color);

		}

	};

	serializer.accept(visitor);

}

}
