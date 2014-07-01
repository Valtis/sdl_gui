/*
 * Window.cpp
 *
 *  Created on: 29.6.2014
 *      Author: valtis
 */

#include "Window.h"
#include "../serialization/Serializer.h"
#include <iostream>
#include <functional>
namespace SDL_GUI {

Window::Window(int x, int y) : m_title(""), m_dimension{x, y, 0, 0} {

}

Window::~Window() {
}



void Window::load(Serializer &serializer) {

	auto visitor = [&](const Node &node) {

		// if string is empty, returns zero
		auto stoi = [](const std::string &str) {
			if (str.empty()) {
				return 0;
			}
			return std::stoi(str);
		};

		std::cout << "Name: " << node.name() << "\n";
		if (node.name() == "window") {

			m_title = node.value("title");
			m_dimension.x = stoi(node.value("x"));
			m_dimension.y = stoi(node.value("y"));

			m_color.r = stoi(node.value("r"));
			m_color.g = stoi(node.value("g"));
			m_color.b = stoi(node.value("b"));



			m_color.a = SDL_ALPHA_OPAQUE;

		}

	};

	serializer.accept(visitor);

}


}
