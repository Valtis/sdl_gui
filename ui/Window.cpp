/*
 * Window.cpp
 *
 *  Created on: 29.6.2014
 *      Author: valtis
 */

#include "Window.h"
#include "../serialization/Serializer.h"
#include "creation/TextureFactory.h"

#include <iostream>
#include <functional>


namespace SDL_GUI {

Window::Window() : m_title{""}, m_dimension{0, 0, 0, 0}, m_background{nullptr, SDL_DestroyTexture} {

}

Window::Window(int x, int y) : m_title{""}, m_dimension{x, y, 0, 0}, m_background{nullptr, SDL_DestroyTexture} {

}


Window::~Window() {
}



void Window::load(Serializer &serializer, SDL_Renderer *renderer) {

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
			m_dimension.w = stoi(node.value("width"));
			m_dimension.h = stoi(node.value("height"));

			m_color.r = stoi(node.value("r"));
			m_color.g = stoi(node.value("g"));
			m_color.b = stoi(node.value("b"));
			m_color.a = stoi(node.value("a"));

			auto factory = creation::TextureFactory{renderer};
			m_background = factory.create_window(m_dimension.w, m_dimension.h, m_color);

		}

	};

	serializer.accept(visitor);

}

void Window::draw(SDL_Renderer *renderer) {
	SDL_RenderCopy(renderer, m_background.get(), nullptr, &m_dimension);

}

}
